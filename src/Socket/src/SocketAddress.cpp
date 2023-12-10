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


/**
 * @brief Construct a new Socket Address object.
 * 
 * @param iPort The port number.
 * @param iIp The IP address.
 */
SocketAddress::SocketAddress(const port_t& iPort, const ip_t& iIp):
  port_(iPort), ip_(iIp) {}

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
  return this->has_valid_port() && this->has_valid_ip();
}

/**
 * @brief Checks if the port number is valid.
 * 
 * @return true if valid, false otherwise.
 */
bool SocketAddress::has_valid_port(void) const {
  return this->get_port() >= 0 && this->get_port() <= MAX_PORT;
}

/**
 * @brief Checks if the IP address is valid.
 * 
 * @return true if valid, false otherwise.
 */
bool SocketAddress::has_valid_ip(void) const {
  const std::regex ipRegex(
    R"(\b(?:25[0-5]|2[0-4][0-9]|[0-1]?[0-9]{1,2})(?:\.(?:25[0-5]|2[0-4][0-9]|[0-1]?[0-9]{1,2})){3}\b)");
  return std::regex_match(this->get_ip(), ipRegex);
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
