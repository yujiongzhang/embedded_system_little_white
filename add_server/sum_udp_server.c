
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "sum_message.h"

#define PORT 8080
#define BUFFER_SIZE sizeof(MessageSum)

typedef int (*calculatefunction)(int a, int b);

//task2： 加减乘除 4 个 服务
int calc_add(int a, int b) {
    return a + b;
}

int calc_sub(int a, int b) {
    return a - b;
}

int calc_multi(int a, int b) {
    return a * b;
}

int calc_div(int a, int b) {
    return (b != 0) ? a / b : 0;  // 防止除以0
}
calculatefunction calculatable[] = {
    calc_add,
    calc_sub,
    calc_multi,
    calc_div
};


int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    MessageSum m_msg;
    int sum;

    // 创建 UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 配置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 绑定 socket
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("UDP Server is running on port %d...\n", PORT);

    while (1) {
        // 接收两个整数（打包在缓冲区中）
        int recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                                (struct sockaddr *)&client_addr, &client_len);
        if (recv_len != BUFFER_SIZE) {
            fprintf(stderr, "Received unexpected data length: %d\n", recv_len);
            continue;
        }

        // 将接收到的数据复制到整数数组中（注意字节序问题）
        memcpy(&m_msg, buffer, BUFFER_SIZE);

        // 计算和
        if (m_msg.head == 0xa5)
        {
            if(m_msg.sum == (m_msg.head + m_msg.number1 + m_msg.number2 + m_msg.mode)){
                int result = calculatable[m_msg.mode](m_msg.number1, m_msg.number2);

                // 发送结果回客户端
                sendto(sockfd, &result, sizeof(sum), 0,
                    (const struct sockaddr *)&client_addr, client_len);
            }
            else{
                printf("sum error");
            }
        }
        else{
            printf("header error");
        }
    }

    close(sockfd);
    return 0;
}