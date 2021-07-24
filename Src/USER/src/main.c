#include "main.h"

#define StartTask_Stack         32
#define StartTask_Prio          1
TaskHandle_t StartTask_Handler;

// #define LedTask_Stack           32
// #define LedTask_Prio            2
// TaskHandle_t LedTask_Handler;

#define HygroTask_Stack         128
#define HygroTask_Prio          3
TaskHandle_t HygroTask_Handler;

// #define DebugTask_Stack         32
// #define DebugTask_Prio          4
// TaskHandle_t DebugTask_Handler;

void Led_Task(void *param)
{
    while(1)
    {
		GPIO_ResetBits(GPIOB, LED_GPIO_PIN);
		bsp_abit_delay_ms(500);
		GPIO_SetBits(GPIOB, LED_GPIO_PIN);
		vTaskDelay(500);
    }
}

void Hygro_Task(void *param)
{
	Humiture_InitTypeDef Humiture_InitStruct;

	while(1)
	{
		if(bsp_abit_dh11_read_data(&Humiture_InitStruct) == 0)
		{
			printf("ÎÂ¶È: %d.%d\r\n", Humiture_InitStruct.Temp_Int, Humiture_InitStruct.Temp_Dec);
			printf("Êª¶È: %d.%d\r\n", Humiture_InitStruct.Humid_Int, Humiture_InitStruct.Humid_Dec);
		}
		vTaskDelay(500);
	}
}

void Debug_Task(void *param)
{
	while(1)
	{
		printf("hello abit\r\n");
		vTaskDelay(500);
	}
}

void Start_Task(void *param)
{
	taskENTER_CRITICAL();
	// xTaskCreate((TaskFunction_t)Led_Task,
	// 		(const char *)"Led_Task",
	// 		(const configSTACK_DEPTH_TYPE)LedTask_Stack,
	// 		(void *)NULL,
	// 		(UBaseType_t) LedTask_Prio,
	// 		(TaskHandle_t *)&LedTask_Handler);
	
	xTaskCreate((TaskFunction_t)Hygro_Task,
			(const char *)"Hygro_Task",
			(const configSTACK_DEPTH_TYPE)HygroTask_Stack,
			(void *)NULL,
			(UBaseType_t) HygroTask_Prio,
			(TaskHandle_t *)&HygroTask_Handler);
	
	// xTaskCreate((TaskFunction_t)Debug_Task,
	// 		(const char *)"Debug_Task",
	// 		(const configSTACK_DEPTH_TYPE)DebugTask_Stack,
	// 		(void *)NULL,
	// 		(UBaseType_t) DebugTask_Prio,
	// 		(TaskHandle_t *)&DebugTask_Handler);
	
	vTaskDelete(StartTask_Handler);
	taskEXIT_CRITICAL();
}

int main()
{
    bsp_abit_delay_init(72);
    bsp_abit_gpio_init();
    bsp_abit_usart_init(115200);
	bsp_abit_nvic_init();

    xTaskCreate((TaskFunction_t)Start_Task,
                (const char *)"Start_Task",
                (const configSTACK_DEPTH_TYPE)StartTask_Stack,
                (void *)NULL,
                (UBaseType_t) StartTask_Prio,
                (TaskHandle_t *)&StartTask_Handler);
    
    vTaskStartScheduler();

    return 0;
}