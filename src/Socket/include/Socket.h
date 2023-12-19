/**
 * @copyright Copyright (c) 2023
 * 
 * @author Hugo Fernandez Solis (hugofernandezsolis@gmail.com)
 * @date 02-12-2023
 * 
 * @file Socket.h
 * 
 * @brief 
 */


#ifndef IPC_SOCKET_H
#define IPC_SOCKET_H


#include <SocketAddress.h>


namespace ipc {   // Inter-Process Communication


/**
 * Socket related types
 */
typedef int sd_t;             // Type definition for port numbers


/**
 * Socket related variables
 */


/**
 * @brief 
 * 
 */
class Socket {
  public:
    // Constructor with default parameter
    Socket(const SocketAddress& iAddr = {});

    // Constructor with socket descriptor and socket address parameters
    Socket(const sd_t& iSd, const SocketAddress& iAddr = {});

    // Getter method for socket descriptor
    const sd_t& get_sd(void) const;

    // Getter method for socket address
    const SocketAddress& get_addr(void) const;

    // Setter method for socket descriptor
    void set_sd(const sd_t& iNewSd);

    // Setter method for socket address
    void set_addr(const sd_t& iNewAddr);

  private:
    // Member variables
    sd_t sd_;
    SocketAddress addr_;
};


}


#endif // IPC_SOCKET_H
