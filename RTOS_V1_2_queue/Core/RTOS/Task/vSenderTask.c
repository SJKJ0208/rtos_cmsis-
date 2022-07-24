//
// Created by o.o on 2022/7/23.
//
#include "all_src.h"
#include "retarget.h"

///此处传入的是一个Data_t类型的指针指向都可访问的内存
void vSenderTask( void const *pvParameters )
{
    uint32_t * buffer_send = (uint32_t*)pvParameters;
    BaseType_t State;
    //此处含有缓冲
    for (;;) {
        //写队列
        int a = osMessageAvailableSpace(ID_Queue1);
        State = osMessagePut(ID_Queue1, (uint32_t)buffer_send, 100);
        if (State == osOK)
        {
          // printf("send success\t\n");
        }
        for (int i = 0; i < mainDELAY_LOOP_COUNT; ++i) {
            
        }
    }
}
