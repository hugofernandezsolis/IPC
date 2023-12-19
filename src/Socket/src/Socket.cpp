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

#include <Socket.h>


namespace ipc {


Socket::Socket(const SocketAddress& iAddr): 
  sd_(-1), addr_(iAddr) {
  this->set_sd(socket(AF_INET, SOCK_STREAM, 0));
  bind(this->get_sd(), (struct sockaddr*)&this->get_addr(), sizeof(this->get_addr()));
}

Socket::Socket(const sd_t& iSd, const SocketAddress& iAddr):
  sd_(iSd), addr_(iAddr) {

}

const sd_t& Socket::get_sd(void) const {
  return this->sd_;
}

const SocketAddress& Socket::get_addr(void) const {
  return this->addr_;
}

void Socket::set_sd(const sd_t& iNewSd) {
  this->sd_ = iNewSd;
}

void Socket::set_addr(const sd_t& iNewAddr) {
  this->addr_ = iNewAddr;
}


} // namespace ipc
