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

#include <unistd.h>


namespace ipc {


ServerSocket::ServerSocket(void):
  SocketTCP(-1) {}

bool ServerSocket::bind_to(const SocketAddress& iAddr) const {
  if (!iAddr.is_valid()) {
    LOG_ERROR << "Unable to bind socket " << *this << " to invalid address " << iAddr;
    return false;
  }
  const sockaddr addr = iAddr;
  if (bind(this->get_sd(), &addr, sizeof(addr)) == -1) {
    LOG_ERROR << "Error on binding socket " << *this << " to address " << iAddr
             << " with errno: " << std::to_string(errno);
    return false;
  }
  LOG_INFO << "Socket " << *this << " successfully bound to address " << iAddr;
  return true; 
}

bool ServerSocket::start_listening(const uint& iMaxConnNumber) const {
  if (listen(this->get_sd(), iMaxConnNumber) == -1) {
    LOG_ERROR << "Error listening for connections on " << *this << " with errno: " << std::to_string(errno) ;
    return false;
  }
  LOG_INFO << "Socket " << *this << " listening for new connections on " << this->get_address()
           << " with max connections = " << iMaxConnNumber;
  return true;
}

bool ServerSocket::accept_connection(SocketTCP& oClientSocket, SocketAddress& oClientSocketAddr) const {
  sockaddr_in addr;
  socklen_t addrSize = sizeof(addr);
  int sock = accept(this->get_sd(), reinterpret_cast<sockaddr*>(&addr), &addrSize);
  if (sock == -1) {
    LOG_ERROR << "Error on accepting connection on socket " << *this;
    return false;
  }
  oClientSocket = sock;
  oClientSocketAddr = addr;
  LOG_INFO << "Accepted new connection on server socket " << *this << ". New client is set on client socket "
           << oClientSocket << " with address " << oClientSocketAddr;
  return true;
}


} // namespace ipc