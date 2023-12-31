/**
 * @copyright Copyright (c) 2023
 * 
 * @author Hugo Fernandez Solis (hugofernandezsolis@gmail.com)
 * @date 02-12-2023
 * 
 * @file SocketTCP.h
 * 
 * @brief 
 */


#ifndef IPC_SOCKET_H
#define IPC_SOCKET_H


#include <cstddef>
#include <logs.h>

#include <SocketAddress.h>


namespace ipc {   // Inter-Process Communication


/**
 * SocketTCP related types
 */
typedef int sd_t;             // Type definition for port numbers


/**
 * SocketTCP related variables
 */
enum socket_status_e {
  STATUS_UNDEFINED,
  STATUS_OPEN,
  STATUS_BOUND,
  STATUS_LISTENING,
  STATUS_ERROR
};


/**
 * @brief 
 * 
 */
class SocketTCP {
  public:
    SocketTCP(const sd_t& iSd = -1);

    bool bind_to(const SocketAddress& iAddr);

    bool send_message(const void* iMessage, const size_t& iSize);

    bool receive_message(void* iMessage, size_t& iSize);

    socket_status_e get_status(void) const;

    SocketAddress get_address(void) const;

    const sd_t& get_sd(void) const;

    void set_sd(const sd_t& iNewSd);

    std::string to_string(void) const;

    ~SocketTCP();

  private:
    // Member variables
    sd_t sd_;
    SocketAddress addr_;

  /**
   * @brief Friend function to overload the output stream operator for easy printing.
   * 
   * @param os The output stream.
   * @param iSocket The Socket object.
   * @return std::ostream& The output stream.
   */
  friend std::ostream& operator <<(std::ostream& os, const SocketTCP& iSocket) {
    os << iSocket.to_string();
    return os;
  }
};


}


#endif // IPC_SOCKET_H
