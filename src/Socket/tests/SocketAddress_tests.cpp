/**
 * @copyright Copyright (c) 2023
 * 
 * @author Hugo Fernandez Solis (hugofernandezsolis@gmail.com)
 * @date 02-12-2023
 * 
 * @file SocketAddress_tests.cpp
 * 
 * @brief 
 */


#include <gtest/gtest.h>

#include <arpa/inet.h>

#include <SocketAddress.h>


namespace ipc {


#define TEST_PORT     4096
#define TEST_PORT_BAD   -1
#define TEST_IP       "127.127.127.127"
#define TEST_IP_BAD   "127.127.127.927"


TEST(SocketAddress, Constructor) {
  LOG_INFO;
  SocketAddress addr0;
  EXPECT_EQ(addr0.get_port(), NO_PORT);
  EXPECT_EQ(addr0.get_ip(), NO_IP);

  SocketAddress addr1(TEST_PORT);
  EXPECT_EQ(addr1.get_port(), TEST_PORT);
  EXPECT_EQ(addr1.get_ip(), NO_IP);
  
  
  SocketAddress addr2(TEST_PORT, TEST_IP);
  EXPECT_EQ(addr2.get_port(), TEST_PORT);
  EXPECT_EQ(addr2.get_ip(), TEST_IP);
}

TEST(SocketAddress, SettersAndGetters) {
  SocketAddress addr;
  EXPECT_EQ(addr.get_port(), NO_PORT);
  EXPECT_EQ(addr.get_ip(), NO_IP);

  addr.set_port(TEST_PORT);
  EXPECT_EQ(addr.get_port(), TEST_PORT);
  EXPECT_EQ(addr.get_ip(), NO_IP);

  addr.set_ip(TEST_IP);
  EXPECT_EQ(addr.get_port(), TEST_PORT);
  EXPECT_EQ(addr.get_ip(), TEST_IP);

  addr.set_port(RANDOM_PORT);
  EXPECT_EQ(addr.get_port(), RANDOM_PORT);
  EXPECT_EQ(addr.get_ip(), TEST_IP);

  addr.set_ip(LOCAL_IP);
  EXPECT_EQ(addr.get_port(), RANDOM_PORT);
  EXPECT_EQ(addr.get_ip(), LOCAL_IP);
}

TEST(SocketAddress, ValidityChecks) {
  SocketAddress addr;
  EXPECT_FALSE(addr.is_valid());

  addr.set_port(TEST_PORT);
  EXPECT_TRUE(addr.has_valid_port());
  EXPECT_FALSE(addr.has_valid_ip());
  EXPECT_FALSE(addr.is_valid());

  addr.set_ip(TEST_IP);
  EXPECT_TRUE(addr.has_valid_port());
  EXPECT_TRUE(addr.has_valid_ip());
  EXPECT_TRUE(addr.is_valid());

  addr.set_port(TEST_PORT_BAD);
  EXPECT_FALSE(addr.has_valid_port());
  EXPECT_TRUE(addr.has_valid_ip());
  EXPECT_FALSE(addr.is_valid());

  addr.set_ip(TEST_IP_BAD);
  EXPECT_FALSE(addr.has_valid_port());
  EXPECT_FALSE(addr.has_valid_ip());
  EXPECT_FALSE(addr.is_valid());
}

TEST(SocketAddress, ConversionOperators) {
  SocketAddress addr(TEST_PORT, TEST_IP);
  sockaddr_in sockAddrIn = addr;
  port_t port = htons(sockAddrIn.sin_port);
  char ip[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &(sockAddrIn.sin_addr), ip, sizeof(ip));

  EXPECT_EQ(port, TEST_PORT);
  EXPECT_EQ(ip_t(ip), TEST_IP);

  sockaddr sockAddr = addr;
  inet_ntop(AF_INET, &((sockaddr_in*)&sockAddr)->sin_addr, ip, sizeof(ip));
  port = ntohs(((sockaddr_in*)&sockAddr)->sin_port);

  EXPECT_EQ(port, TEST_PORT);
  EXPECT_EQ(ip_t(ip), TEST_IP);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


} // namespace ipc
