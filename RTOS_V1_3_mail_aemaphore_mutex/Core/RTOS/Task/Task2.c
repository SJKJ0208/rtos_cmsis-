//
// Created by o.o on 2022/7/22.
//

#include "all_src.h"
#include "stdio.h"

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
        osDelay(100);
        /* 延迟一会(比较简单粗暴) */
        for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
        {
        }
    }
}