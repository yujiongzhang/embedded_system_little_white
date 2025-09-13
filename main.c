#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "task1.h"
#include "task2.h"

int main() {
    pthread_t thread1, thread2;
    int tid1 = 1, tid2 = 2;

    printf("创建两个线程...\n");

    // 创建线程1
    if (pthread_create(&thread1, NULL, thread_function_1, &tid1) != 0) {
        fprintf(stderr, "无法创建线程1\n");
        exit(EXIT_FAILURE);
    }

    // 创建线程2
    if (pthread_create(&thread2, NULL, thread_function_2, &tid2) != 0) {
        fprintf(stderr, "无法创建线程2\n");
        exit(EXIT_FAILURE);
    }

    // 等待线程结束
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("两个线程执行完毕。\n");
    return 0;
}