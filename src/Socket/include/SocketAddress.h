/**
 * @copyright Copyright (c) 2023
 * 
 * @author Hugo Fernandez Solis (hugofernandezsolis@gmail.com)
 * @date 02-12-2023
 * 
 * @file SocketAddress.h
 * 
 * @brief 
 */


#ifndef IPC_SOCKET_ADDRESS_H
#define IPC_SOCKET_ADDRESS_H


#include <string>
#include <iostream>


/**
 * SocketAddress related types
 */
typedef int port_t;            //
typedef std::string ip_t;       //


/**
 * SocketAddress related variables
 */
#define LOCAL_IP    "127.0.0.1"     //
#define NO_IP         "0.0.0.0"     //

#define NO_PORT          -1     //
#define RANDOM_PORT       0     //
#define MAX_PORT      65535     //


namespace ipc {


/**
 * @brief 
 * 
 */
class SocketAddress {
  public:
    SocketAddress(const port_t& iPort = RANDOM_PORT, const ip_t& iIp = LOCAL_IP);

    const port_t& get_port(void) const;
    const ip_t& get_ip(void) const;

    void set_port(const port_t& iNewPort);
    void set_ip(const ip_t& iNewIp);

    bool is_valid(void) const;
    bool has_valid_port(void) const;
    bool has_valid_ip(void) const;

    std::string to_string(void) const;
    
  private:
    port_t port_;
    ip_t ip_;

  friend std::ostream& operator<<(std::ostream& os, const SocketAddress& iAddr) {
    os << iAddr.to_string();
    return os;
  }
};


} // namespace ipc


#endif // IPC_SOCKET_ADDRESS_H
