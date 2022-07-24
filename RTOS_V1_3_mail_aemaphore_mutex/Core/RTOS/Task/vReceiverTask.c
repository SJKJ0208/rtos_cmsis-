//
// Created by o.o on 2022/7/23.
//
#include "all_src.h"
#include "retarget.h"

void vReceiverTask( void const *pvParameters )
{
    //此处含有缓冲
    Data_t* data_get;
    osEvent buffer_get;
    for (;;) {
        //读队列
        buffer_get = osMessageGet(ID_Queue1,100);
        if (buffer_get.status == osEventMessage)
        {
            data_get = (Data_t*)(buffer_get.value.p);
            if (data_get->eDataID == eMotorSpeed)
                printf("From Can = %d\r\n",(int)data_get->lDataValue);
            else if (data_get->eDataID == eSpeedSetPoint)
                printf("From HMI = %d\r\n",(int)data_get->lDataValue);
        }
        else
        {
            //printf("can not receive");
        }
        for (int i = 0; i < mainDELAY_LOOP_COUNT; ++i) {
            
        }
    }
}