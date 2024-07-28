/**
 * @copyright Copyright (c) 2023
 * 
 * @author Hugo Fernandez Solis (hugofernandezsolis@gmail.com)
 * @date 02-12-2023
 * 
 * @file ClientSocket.cpp
 * 
 * @brief 
 */


#include <ClientSocket.h>


namespace ipc {   // Inter-Process Communication


/**
 * @brief
 * 
 */
ClientSocket::ClientSocket(const sd_t& iSd):
  Socket(iSd) {}

/**
 * @brief 
 * 
 * @param iServerAddr 
 * 
 * @return false 
 */
bool ClientSocket::connect_to(const SocketAddress &iServerAddr) {
  if (this->get_type() != SOCKET_TCP) {
    LOG_ERROR << "You can only connect TCP sockets to a server!";
    return false;
  }
  sockaddr addr = iServerAddr;
  if (connect(this->get_sd(), &addr, sizeof(addr)) < 0) {
    LOG_ERROR << "Unable to connect to server " << iServerAddr << "! Errno: " << std::to_string(errno);;
    return false;
  }
  this->set_serverAddr(addr);
  LOG_INFO << "Successfully connected to server " << iServerAddr;
  return true;
}

/**
 * @brief 
 * 
 * @param iMessage 
 * @param iSize 
 * 
 * @return false 
 */
bool ClientSocket::send(const void *iMessage, const size_t &iSize) {
  if (!this->is_open()) {
    LOG_ERROR << "Socket must be open first!";
    return false;
  }
  int bytesSent = 0;
  switch (this->get_type()) {
    case SOCKET_TCP: {
      bytesSent = ::send(this->get_sd(), iMessage, iSize, 0);
      break;
    }
    case SOCKET_UDP: {
      sockaddr serverSockAddr = this->get_serverAddr();
      bytesSent = ::sendto(this->get_sd(), iMessage, iSize, 0, &serverSockAddr, sizeof(serverSockAddr));
      break;
    }
    default: {
      LOG_ERROR << "Socket type " << this->get_type() << " not supported";
      return false;
      break;
    }
  }
  if (bytesSent < 0) {
    LOG_ERROR << "Error while sending message to " << this->get_serverAddr() << "! Errno: " << std::to_string(errno);
    return false;
  }
  LOG_INFO << "Successfully sent " << bytesSent << " bytes of data to " << this->get_serverAddr();
  return true;
}

/**
 * @brief 
 * 
 * @param oMessage 
 * @param oSize 
 * 
 * @return false 
 */
bool ClientSocket::recv(void *oMessage, size_t &oSize) {
  if (!this->is_open()) {
    LOG_ERROR << "Socket must be open first!";
    return false;
  }
  int bytesRecv = -1;
  switch (this->get_type()) {
    case SOCKET_TCP: {
      bytesRecv = ::recv(this->get_sd(), oMessage, oSize, 0);
      break;
    }
    case SOCKET_UDP: {
      sockaddr serverSockAddr = this->get_serverAddr();
      socklen_t clientAddrSize = sizeof(serverSockAddr);
      bytesRecv = ::recvfrom(this->get_sd(), oMessage, oSize, 0, &serverSockAddr, &clientAddrSize);
      /* TODO:
      *   - Put the serverSockAddr into the iClientSocket once its transformed into ClientSocket.
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
    LOG_ERROR << "Error while receiving message from " << this->get_serverAddr() << "! Errno: " << std::to_string(errno);       
    return false;
  }
  LOG_INFO << "Successfully received " << bytesRecv << " bytes of data from " << this->get_serverAddr();
  return true;
}

/**
 * @brief 
 * 
 * @return SocketAddress 
 */
const SocketAddress& ClientSocket::get_serverAddr(void) {
  return this->serverAddr_;
}

/**
 * @brief 
 * 
 * @param iServerAddr 
 */
void ClientSocket::set_serverAddr(const sockaddr &iServerAddr) {
  this->serverAddr_ = *(reinterpret_cast<sockaddr_in*>(const_cast<sockaddr*>(&iServerAddr)));
}


} // namespace ipc