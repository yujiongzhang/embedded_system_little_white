# embedded_system_little_white

## how to use

1、what's shell

2、param once

3、udp

4、read file

5、threads

## Note

1、read code with debug

2、Code Architecture before coding

## Task 01

1、send result msg using udp socket 

```c
typedef struct{
    uint8_t MBP;
    uint8_t SBP;
    uint8_t DBP;
    uint8_t HR;
}Body_Data; // body data structure

typedef struct {
    uint8_t head; // 0xa5
    Body_Data body_data;
    uint8_t sum; // sum of head + body_data
} Message_Body; //Body Message structure

```

2、send result and pressure with 2 threads

3、send number1 and number2 and wait for result

## Task 02

1、传入**双指针** 重写 creat_message(m_msg, ADD_MODE, 3, 3);

2、python debug 相对路径设置

3、json 是什么

- 第三方库实现 python 、c

- 网络发送json数据（序列化为json）

4、tcp学习


## reference

https://subingwen.cn/linux