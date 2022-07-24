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

void StartTask02(void const * argument);
void StartTask03(void const * argument);

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

    //此处利用宏，不知不觉的创建了一个包含信息（名字，函数地址，优先级，传递的参数，堆栈大小）
    osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
    defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);


    osThreadDef(myTask02, StartTask02, 2, 1, 128);
    myTask02Handle = osThreadCreate(osThread(myTask02), NULL);


    osThreadDef(myTask03, StartTask03, 1, 1, 128);
    myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

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