/**
 * @copyright Copyright (c) 2023
 * 
 * @author Hugo Fernandez Solis (hugofernandezsolis@gmail.com)
 * @date 02-12-2023
 * 
 * @file Socket.cpp
 * 
 * @brief 
 */


#include <Socket.h>

#include <arpa/inet.h>


namespace ipc {   // Inter-Process Communication


/**
 * @brief Construct a new Socket
 */
Socket::Socket(const sd_t& iSd) {
  this->set_sd(iSd);
}

/**
 * @brief 
 * 
 * @return
 */
bool Socket::open(const socket_type& iSocketType) {
  if (this->is_open()) {
    LOG_WARNING << "Trying to open an already open socket " << *this;
    return true;
  }
  this->set_sd(::socket(AF_INET, iSocketType, 0));
  if (this->get_sd() < 0) {
    LOG_ERROR << "Unexpected error while trying to open new socket" << "! Errno: " << std::to_string(errno);
    return false;
  }
  LOG_INFO << "New socket opened " << *this;
  return true;
}

/**
 * @brief 
 * 
 * @param iNewAddr 
 * 
 * @return 
 */
bool Socket::bind(const SocketAddress &iNewAddr) const {
  const sockaddr addr = iNewAddr;
  if (::bind(this->get_sd(), &addr, sizeof(addr)) < 0) {
    LOG_ERROR << "Unexpected error while trying to bind socket " << *this << " to address " << iNewAddr << "! Errno: "
              << std::to_string(errno);
    return false;
  }
  LOG_INFO << "Socket " << *this << " bound correctly to it's new address";
  return true;
}

/**
 * @brief 
 * 
 * @return
 */
bool Socket::close(void) {
  if (!this->is_open()) {
    LOG_WARNING << "Socket already closed!";
    return true;
  }
  if (::close(this->get_sd())) {
    LOG_INFO << "Closed socket " << this->get_sd();
    this->set_sd(-1);
    return true;
  }
  LOG_ERROR << "Unexpected error while trying to close socket " << *this << "! Errno: " << std::to_string(errno);
  return false;
}

/**
 * @brief 
 * 
 * @return
 */
bool Socket::is_open(void) const {
  int error = 0;
  socklen_t len = sizeof(error);
  int retval = getsockopt(this->get_sd(), SOL_SOCKET, SO_ERROR, &error, &len);
  return ((retval == 0) && (error == 0));
}

/**
 * @brief 
 * 
 * @return
 */
socket_type Socket::get_type(void) const {
  socket_type type;
  socklen_t length = sizeof(type);
  if (getsockopt(this->get_sd(), SOL_SOCKET, SO_TYPE, &type, &length) == -1) {
    LOG_ERROR << "Unexpected error while trying to retrieve the socket type of socket " << *this;
    return SOCKET_ERROR;
  }
  return type;
}

/**
 * @brief Get the socket descriptor
 * 
 * @return The socket descriptor 
 */
const sd_t& Socket::get_sd(void) const {
  return this->sd_;
}

/**
 * @brief Get the addr
 * 
 * @return The socket address
 */
SocketAddress Socket::get_addr(void) const {
  struct sockaddr_in auxAddr;
  socklen_t addr_len = sizeof(auxAddr);
  if (getsockname(this->get_sd(), (struct sockaddr*)&auxAddr, &addr_len) == -1) {
    //LOG_ERROR << "Unable to retrieve address for socket " << *this;
    return {BAD_PORT, NO_IP};
  }
  return auxAddr;
}

/**
 * @brief Set a new socket descriptor. !! Take care. This won't close the previous socket descriptor.
 * 
 * @param iNewSd New socket descriptor to be set
 */
void Socket::set_sd(const sd_t& iNewSd) {
  this->sd_ = iNewSd;
}

/**
 * @brief Convert the socket to human readable format
 * 
 * @return String formatted socket info
 */
std::string Socket::to_string(void) const {
  return std::to_string(this->get_sd()) + "-(" + this->get_addr().to_string() + ')';
}

/**
 * @brief Destroy the Socket. !! This won't close the socket
 */
Socket::~Socket() {
  LOG_INFO << "Closed socket " << *this;
  ::close(this->get_sd());
}

/**
 * @brief Get the socket descriptor
 * 
 * @return The socket descriptor 
 */
sd_t& Socket::get_sd(void) {
  return this->sd_;
}

/**
 * @brief 
 * 
 */
const Socket& Socket::operator=(const sd_t& iNewSd) {
  this->set_sd(iNewSd);
  return *this;
}

/**
 * @brief Construct a new Socket::operator sd_t object
 * 
 */
Socket::operator sd_t(void) const {
  return this->get_sd();
}


} // namespace ipc
