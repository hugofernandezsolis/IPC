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


#include <arpa/inet.h>

#include <regex>

#include <SocketAddress.h>


namespace ipc {


/**
 * @brief Construct a new Socket Address object.
 * 
 * @param iPort The port number.
 * @param iIp The IP address.
 */
SocketAddress::SocketAddress(const port_t& iPort, const ip_t& iIp):
  port_(iPort), ip_(iIp) {}

/**
 * @brief Construct a new Socket Address object.
 * 
 * @param iAddr The socket address.
 */
SocketAddress::SocketAddress(const sockaddr_in& iAddr) {
  this->set_port(htons(iAddr.sin_port));
  char ip[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &(iAddr.sin_addr), ip, sizeof(ip));
  this->set_ip(ip);
}

/**
 * @brief Gets the port number.
 * 
 * @return The port number.
 */
const port_t& SocketAddress::get_port(void) const {
  return this->port_;
}

/**
 * @brief Gets the IP address.
 * 
 * @return The IP address.
 */
const ip_t& SocketAddress::get_ip(void) const {
  return this->ip_;
}

/**
 * @brief Sets the port number.
 * 
 * @param iNewPort The new port number.
 */
void SocketAddress::set_port(const port_t& iNewPort) {
  this->port_ = iNewPort;
}

/**
 * @brief Sets the IP address.
 * 
 * @param iNewIp The new IP address.
 */
void SocketAddress::set_ip(const ip_t& iNewIp) {
  this->ip_ = iNewIp;
}

/**
 * @brief Checks if the SocketAddress is valid.
 * 
 * @return true if valid, false otherwise.
 */
bool SocketAddress::is_valid(void) const {
  if(this->has_valid_port() && this->has_valid_ip()) {
    LOG_INFO << "Address " << *this << " is valid";
    return true;
  }
  LOG_INFO << "Address " << *this << " is not valid";
  return false;
}

/**
 * @brief Checks if the port number is valid.
 * 
 * @return true if valid, false otherwise.
 */
bool SocketAddress::has_valid_port(void) const {
  if (this->get_port() >= 0 && this->get_port() <= MAX_PORT) {
    LOG_INFO << "Address " << *this << " has a valid port: " << std::to_string(this->get_port());
    return true;
  }
  LOG_INFO << "Address " << *this << " has a not valid port: " << std::to_string(this->get_port());
  return false;
}

/**
 * @brief Checks if the IP address is valid.
 * 
 * @return true if valid, false otherwise.
 */
bool SocketAddress::has_valid_ip(void) const {
  const std::regex ipRegex(
    R"(\b(?:25[0-5]|2[0-4][0-9]|[0-1]?[0-9]{1,2})(?:\.(?:25[0-5]|2[0-4][0-9]|[0-1]?[0-9]{1,2})){3}\b)");
  if (std::regex_match(this->get_ip(), ipRegex)) {
    LOG_INFO << "Address " << *this << " has a valid ip: " << this->get_ip();
    return true;
  }
  LOG_INFO << "Address " << *this << " has a not valid port: " << this->get_ip();
  return false;
}

/**
 * @brief Converts the SocketAddress object to a sockaddr_in structure.
 * 
 * This conversion operator allows seamless integration with networking functions
 * that use the sockaddr_in structure.
 * 
 * @return sockaddr_in The sockaddr_in structure representing the SocketAddress.
 */
SocketAddress::operator sockaddr_in(void) const {
  sockaddr_in socketAddress {};
  socketAddress.sin_family = AF_INET;
  inet_pton(AF_INET, this->get_ip().c_str(), &(socketAddress.sin_addr));
  socketAddress.sin_port = htons(this->get_port());
  return socketAddress;
}

/**
 * @brief Converts the SocketAddress object to a sockaddr_in structure.
 * 
 * This conversion operator allows seamless integration with networking functions
 * that use the sockaddr_in structure.
 * 
 * @return sockaddr_in The sockaddr_in structure representing the SocketAddress.
 */
SocketAddress::operator sockaddr(void) const {
  sockaddr_in sockaddrIn = *this;
  sockaddr sockaddrGeneric = {};
  std::memcpy(&sockaddrGeneric, &sockaddrIn, sizeof(sockaddrIn));
  return sockaddrGeneric;
}

/**
 * @brief Converts the SocketAddress to a string.
 * 
 * @return The string representation of the SocketAddress.
 */
std::string SocketAddress::to_string(void) const {
  return this->get_ip() + ':' + std::to_string(this->get_port());
}


} // namespace ipc
