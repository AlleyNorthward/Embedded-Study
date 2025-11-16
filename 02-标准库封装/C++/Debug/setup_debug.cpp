#include "setup_debug.hpp"

SetUpDebug::SetUpDebug(){}

void SetUpDebug::printf_encode(u8* p){
    while(*p != '\0'){
        printf("0x%02X ",*p);
        p++;
    }
    printf("\r\n");
}

void SetUpDebug::debugging_printf(){
    usart.Init_USART1(115200);
    USART_Cmd(USART1, ENABLE);
}
