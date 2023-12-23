/**
 * @copyright Copyright (c) 2023
 * 
 * @author Hugo Fernandez Solis (hugofernandezsolis@gmail.com)
 * @date 02-12-2023
 * 
 * @file Socket.cpp
 * 
 * @brief 
 */


#include <SocketTCP.h>

#include <unistd.h>


namespace ipc {


SocketTCP::SocketTCP(const sd_t& iSd):
  sd_(iSd) {
  if (this->get_sd() < 0) {
    this->set_sd(socket(AF_INET, SOCK_STREAM, 0));
  }
  this->get_sd() == -1 ?
    LOG_ERROR << "Unable to open socket with errno: " << std::to_string(errno) :
    LOG_INFO << "New socket created: " << *this;
}

SocketAddress SocketTCP::get_address(void) const {
  sockaddr_in socketAddress;
  socklen_t addrSize = sizeof(socketAddress);
  if (getsockname(this->get_sd(), reinterpret_cast<sockaddr*>(&socketAddress), &addrSize) == -1) {
    LOG_ERROR << "Unable to retrieve address for socket " << *this << ". Returning empty address instead"; 
  }
  return socketAddress;
}

socket_status_e SocketTCP::get_status(void) const {
  int opt = 0;
  socklen_t size = sizeof(opt);
  if (getsockopt(this->get_sd(), SOL_SOCKET, SO_REUSEADDR, &opt, &size) && opt) {
    LOG_INFO << "Socket " << *this << " is listening for connections";
    return STATUS_LISTENING;
  }
  if (getsockopt(this->get_sd(), SOL_SOCKET, SO_ACCEPTCONN, &opt, &size) && opt) {
    LOG_INFO << "Socket " << *this << " is bound to an address";
    return STATUS_BOUND;
  }
  if (getsockopt(this->get_sd(), SOL_SOCKET, SO_ERROR, &opt, &size) && !opt) {
    LOG_INFO << "Socket " << *this << " is open";
    return STATUS_OPEN;
  }
  LOG_INFO << "Socket " << *this << " is not opened";
  return STATUS_ERROR;
}

const sd_t& SocketTCP::get_sd(void) const {
  return this->sd_;
}

void SocketTCP::set_sd(const sd_t& iNewSd) {
  this->sd_ = iNewSd;
}

std::string SocketTCP::to_string(void) const {
  return std::to_string(this->get_sd());
}

SocketTCP::~SocketTCP() {
  close(this->get_sd());
}


} // namespace ipc
