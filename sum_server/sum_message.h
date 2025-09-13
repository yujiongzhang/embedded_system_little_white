#include <stdint.h>

#pragma pack(1)

typedef struct {
    uint8_t head; // 0xa5
    uint16_t number1;
    uint16_t number2;
    uint8_t sum; 
} MessageSum;

#pragma pack()