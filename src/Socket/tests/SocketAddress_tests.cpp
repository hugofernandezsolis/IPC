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

#include <SocketAddress.h>


namespace ipc {


#define TEST_PORT     4096
#define TEST_PORT_BAD   -1
#define TEST_IP       "127.127.127.127"
#define TEST_IP_BAD   "127.127.127.927"


TEST(SocketAddress, Constructor) {
  SocketAddress addr0;
  EXPECT_EQ(addr0.get_port(), RANDOM_PORT);
  EXPECT_EQ(addr0.get_ip(), LOCAL_IP);

  SocketAddress addr1(TEST_PORT);
  EXPECT_EQ(addr1.get_port(), TEST_PORT);
  EXPECT_EQ(addr1.get_ip(), LOCAL_IP);
  
  
  SocketAddress addr2(TEST_PORT, TEST_IP);
  EXPECT_EQ(addr2.get_port(), TEST_PORT);
  EXPECT_EQ(addr2.get_ip(), TEST_IP);
}

TEST(SocketAddress, SettersAndGetters) {
  SocketAddress addr;
  EXPECT_EQ(addr.get_port(), RANDOM_PORT);
  EXPECT_EQ(addr.get_ip(), LOCAL_IP);

  addr.set_port(TEST_PORT);
  EXPECT_EQ(addr.get_port(), TEST_PORT);
  EXPECT_EQ(addr.get_ip(), LOCAL_IP);

  addr.set_ip(TEST_IP);
  EXPECT_EQ(addr.get_port(), TEST_PORT);
  EXPECT_EQ(addr.get_ip(), TEST_IP);

  addr.set_port(RANDOM_PORT);
  EXPECT_EQ(addr.get_port(), RANDOM_PORT);
  EXPECT_EQ(addr.get_ip(), TEST_IP);

  addr.set_ip(NO_IP);
  EXPECT_EQ(addr.get_port(), RANDOM_PORT);
  EXPECT_EQ(addr.get_ip(), NO_IP);
}

TEST(SocketAddress, ValidityChecks) {
  SocketAddress addr;
  EXPECT_TRUE(addr.is_valid());

  addr.set_port(TEST_PORT_BAD);
  EXPECT_FALSE(addr.has_valid_port());
  EXPECT_TRUE(addr.has_valid_ip());
  EXPECT_FALSE(addr.is_valid());

  addr.set_ip(TEST_IP_BAD);
  EXPECT_FALSE(addr.has_valid_port());
  EXPECT_FALSE(addr.has_valid_ip());
  EXPECT_FALSE(addr.is_valid());

  addr.set_port(TEST_PORT);
  EXPECT_TRUE(addr.has_valid_port());
  EXPECT_FALSE(addr.has_valid_ip());
  EXPECT_FALSE(addr.is_valid());

  addr.set_ip(TEST_IP);
  EXPECT_TRUE(addr.has_valid_port());
  EXPECT_TRUE(addr.has_valid_ip());
  EXPECT_TRUE(addr.is_valid());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


} // namespace ipc
