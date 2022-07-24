//
// Created by o.o on 2022/7/24.
//

#include "all_src.h"
#include "retarget.h"
#include "string.h"


uint8_t KEY_Scan(void);

void vReceiverTask_mail( void const *pvParameters )
{
    Msg * re_msg;
    osEvent state;
    static uint8_t flag = 0;///用于标记是否开灯
    static uint8_t flag2 = 0;///用于标记是否开灯

    for( ;; )
    {
        state =  osMailGet(ID_Mail1,osWaitForever);
        ///假如没接收到就一直堵住
        if (state.status == osEventMail){
            ///此时是接收到了
            re_msg  = (Msg*)(state.value.p);
            printf("%s\r\n",re_msg->buf);
            if (re_msg->keyValue == 1)
            {
                if (flag == 1)
                    led1_off;
                else if (flag == 0)
                    led1_on;
                flag = !flag;
            }
            else if (re_msg->keyValue == 2)
            {
                if (flag2 == 1)
                    led2_off;
                else if (flag2 == 0)
                    led2_on;
            }
        }
        osDelay(20);
    }
}

void vSenderTask_mail( void const *pvParameters )
{
    ///利用mail将一个函数中的值传递到另一个函数中

    uint32_t key_value;
    Msg *msgp = NULL;
    osStatus state = osErrorOS;
    msgp =  osMailAlloc(ID_Mail1,osWaitForever);
    ///判断是否够内存开辟
    if (msgp == NULL)
    {
        printf("osMailAlloc 开辟失败");
    }
    for( ;; )
    {
        key_value = KEY_Scan();
        if (key_value!=0) {
            strcpy(msgp->buf, "key pressed");
            msgp->keyValue = key_value;
            state = osMailPut(ID_Mail1, msgp);
            if (state != osOK) {
                printf("mail send failed");
            }
        }
        osDelay(20);
        ///传出去后，完成扫描任务，也就是设置了200ms扫描一次
    }
}

uint8_t KEY_Scan(void)
{
    //没有key_up，会导致按下按键再松开之前，多次调用KEY_Scan时，每次都会检测到按键
    //被按下了，有了key_up，第一次调用KEY_Scan时返回键值，后面几次调用时会通过
    //key_up检测到已经返回过一次键值了，不再返回键值
    ///用作适配不同的逻辑key
    uint8_t key_set = 0;
    uint8_t key_reset = 1;
    static uint8_t key_up = 0;
    int KEY1 = HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_GPIO_Pin);
    int KEY2 = HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_GPIO_Pin);

    if((key_up == 0) && (KEY1 == key_reset || KEY2 == key_reset)) //检测到刚按下进入，如果是按住不放不会进入
    {
        osDelay(100);                      //去抖动
        key_up = 1;                        //设置标志位，表示按下

        if(KEY1 == key_reset)return 1; 				//如果k1按下就返回1
        else if(KEY2 == key_reset)return 2; 		//如果k2按下就返回2
    }
    else if(KEY1 == key_set && KEY2 == key_set) key_up = 0; 	 //按键松开，清标志位
    return 0;                              //无按键按下或松开了时就返回0
}

void gpio_init_led()
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitTypeDef led_gpio_init = {0};
    led_gpio_init.Pin = GPIO_PIN_1;
    led_gpio_init.Mode =GPIO_MODE_OUTPUT_PP;
    led_gpio_init.Pull = GPIO_PULLUP;//默认低为开
    led_gpio_init.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA,&led_gpio_init);

    led_gpio_init.Pin = GPIO_PIN_2;
    HAL_GPIO_Init(GPIOA,&led_gpio_init);

    led_gpio_init.Pin = GPIO_PIN_0;
    led_gpio_init.Mode = GPIO_MODE_INPUT;
    led_gpio_init.Pull = GPIO_NOPULL;
    ///key1 GPIOA-0
    HAL_GPIO_Init(GPIOA,&led_gpio_init);

    ///key2 GPIOC-13
    led_gpio_init.Pin = GPIO_PIN_13;
    HAL_GPIO_Init(GPIOC,&led_gpio_init);
}