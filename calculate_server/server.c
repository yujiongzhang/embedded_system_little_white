
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "sum_message.h"

#define PORT 8080
#define BUFFER_SIZE sizeof(MessageSum)

#include <stdint.h>

// 定义计算函数的类型：接收两个 uint16_t，返回 uint16_t
typedef int16_t (*CalcFunc)(uint16_t a, uint16_t b);

// 实现各个运算函数
int16_t calc_add(uint16_t a, uint16_t b) {
    return a + b;
}

int16_t calc_sub(uint16_t a, uint16_t b) {
    return a - b;
}

int16_t calc_multi(uint16_t a, uint16_t b) {
    return a * b;
}

int16_t calc_div(uint16_t a, uint16_t b) {
    return (b != 0) ? (a / b) : 0;  // 防止除零
}

// 查表法：索引对应 calculate_mode 的值（注意从 1 开始）
CalcFunc calc_table[] = {
    NULL,           // 0: 保留，不使用
    calc_add,       // 1: CALC_MODE_ADD
    calc_sub,       // 2: CALC_MODE_SUB
    calc_multi,     // 3: CALC_MODE_MULTI
    calc_div        // 4: CALC_MODE_DIV
};

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    MessageSum m_msg;
    int result;

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

        if (m_msg.head == 0xa5) // 计算头
        {
            if(m_msg.sum == (m_msg.head + m_msg.calculate_mode + m_msg.number1 + m_msg.number2)){ // 校验位
                // switch (m_msg.calculate_mode)
                // {
                // case CALC_MODE_ADD:
                //     result = m_msg.number1 + m_msg.number2;
                //     break;
                // case CALC_MODE_SUB:
                //     result = m_msg.number1 - m_msg.number2;
                //     break;
                // case CALC_MODE_MULTI:
                //     result = m_msg.number1 * m_msg.number2;
                //     break;
                // case CALC_MODE_DIV:
                //     result = m_msg.number1 / m_msg.number2;
                //     break;
                // default:
                //     break;
                // }

                result = calc_table[m_msg.calculate_mode](m_msg.number1, m_msg.number2);
                
                printf("Received: %d + %d = %d\n", m_msg.number1, m_msg.number2, result);

                // 发送结果回客户端
                sendto(sockfd, &result, sizeof(result), 0,
                    (const struct sockaddr *)&client_addr, client_len);
            }
            else{
                printf("result error");
            }
        }
        else{
            printf("header error");
        }
    }

    close(sockfd);
    return 0;
}