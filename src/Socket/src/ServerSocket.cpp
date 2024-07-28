/**
 * @copyright Copyright (c) 2023
 * 
 * @author Hugo Fernandez Solis (hugofernandezsolis@gmail.com)
 * @date 02-12-2023
 * 
 * @file ServerSocket.cpp
 * 
 * @brief 
 */


#include <ServerSocket.h>


namespace ipc {   // Inter-Process Communication


/**
 * @brief
 * 
 */
ServerSocket::ServerSocket(void):
  Socket() {}

/**
 * @brief 
 * 
 * @param iMaxConnNumber 
 * 
 * @return 
 */
bool ServerSocket::listen(const uint& iMaxConnNumber) const {
  if (this->get_type() == SOCKET_TCP) {
    if (::listen(this->get_sd(), iMaxConnNumber) < 0) {
      LOG_ERROR << "Error listening for connections on " << *this << "! Errno: " << std::to_string(errno);
      return false;
    }
    LOG_INFO << "Socket " << *this << " listening for new connections with max connections = " << iMaxConnNumber;
    return true;
  }
  LOG_ERROR << "You can only listen on TCP sockets";
  return false;
}

/**
 * @brief 
 * 
 * @param oSocket 
 * @param oSocketAddr 
 * 
 * @return true 
 */
bool ipc::ServerSocket::accept_connection(ClientSocket &oSocket, SocketAddress &oSocketAddr) {
  if (this->get_type() == SOCKET_TCP) {
    sockaddr_in addr;
    socklen_t addrSize = sizeof(addr);
    int sock = ::accept(this->get_sd(), (struct sockaddr*)&addr, &addrSize);
    LOG_INFO << "New incoming connection in " << sock;
    if (sock == -1) {
      LOG_ERROR << "Error on accepting connection on socket " << *this;
      return false;
    }
    oSocket.set_sd(sock);
    oSocketAddr = addr;
    LOG_INFO << "Accepted new connection on server socket " << *this << ". New client is set on client socket "
            << oSocket;
    return true;
  }
  LOG_ERROR << "You can only accept_connections on TCP sockets";
  return false;
}

/**
 * @brief 
 * 
 * @param iMessage 
 * @param iSize 
 * @param iClientSocket 
 * 
 * @return 
 */
bool ServerSocket::send_to(const void* iMessage, const size_t& iSize, const ClientSocket &iClientSocket) {
  if (!iClientSocket.is_open()) {
    LOG_ERROR << "Client socket on server side is closed";
    return false;
  }
  int bytesSent = 0;
  switch (this->get_type()) {
    case SOCKET_TCP: {
      bytesSent = ::send(iClientSocket, iMessage, iSize, 0);
      break;
    }
    case SOCKET_UDP: {
      sockaddr clientSockAddr = iClientSocket.get_addr();
      bytesSent = ::sendto(iClientSocket, iMessage, iSize, 0, &clientSockAddr, sizeof(clientSockAddr));
      break;
    }
    default: {
      LOG_ERROR << "Socket type " << this->get_type() << " not supported";
      return false;
      break;
    }
  }
  if (bytesSent < 0) {
    LOG_ERROR << "Error while sending message to " << iClientSocket << "! Errno: " << std::to_string(errno);
    return false;
  }
  LOG_INFO << "Successfully sent " << bytesSent << " bytes of data to " << iClientSocket;
  return true;
}

/**
 * @brief 
 * 
 * @param oMessage 
 * @param oSize 
 * @param iClientSocket 
 *  
 * @return 
 */
bool ServerSocket::recv_from(void *oMessage, size_t &oSize, const ClientSocket &iClientSocket) {
  if (!iClientSocket.is_open()) {
    LOG_ERROR << "Client socket on server side is closed";
  }
  if (!this->is_open()) {
    LOG_ERROR << "Client socket on server side is closed";
    return false;
  }
  int bytesRecv = 0;
  switch (this->get_type()) {
    case SOCKET_TCP: {
      bytesRecv = ::recv(iClientSocket, oMessage, oSize, 0);
      break;
    }
    case SOCKET_UDP: {
      sockaddr clientSockAddr = iClientSocket.get_addr();
      socklen_t clientAddrSize = sizeof(clientSockAddr);
      bytesRecv = ::recvfrom(iClientSocket, oMessage, oSize, 0, &clientSockAddr, &clientAddrSize);
      /* TODO:
      *   - Put the clientSockAddr into the iClientSocket once its transformed into ClientSocket.
      */
      break;
    }
    default: {
      LOG_ERROR << "Socket type " << this->get_type() << " not supported";
      return false;
      break;
    }
  }
  if (bytesRecv < 0) {
    LOG_ERROR << "Error while receiving message from " << iClientSocket << ". Received " << bytesRecv
              << " bytes! Errno: " << std::to_string(errno);       
    return false;
  }
  LOG_INFO << "Successfully received " << bytesRecv << " bytes of data from " << iClientSocket;
  return true;
}


} // namespace ipc