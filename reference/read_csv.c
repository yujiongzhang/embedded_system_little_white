#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "MessageType.h"

void process_input_data(Message_Body* _msg, char* _str){
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
}

void printf_message_body(Message_Body _msg){
    printf("head: %d\n", _msg.head);
    printf("HR:   %d\n", _msg.body_data.HR);
    printf("SBP:  %d\n", _msg.body_data.SBP);
    printf("DBP:  %d\n", _msg.body_data.DBP);
    printf("MBP:  %d\n", _msg.body_data.MBP);
    printf("sum:  %d\n", _msg.sum);
    printf("\n");
}

Message_Body m_message_body;

int main(int argc, char *argv[]) {

    char* file_path = "/home/zyj/embedded_system_little_white/data/result_data.csv";
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("无法打开文件");
        return 1;
    }
    
    char *line = NULL;
    size_t len = 0;
    ssize_t read; // 读到了多少个
    int line_count = 0; // 记录当前第几行
    
    printf("开始读取CSV文件，每秒打印一行...\n\n");
    
    read = getline(&line, &len, file); // 跳过第一行
    
    // 使用getline动态分配内存
    while ((read = getline(&line, &len, file)) != -1) {
        line_count++;
        
        // 移除换行符
        if (read > 0 && line[read - 1] == '\n') { // 判断是否为一行
            line[read - 1] = '\0';
        }
        
        printf("第 %d 行: %s\n", line_count, line);

        process_input_data(&m_message_body, line);

        printf_message_body(m_message_body);


        sleep(1);
    }
    
    free(line); // 释放动态分配的内存
    fclose(file);
    
    printf("\n文件读取完成，共读取 %d 行。\n", line_count);
    return 0;
}