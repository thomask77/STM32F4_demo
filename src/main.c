#include "stm32f4xx.h"
#include "uart.h"
#include "ansi.h"
#include "ustime.h"
#include "FreeRTOS.h"
#include "task.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


void set_leds(int leds)
{
    GPIOD->ODR = (GPIOD->ODR & ~0xF000) | ((leds << 12) & 0xF000);
}

struct task_param {
    char *name;
    int   interval;
};

static void fpu_task(void *pvParameters)
{
    // Force x to stay in a FPU reg.
    //
    register float x = 0;
    struct task_param *p = pvParameters;

    for(;;) {
        printf("%s: x = %f\n", p->name, x);
        x += 1;
        vTaskDelay(p->interval);
    }
}

static void init_task(void *pvParameters)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIO_Init(GPIOD, &(GPIO_InitTypeDef) {
        .GPIO_Pin   = 0xF000,
        .GPIO_Mode  = GPIO_Mode_OUT,
        .GPIO_OType = GPIO_OType_PP,
        .GPIO_PuPd  = GPIO_PuPd_NOPULL,
        .GPIO_Speed = GPIO_Speed_50MHz,
    });

    uart_init(115200);
    printf(ANSI_FG_LTRED "STM32F407" ANSI_NORMAL " FreeRTOS Test\n" );

    vTaskDelay(100);

    for (int i=0; i<5; i++) {
        printf("Starting FPU task %d..\n", i);

        struct task_param *p;

        p = malloc(sizeof(struct task_param));
        p->name     = malloc(16);
        p->interval = (i+1) * 500;
        sprintf(p->name, "FPU_%d", i);

        xTaskCreate(fpu_task, (int8_t*)p->name, 1024, p, tskIDLE_PRIORITY, NULL);
    }

    for(;;);
}


int main(void)
{
    // FreeRTOS assumes 4 preemption- and 0 subpriority-bits
    //
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    // Create init task and start the scheduler
    //
    xTaskCreate(init_task, (signed char*)"init", 1024, NULL, tskIDLE_PRIORITY, NULL);
    vTaskStartScheduler();
}
