//
// Created by o.o on 2022/7/22.
//

#ifndef RTOS_V1_ALL_SRC_H
#define RTOS_V1_ALL_SRC_H

#include "FreeRTOS.h"
#include "cmsis_os.h"

#define mainDELAY_LOOP_COUNT 100000

//外部函数必须在此处声明
extern osThreadId defaultTaskHandle;
extern osThreadId myTask02Handle;
extern osThreadId myTask03Handle;

#endif //RTOS_V1_ALL_SRC_H
