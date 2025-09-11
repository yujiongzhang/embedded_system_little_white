
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE (2 * sizeof(int)) // 接收两个 int

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    int nums[2];
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
        memcpy(nums, buffer, BUFFER_SIZE);

        // 计算和
        sum = nums[0] + nums[1];

        printf("Received: %d + %d = %d\n", nums[0], nums[1], sum);

        // 发送结果回客户端
        sendto(sockfd, &sum, sizeof(sum), 0,
               (const struct sockaddr *)&client_addr, client_len);
    }

    close(sockfd);
    return 0;
}