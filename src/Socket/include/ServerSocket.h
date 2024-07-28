/**
 * @copyright Copyright (c) 2023
 * 
 * @author Hugo Fernandez Solis (hugofernandezsolis@gmail.com)
 * @date 02-12-2023
 * 
 * @file ServerSocket.h
 * 
 * @brief 
 */


#ifndef IPC_SERVER_SOCKET_H
#define IPC_SERVER_SOCKET_H


#include <logs.h>

#include <Socket.h>
#include <ClientSocket.h>


namespace ipc {   // Inter-Process Communication


/**
 * ServerSocket related types
 */


/**
 * ServerSocket related variables
 */


/**
 * @brief
 */
class ServerSocket : public Socket {
  public:
    /**
     * @brief
     * 
     */
    ServerSocket(void);
    /**
     * @brief 
     * 
     * @return 
     */
    [[nodiscard]] bool listen(const uint& iMaxConnNumber = 1024) const;

    /**
     * @brief 
     * 
     * @return
     */
    bool accept_connection(ClientSocket& oSocket, SocketAddress& oSocketAddr);

    /**
     * @brief
     * 
     * @return 
     */
    [[nodiscard]] bool send_to(const void* iMessage, const size_t& iSize, const ClientSocket &iClientSocket);

    /**
     * @brief
     * 
     * @return 
     */
    [[nodiscard]] bool recv_from(void* oMessage, size_t& oSize, const ClientSocket &iClientSocket);
};


} // namespace ipc


#endif // IPC_SERVER_SOCKET_H
