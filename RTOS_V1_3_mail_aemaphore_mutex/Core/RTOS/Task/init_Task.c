//
// Created by o.o on 2022/7/22.
//
//因为希望掌握构建代码的能力，因此在此构造一个rtos的使用模板，并产出一篇关于rtos的文章

//init用于对所有的任务和驱动进行初始化


#include "retarget.h"
#include "usart.h"
#include "all_src.h"


osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;

osMessageQId ID_Queue1;

///队列的使用

void StartTask02(void const * argument);
void StartTask03(void const * argument);
///发送和接受任务
void vReceiverTask( void const *pvParameters );
void vSenderTask( void const *pvParameters );

///默认任务
void StartDefaultTask(void const * argument);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );


//为空闲函数寻找静态TCB的栈空间
static StaticTask_t xIdleTaskTCBBuffer;
//第一个空间用于作为缓存
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
    *ppxIdleTaskStackBuffer = &xIdleStack[0];
    //此处给出栈大小128(最小)
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
    /* place for user code */
}


/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
    RetargetInit(&huart1);
    printf("enter in init\r\n");
    /* 创建队列: 长度为5，数据大小为4字节(存放一个整数) */
    osMessageQDef(queue1,5, Data_t);
    ID_Queue1 = osMessageCreate(osMessageQ(queue1),NULL);

    if (ID_Queue1 != NULL)
    {
        printf("creat success\r\n");
        //此处利用宏，不知不觉的创建了一个包含信息（名字，函数地址，优先级，传递的参数，堆栈大小）
//        osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
//        defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

        /* 创建2个任务用于写队列, 传入的参数是不同的结构体地址
         * 任务函数会连续执行，向队列发送结构体
         * 优先级为2
         */
        osThreadDef(CAN_Task, vSenderTask, 2, 2, 1000);
        myTask02Handle = osThreadCreate(osThread(CAN_Task), ( void * ) &( xStructsToSend[ 0 ] ));


        osThreadDef(HMI_Task, vSenderTask, 2, 2, 1000);
        myTask03Handle = osThreadCreate(osThread(HMI_Task), ( void * ) &( xStructsToSend[ 1 ] ));

        /* 创建1个任务用于读队列
         * 优先级为1, 低于上面的两个任务
         * 这意味着发送任务优先写队列，队列常常是满的状态
         */
        osThreadDef(Receiver, vReceiverTask, 1, 2, 1000);
        myTask03Handle = osThreadCreate(osThread(Receiver), NULL);
    }
}

/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
void StartDefaultTask(void const * argument)
{

    for(;;)
    {
        osDelay(1);
    }

}