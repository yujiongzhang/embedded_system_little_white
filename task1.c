#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h> 

#include "MessageType.h"
#include "task1.h"

static void pack_data(Message_Body* _msg){
    _msg->head = 0xa5;
    _msg->sum = _msg->head + _msg->body_data.MBP + _msg->body_data.HR + _msg->body_data.DBP + _msg->body_data.SBP;
}

static void process_input_data(Message_Body* _msg, char* _str){
    char str[100];
    strcpy(str, _str);

    int count = 0;

    char* token = strtok(str, ",");
    if (token != NULL)
    {
        _msg->body_data.HR = atoi(token);
    }

    token = strtok(NULL, ",");
    if (token != NULL)
    {
        _msg->body_data.SBP = atoi(token);
    }

    token = strtok(NULL, ",");
    if (token != NULL)
    {
        _msg->body_data.DBP = atoi(token);
    }

    token = strtok(NULL, ",");
    if (token != NULL)
    {
        _msg->body_data.MBP = atoi(token);
    }

    pack_data(_msg);
}

void* thread_function_1() {

    char* file_path = "/home/zyj/embedded_system_little_white/data/result_data.csv";
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("无法打开文件");

    }
    
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);
    // 创建 UDP 套接字
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    // 配置目标地址结构
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(55550);
    // 将 IP 地址从文本转换为二进制形式
    if (inet_pton(AF_INET, "192.168.3.15", &server_addr.sin_addr) <= 0) {
        fprintf(stderr, "Invalid address or Address not supported\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    Message_Body m_message_body;
    memset((void*)&m_message_body, 0 , sizeof(m_message_body));

    // Body_Data m_body_data = {
    //     .HR = 0,
    //     .SBP = 0,
    //     .DBP = 0,
    //     .MBP = 0
    // };

    // Message_Body m_message_body = {
    //     .head = 0,
    //     .body_data = m_body_data,
    //     .sum = 0
    // };

    char *line = NULL;
    size_t len = 0;
    ssize_t read; // 读到了多少个
    int line_count = 0; // 记录当前第几行
    read = getline(&line, &len, file); // 跳过第一行
    // 使用getline动态分配内存
    while ((read = getline(&line, &len, file)) != -1) {
        line_count++;
        
        // 移除换行符
        if (read > 0 && line[read - 1] == '\n') { // 判断是否为一行
            line[read - 1] = '\0';
        }
        
        // 数据处理的函数
        process_input_data(&m_message_body,line);

        // 发送数据
        if (sendto(sockfd, &m_message_body, sizeof(m_message_body), 0,
                (const struct sockaddr *)&server_addr, addr_len) < 0) {
            perror("Send failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        sleep(1);// hz
    }
    
    free(line); // 释放动态分配的内存
    fclose(file);
    
    printf("\n文件读取完成，共读取 %d 行。\n", line_count);
        
    close(sockfd);// 关闭套接字
    printf("关闭套接字");

}