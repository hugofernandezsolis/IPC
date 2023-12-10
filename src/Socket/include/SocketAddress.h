/**
 * @copyright Copyright (c) 2023
 * 
 * @author Hugo Fernandez Solis (hugofernandezsolis@gmail.com)
 * @date 02-12-2023
 * 
 * @file SocketAddress.h
 * 
 * @brief Defines the SocketAddress class for handling IP addresses and ports.
 */


#ifndef IPC_SOCKET_ADDRESS_H
#define IPC_SOCKET_ADDRESS_H


#include <string>
#include <iostream>


/**
 * SocketAddress related types
 */
typedef int port_t;             // Type definition for port numbers
typedef std::string ip_t;       // Type definition for IP addresses


/**
 * SocketAddress related variables
 */
#define LOCAL_IP    "127.0.0.1"     // Localhost IP address
#define NO_IP         "0.0.0.0"     // No specific IP address

#define NO_PORT          -1     // No specific port
#define RANDOM_PORT       0     // Use a random port
#define MAX_PORT      65535     // Maximum allowed port number


namespace ipc {   // Inter-Process Communication


/**
 * @brief Represents a socket address with an IP and port.
 */
class SocketAddress {
  public:
    /**
     * @brief Construct a new Socket Address object.
     * 
     * @param iPort The port number.
     * @param iIp The IP address.
     */
    SocketAddress(const port_t& iPort = RANDOM_PORT, const ip_t& iIp = LOCAL_IP);

    /**
     * @brief Gets the port number.
     * 
     * @return The port number.
     */
    const port_t& get_port(void) const;

    /**
     * @brief Gets the IP address.
     * 
     * @return The IP address.
     */
    const ip_t& get_ip(void) const;

    /**
     * @brief Sets the port number.
     * 
     * @param iNewPort The new port number.
     */
    void set_port(const port_t& iNewPort);

    /**
     * @brief Sets the IP address.
     * 
     * @param iNewIp The new IP address.
     */
    void set_ip(const ip_t& iNewIp);

    /**
     * @brief Checks if the SocketAddress is valid.
     * 
     * @return true if valid, false otherwise.
     */
    bool is_valid(void) const;

    /**
     * @brief Checks if the port number is valid.
     * 
     * @return true if valid, false otherwise.
     */
    bool has_valid_port(void) const;

    /**
     * @brief Checks if the IP address is valid.
     * 
     * @return true if valid, false otherwise.
     */
    bool has_valid_ip(void) const;

    /**
     * @brief Converts the SocketAddress to a string.
     * 
     * @return The string representation of the SocketAddress.
     */
    std::string to_string(void) const;
    
  private:
    port_t port_;   // The port number
    ip_t ip_;       // The IP address

  /**
   * @brief Friend function to overload the output stream operator for easy printing.
   * 
   * @param os The output stream.
   * @param iAddr The SocketAddress object.
   * @return std::ostream& The output stream.
   */
  friend std::ostream& operator<<(std::ostream& os, const SocketAddress& iAddr) {
    os << iAddr.to_string();
    return os;
  }
};


} // namespace ipc


#endif // IPC_SOCKET_ADDRESS_H
