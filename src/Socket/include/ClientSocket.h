/**
 * @copyright Copyright (c) 2023
 * 
 * @author Hugo Fernandez Solis (hugofernandezsolis@gmail.com)
 * @date 02-12-2023
 * 
 * @file ClientSocket.h
 * 
 * @brief 
 */


#ifndef IPC_CLIENT_SOCKET_H
#define IPC_CLIENT_SOCKET_H


#include <logs.h>

#include <Socket.h>


namespace ipc {   // Inter-Process Communication


/**
 * ClientSocket related types
 */


/**
 * ClientSocket related variables
 */


/**
 * @brief
 */
class ClientSocket : public Socket {
  public:
    /**
     * @brief
     */
    ClientSocket(const sd_t& iSd = -1);

    /**
     * @brief
     * 
     * @return 
     */
    [[nodiscard]] bool connect_to(const SocketAddress& iServerAddr);

    /**
     * @brief
     * 
     * @return 
     */
    [[nodiscard]] bool send(const void* iMessage, const size_t& iSize);

    /**
     * @brief
     * 
     * @return 
     */
    [[nodiscard]] bool recv(void* oMessage, size_t& oSize);

    /**
     * @brief Get the serverAddr object
     * 
     * @return const SocketAddress& 
     */
    const SocketAddress& get_serverAddr(void);

    /**
     * @brief Set the serverAddr object
     * 
     * @param iServerAddr 
     */
    void set_serverAddr(const sockaddr& iServerAddr);
  
  private:

  private:
    SocketAddress serverAddr_;
};


} // namespace ipc


#endif // IPC_CLIENT_SOCKET_H
