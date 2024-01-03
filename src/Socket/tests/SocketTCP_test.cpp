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

#include "SocketAddress.h"
#include <gtest/gtest.h>

#include <arpa/inet.h>

#include <thread>

#include <SocketTCP.h>


namespace ipc {


TEST(SocketTCP, Constructor) {
	LOG_INFO;
	SocketTCP sock1;
	EXPECT_GT(sock1.get_sd(), -1);
	EXPECT_EQ(sock1.get_address(), SocketAddress());
	EXPECT_EQ(sock1.get_status(), STATUS_OPEN);

	int sd = socket(AF_INET, SOCK_STREAM, 0);
	SocketTCP sock2(sd);
	EXPECT_EQ(sock2.get_sd(), sd);
	EXPECT_EQ(sock2.get_address(), SocketAddress());
	EXPECT_EQ(sock2.get_status(), STATUS_OPEN);
}


TEST(SocketTCP, BindToAddress) {
	SocketTCP sock;
	SocketAddress addr1;
	EXPECT_FALSE(sock.bind_to(addr1));
	EXPECT_NE(sock.get_address(), addr1);

	SocketAddress addr2(8080, LOCAL_IP);
	EXPECT_TRUE(sock.bind_to(addr2));
	EXPECT_EQ(sock.get_address(), addr2);

	/* std::thread recvThread([recvSocket, sendSocket]() {
  }); */
}

TEST(SocketTCP, test) {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Error creating socket");
        return;
    }

    // Bind the socket to an address (you should replace this with your own binding code)
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(8080);

    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error binding socket");
        close(sockfd);
        return;
    }

    // Get the local address information
    struct sockaddr_in localAddr;
    socklen_t addrLen = sizeof(localAddr);
    if (getsockname(sockfd, (struct sockaddr*)&localAddr, &addrLen) == -1) {
        perror("Error getting socket name");
        close(sockfd);
        return;
    }

    // Convert the binary IP address to a human-readable string
    char ipStr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(localAddr.sin_addr), ipStr, INET_ADDRSTRLEN);

    // Print the local address and port
    std::cout << "Local Address: " << ipStr << std::endl;
    std::cout << "Local Port: " << ntohs(localAddr.sin_port) << std::endl;

		SocketTCP sock(sockfd);
		std::cout << "Addr: " << sock.get_address();

    // Don't forget to close the socket when you're done
    close(sockfd);

		EXPECT_EQ(1, 2);
}


} // namespace ipc
