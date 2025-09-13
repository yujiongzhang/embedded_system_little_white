#include<utils.h>

void printf_message_body(Message_Body _msg){
    printf("head: %d\n", _msg.head);
    printf("HR:   %d\n", _msg.body_data.HR);
    printf("SBP:  %d\n", _msg.body_data.SBP);
    printf("DBP:  %d\n", _msg.body_data.DBP);
    printf("MBP:  %d\n", _msg.body_data.MBP);
    printf("sum:  %d\n", _msg.sum);
    printf("\n");
}