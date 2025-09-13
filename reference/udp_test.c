#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>  // for Linux/macOS (use <winsock2.h> on Windows)

typedef struct {
    uint8_t data1;
    uint8_t data2;
    uint8_t data3;
} __attribute__((packed)) DataType;

#define SERVER_IP "127.0.0.1"     // 目标服务器IP地址
#define SERVER_PORT 55550          // 目标端口号
#define BUFFER_SIZE 1024


int test1(){
    int sockfd;
    struct sockaddr_in server_addr;
    const char *message = "Hello, UDP Server!\n";
    socklen_t addr_len = sizeof(server_addr);

    // 创建 UDP 套接字
    ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0);

    // 配置目标地址结构
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    // 将 IP 地址从文本转换为二进制形式
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);


    while (1)
    {
        sendto(sockfd, message, strlen(message), 0, (const struct sockaddr *)&server_addr, addr_len);
        sleep(1);
    }

    // 关闭套接字
    close(sockfd);
    return 0;
}

int test2(){
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);

    DataType my_data = {
        .data1 = 0x01,
        .data2 = 0x02,
        .data3 = 0x03
    };
    
    // 创建 UDP 套接字
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 配置目标地址结构
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    // 将 IP 地址从文本转换为二进制形式
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        fprintf(stderr, "Invalid address or Address not supported\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        sendto(sockfd, &my_data, sizeof(my_data), 0,(const struct sockaddr *)&server_addr, addr_len);
    
        printf("已发送: %d\n",my_data.data1);
        sleep(1);
    }

    // 关闭套接字
    close(sockfd);
    return 0;
}

int main() {
    // test1();
    test2();
}