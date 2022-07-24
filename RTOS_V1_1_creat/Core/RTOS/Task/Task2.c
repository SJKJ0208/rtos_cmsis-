//
// Created by o.o on 2022/7/22.
//

#include "all_src.h"
#include "stdio.h"
#include "cmsis_os.h"

/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/

void StartTask03(void const * argument)
{
    const char *pcTaskName = "T2 run\r\n";
    volatile uint32_t ul; /* volatile用来避免被优化掉 */

    /* 任务函数的主体一般都是无限循环 */
    for( ;; )
    {
        /* 打印任务1的信息 */
        printf( pcTaskName );
        printf("turn down task2\t\n");
        for (int i = 0; i < mainDELAY_LOOP_COUNT; ++i) {

        }
        osThreadSetPriority(myTask03Handle, osThreadGetPriority(osThreadGetId())-2);
        /* 延迟一会(比较简单粗暴) */
    }
}