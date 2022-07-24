//
// Created by o.o on 2022/7/22.
//

#ifndef RTOS_V1_ALL_SRC_H
#define RTOS_V1_ALL_SRC_H

#include "FreeRTOS.h"
#include "cmsis_os.h"

#define mainDELAY_LOOP_COUNT 100000

#define KEY1_GPIO_Port GPIOA
#define KEY2_GPIO_Port GPIOC
#define KEY1_GPIO_Pin GPIO_PIN_0
#define KEY2_GPIO_Pin GPIO_PIN_13

#define LED1_GPIO_Port GPIOA
#define LED1_GPIO_Pin GPIO_PIN_1
#define LED2_GPIO_Port GPIOA
#define LED2_GPIO_Pin GPIO_PIN_2


///使用define函数
#define led1_on HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_GPIO_Pin,GPIO_PIN_RESET)
#define led1_off HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_GPIO_Pin,GPIO_PIN_SET)

#define led2_on HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_GPIO_Pin,GPIO_PIN_RESET)
#define led2_off HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_GPIO_Pin,GPIO_PIN_SET)


/* 定义2种数据来源(ID) */
typedef enum
{
    eMotorSpeed,
    eSpeedSetPoint
} ID_t;

/* 定义在队列中传输的数据的格式 */
typedef struct {
    ID_t eDataID;
    uint32_t lDataValue;
}Data_t;

///mail的锻炼用具
typedef struct message
{
    uint8_t keyValue;
    char buf[15];
}Msg;

/* 队列句柄, 创建队列时会设置这个变量 */
static QueueHandle_t xQueue;


/* vSenderTask被用来创建2个任务，用于写队列
 * vReceiverTask被用来创建1个任务，用于读队列
 */

/* 定义2个结构体 */
static const Data_t xStructsToSend[ 2 ] =
{
    { eMotorSpeed,    10 }, /* CAN任务发送的数据 */
    { eSpeedSetPoint, 5 }   /* HMI任务发送的数据 */
};



//外部函数必须在此处声明


extern osThreadId defaultTaskHandle;
extern osThreadId myTask02Handle;
extern osThreadId myTask03Handle;

extern osMessageQId ID_Queue1;
extern osMailQId ID_Mail1;


#endif //RTOS_V1_ALL_SRC_H
