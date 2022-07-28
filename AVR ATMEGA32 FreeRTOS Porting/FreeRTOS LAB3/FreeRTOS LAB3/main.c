/*
 * FreeRTOS  LAB2.c
 *
 * Created: 7/15/2022 4:35:56 PM
 * Author : ahmed
 */ 



/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8000000


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_INTERFACE.h"
#include "LCD_INTERFACE.h"
#include "LCD_CONFIG.h"
#include "KEYPAD_INTERFACE.h"



/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/* I assign the same priority for the two tasks to see 
the effect of using semaphore on the shared resource (LCD) */
#define TASK1_PRIORITY  (3)
#define TASK2_PRIORITY  (2)

TaskHandle_t Keypad_handle = NULL , LCD_handle = NULL ;

QueueHandle_t Queue1 = NULL ;

void Keypad_task(void *pvParameter);

void LCD_task(void *pvParameter);

void system_init(void)
{
	Keypad_VoidInit();
	LCD_Void_4BitInit();
}


int main()
{
	
	system_init();
	
	Queue1 = xQueueCreate(10,sizeof(unsigned char));
	
	if( Queue1 == NULL )
	{
		/* Queue was not created and must not be used. */
	}

	BaseType_t task1_return = pdFALSE, task2_return = pdFALSE ;
	/* Create the Tasks */
	task1_return = xTaskCreate((pdTASK_CODE)Keypad_task, (signed char *)"Keypad_task", configMINIMAL_STACK_SIZE, NULL, TASK1_PRIORITY, &Keypad_handle);
	task2_return = xTaskCreate((pdTASK_CODE)LCD_task, (signed char *)"LCD_task", configMINIMAL_STACK_SIZE, NULL, TASK2_PRIORITY, &LCD_handle);
	
	if (task1_return == pdTRUE)
	{
		/* task2 created successfully */
	}
	if (task2_return == pdTRUE)
	{
		/* task2 created successfully */
	}
	
	vTaskStartScheduler();
	return 0;
}


void Keypad_task(void *pvParameter)
{
	unsigned char val;
	BaseType_t check = pdFALSE;
	for (;;)
	{
		val = Keypad_U8_GetPressed();
		if (val != 255)
		{
			check = xQueueSend(Queue1,&val,portMAX_DELAY);
			if (check != pdPASS)
			{
				/* Failed to post the message, even after portMAX_DELAY ticks. */
			}
		}
		
		vTaskDelay(100);			// During this delay the task in the waiting state
	}
}


void LCD_task(void *pvParameter)
{
	BaseType_t ret = pdFALSE;
	unsigned char val;
	static unsigned char count = 0;
	for (;;)
	{
		ret = xQueueReceive(Queue1,&val,portMAX_DELAY);
		if (ret == pdTRUE)
		{
			count++ ;
			if (count > 10)
			{
				LCD_Void_4BitSendCommand(DISPLAYCLEAR);
				LCD_Void_4BitSendString((u8*)"wait");
			} 
			else
			{
				LCD_Void_4BitSendChar(val);
			}
		}
	}
}


