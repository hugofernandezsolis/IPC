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


#include <unistd.h>

#include <cstring>

#include <logs.h>
#include <SocketAddress.h>


namespace ipc {   // Inter-Process Communication


/**
 * Socket related types
 */
typedef int sd_t;             // Type definition for port numbers


/**
 * SocketTCP related variables
 */
enum socket_type {
  SOCKET_TCP = SOCK_STREAM,
  SOCKET_UDP = SOCK_DGRAM,
  ERROR_TYPE
};


/**
 * @brief Base class for sockets
 */
class Socket {
  public:
    /**
     * @brief Construct a new Socket
     */
    Socket(const sd_t& iSd = -1);

    /**
     * @brief
     * 
     * @return 
     */
    [[nodiscard]] bool open(const socket_type& iType = SOCKET_UDP);

    /**
     * @brief 
     * 
     * @return 
     */
    [[nodiscard]] bool bind(const SocketAddress& iNewAddr = {RANDOM_PORT, LOCAL_IP}) const;


    /**
     * @brief 
     * 
     * @return 
     */
    [[nodiscard]] bool close(void);

    /**
     * @brief 
     * 
     * @return
     */
    [[nodiscard]] bool is_open(void) const;
    
    /**
     * @brief 
     * 
     * @return
     */
    [[nodiscard]] socket_type get_type(void) const;

    /**
     * @brief Get the socket descriptor
     * 
     * @return The socket descriptor 
     */
    const sd_t& get_sd(void) const;

    /**
     * @brief Get the addr
     * 
     * @return The socket address
     */
    SocketAddress get_addr(void) const;

    /**
     * @brief Set a new socket descriptor. !! Take care. This won't close the previous socket descriptor.
     * 
     * @param iNewSd New socket descriptor to be set
     */
    void set_sd(const sd_t& iNewSd);

    /**
     * @brief Convert the socket to human readable format
     * 
     * @return String formatted socket info
     */
    std::string to_string(void) const;

    /**
     * @brief Destroy the Socket. !! This won't close the socket
     */
    ~Socket();

    /**
     * @brief 
     * 
     */
    const Socket& operator=(const sd_t& iNewSd);

    /**
     * @brief 
     * 
     */
    operator sd_t(void) const;

  protected:
    /**
     * @brief Get the socket descriptor
     * 
     * @return The socket descriptor 
     */
    sd_t& get_sd(void);

  private:
    sd_t sd_;

  /**
   * @brief Friend function to overload the output stream operator for easy printing.
   * 
   * @param os The output stream.
   * @param iSocket The Socket object.
   * @return std::ostream& The output stream.
   */
  friend std::ostream& operator <<(std::ostream& os, const Socket& iSocket) {
    os << iSocket.to_string();
    return os;
  }
};


/**
 * @brief 
 * 
 * @param os 
 * @param iSocket 
 * 
 * @return std::ostream& 
 */
/* std::ostream& operator <<(std::ostream& os, const socket_type& iSocketType) {
  switch (iSocketType) {
  case SOCKET_TCP:
    os << "SOCKET_TCP";
    break;
  case SOCKET_UDP:
    os << "SOCKET_UDP";
    break;
  default:
    os << "ERROR_TYPE";
    break;
  }
  return os;
} */


} // namespace ipc


#endif // IPC_SOCKET_H
