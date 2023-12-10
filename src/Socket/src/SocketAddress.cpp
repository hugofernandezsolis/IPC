/**
 * @copyright Copyright (c) 2023
 * 
 * @author Hugo Fernandez Solis (hugofernandezsolis@gmail.com)
 * @date 02-12-2023
 * 
 * @file SocketAddress.cpp
 * 
 * @brief 
 */


#include <regex>

#include <SocketAddress.h>


namespace ipc {


SocketAddress::SocketAddress(const port_t& iPort, const ip_t& iIp):
  port_(iPort), ip_(iIp) {}

const port_t& SocketAddress::get_port(void) const {
  return this->port_;
}

const ip_t& SocketAddress::get_ip(void) const {
  return this->ip_;
}

void SocketAddress::set_port(const port_t& iNewPort) {
  this->port_ = iNewPort;
}

void SocketAddress::set_ip(const ip_t& iNewIp) {
  this->ip_ = iNewIp;
}

bool SocketAddress::is_valid(void) const {
  return this->has_valid_port() && this->has_valid_ip();
}

bool SocketAddress::has_valid_port(void) const {
  return this->get_port() >= 0 && this->get_port() <= MAX_PORT;
}

bool SocketAddress::has_valid_ip(void) const {
  const std::regex ipRegex(
    R"(\b(?:25[0-5]|2[0-4][0-9]|[0-1]?[0-9]{1,2})(?:\.(?:25[0-5]|2[0-4][0-9]|[0-1]?[0-9]{1,2})){3}\b)");
  return std::regex_match(this->get_ip(), ipRegex);
}

std::string SocketAddress::to_string(void) const {
  return this->get_ip() + ':' + std::to_string(this->get_port());
}


} // namespace ipc
