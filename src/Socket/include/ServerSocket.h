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


#ifndef IPC_SERVER_SOCKET_H
#define IPC_SERVER_SOCKET_H


#include <logs.h>

#include <SocketTCP.h>


namespace ipc {   // Inter-Process Communication


/**
 * Socket related types
 */


/**
 * Socket related variables
 */


/**
 * @brief 
 * 
 */
class ServerSocket : public SocketTCP {
  public:
    // Constructor with socket descriptor and socket address parameters
    ServerSocket(void);

    bool bind_to(const SocketAddress& iAddr) const;

    bool start_listening(const uint& iMaxConnNumber) const;

    bool accept_connection(SocketTCP& oSocket, SocketAddress& oSocketAddr) const;
};


}


#endif // IPC_SERVER_SOCKET_H
