
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE (2 * sizeof(int))

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int nums[2] = {25, 37};
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
    memcpy(buffer, nums, BUFFER_SIZE);
    sendto(sockfd, buffer, BUFFER_SIZE, 0,
           (const struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Sent: %d and %d\n", nums[0], nums[1]);

    // 接收结果
    recvfrom(sockfd, &result, sizeof(result), 0, NULL, NULL);

    printf("Result from server: %d\n", result);

    close(sockfd);
    return 0;
}