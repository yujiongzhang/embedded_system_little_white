#include <stdint.h>

#pragma pack(1)

typedef struct{
    uint8_t MBP;
    uint8_t SBP;
    uint8_t DBP;
    uint8_t HR;
}Body_Data; // body data structure

typedef struct {
    uint8_t head;
    Body_Data body_data;
    uint8_t sum;
} Message_Body; //Body Message structure


typedef struct 
{
    uint8_t head;
    float pressure;
    uint8_t sum;
}Message_Pressure; // Pressure message structure


#pragma pack()