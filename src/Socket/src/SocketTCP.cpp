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


#include "logs.h"
#include <SocketTCP.h>

#include <cstring>
#include <functional>
#include <string>
#include <sys/socket.h>
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

bool SocketTCP::bind_to(const SocketAddress& iAddr) {
  sockaddr_in addr = iAddr;
  if (bind(this->get_sd(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1) {
    LOG_INFO << "Socket " << *this << " bound to " << iAddr;
    return true;
  }
  LOG_ERROR << "Couldn't bind socket " << *this << " to address " << iAddr;
  return false;
}

bool SocketTCP::send_message(const void* iMessage, const size_t& iSize) {
  int result = send(this->get_sd(), iMessage, iSize, 0);
  LOG_INFO << "Sent " << std::to_string(result) << " bytes out of " << std::to_string(iSize);
  return result == -1;
}

bool SocketTCP::receive_message(void* iMessage, size_t& iSize) {
  memset(iMessage, 0, iSize);
  int result = recv(this->get_sd(), iMessage, iSize, 0);
  LOG_INFO << "Received " << std::to_string(result) << "bytes of data";
  iSize = result;
  return result != -1;
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
  if (getsockopt(this->get_sd(), SOL_SOCKET, SO_REUSEADDR, &opt, &size) != -1 && opt) {
    LOG_INFO << "Socket " << *this << " is listening for connections";
    return STATUS_LISTENING;
  }
  if (getsockopt(this->get_sd(), SOL_SOCKET, SO_ACCEPTCONN, &opt, &size) != -1 && opt) {
    LOG_INFO << "Socket " << *this << " is bound to an address";
    return STATUS_BOUND;
  }
  if (getsockopt(this->get_sd(), SOL_SOCKET, SO_ERROR, &opt, &size) != -1 && !opt) {
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
