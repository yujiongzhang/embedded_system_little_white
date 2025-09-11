#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    char* file_path = "./data/result_data.csv";
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("无法打开文件");
        return 1;
    }
    
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int line_count = 0;
    
    printf("开始读取CSV文件，每秒打印一行...\n\n");
    
    // 使用getline动态分配内存
    while ((read = getline(&line, &len, file)) != -1) {
        line_count++;
        
        // 移除换行符
        if (read > 0 && line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }
        
        printf("第 %d 行: %s\n", line_count, line);
        sleep(1);
    }
    
    free(line); // 释放动态分配的内存
    fclose(file);
    
    printf("\n文件读取完成，共读取 %d 行。\n", line_count);
    return 0;
}