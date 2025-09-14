#include <stdint.h>

#define CALC_MODE_ADD     1U
#define CALC_MODE_SUB     2U
#define CALC_MODE_MULTI   3U
#define CALC_MODE_DIV     4U

#pragma pack(1)

typedef struct {
    uint8_t head; // 0xa5
    uint8_t calculate_mode; // 1-add, 2-sub, 3-multi, 4-div
    uint16_t number1;
    uint16_t number2;
    uint8_t sum; 
} MessageSum;

#pragma pack()