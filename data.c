// gcc data.c -o data
// ./data

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

typedef struct {
    uint8_t type;
    uint16_t length;
    uint32_t timestamp;
} __attribute__((packed)) Type1;

typedef struct {
    uint8_t type;
    uint16_t length;
    uint32_t timestamp;
} Type2;

#pragma pack(1)
typedef struct {
    uint8_t type;
    uint16_t length;
    uint32_t timestamp;
} Type3;
#pragma pack()


int main() {
    printf("sizeof(Type1): %ld\n",sizeof(Type1));
    printf("sizeof(Type2): %ld\n",sizeof(Type2));
    printf("sizeof(Type3): %ld\n",sizeof(Type3));
    return 0;
}