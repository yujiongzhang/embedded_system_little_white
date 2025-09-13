#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// 线程函数1
void* thread_function_1(void* arg) {
    int thread_id = *((int*)arg);
    for (int i = 0; i < 5; i++) {
        printf("线程 %d 执行: %d\n", thread_id, i + 1);
        sleep(1); // 模拟耗时操作
    }
    pthread_exit(NULL);
}

// 线程函数2
void* thread_function_2(void* arg) {
    int thread_id = *((int*)arg);
    for (int i = 0; i < 5; i++) {
        printf("线程 %d 执行: %d\n", thread_id, i + 1);
        sleep(2); // 模拟耗时操作
    }
    pthread_exit(NULL);
}

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