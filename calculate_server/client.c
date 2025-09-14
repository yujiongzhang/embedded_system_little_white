
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "sum_message.h"

#define PORT 8080
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE sizeof(MessageSum)

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    MessageSum m_msg = {
        .head = 0xa5,
        .calculate_mode = CALC_MODE_SUB,
        .number1 = 11,
        .number2 = 12,
        .sum = 0
    };
    m_msg.sum = m_msg.head + m_msg.calculate_mode + m_msg.number1 + m_msg.number2;

    int result;
    // 创建 UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    // 打包两个整数并发送
    memcpy(buffer, &m_msg, BUFFER_SIZE);
    sendto(sockfd, buffer, BUFFER_SIZE, 0,
           (const struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Sent: %d and %d\n", m_msg.number1, m_msg.number2);

    // 接收结果
    recvfrom(sockfd, &result, sizeof(result), 0, NULL, NULL);

    printf("Result from server: %d\n", result);

    close(sockfd);
    return 0;
}