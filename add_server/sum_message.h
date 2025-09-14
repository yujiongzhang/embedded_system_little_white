#include <stdint.h>

#pragma pack(1)

typedef struct {
    uint8_t head; // 0xa5
    uint8_t mode;
    uint16_t number1;
    uint16_t number2;
    uint8_t sum; // 校验和
} MessageSum;

#pragma pack()