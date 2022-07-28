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



/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"



/* I assign the same priority for the two tasks to see 
the effect of using semaphore on the shared resource (LCD) */
#define TASK1_PRIORITY  (3)
#define TASK2_PRIORITY  (3)

TaskHandle_t task1_handle = NULL , task2_handle = NULL ;

SemaphoreHandle_t  LCD_SEM = NULL ;

void task1(void *pvParameter);

void task2(void *pvParameter);


int main()
{
	
	LCD_Void_4BitInit();
	
	/* for shared resources it is better to use mutex */
	LCD_SEM = xSemaphoreCreateMutex();
	//LCD_SEM = xSemaphoreCreateBinary();
	//xSemaphoreGive(LCD_SEM);
	
	if (LCD_SEM != NULL)
	{
		/* semaphore created successfully*/
	}
	BaseType_t task1_return = pdFALSE, task2_return = pdFALSE ;
	/* Create the Tasks */
	task1_return = xTaskCreate((pdTASK_CODE)task1, (signed char *)"task1", configMINIMAL_STACK_SIZE, NULL, TASK1_PRIORITY, &task1_handle);
	task2_return = xTaskCreate((pdTASK_CODE)task2, (signed char *)"task2", configMINIMAL_STACK_SIZE, NULL, TASK2_PRIORITY, &task2_handle);
	
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


void task1(void *pvParameter)
{
	BaseType_t ret = pdFALSE;
	for (;;)
	{
		ret = xSemaphoreTake(LCD_SEM,2000);
		if (ret == pdTRUE)
		{
			LCD_Void_4BitSendCommand(DISPLAYCLEAR);
			LCD_Void_4BitSendString((u8*)"I'm Task 1");
			_delay_ms(1000);			// During this delay the task in the running state
			vTaskDelay(2000);			// During this delay the task in the waiting state
		}
		
		xSemaphoreGive(LCD_SEM);
	}
}


void task2(void *pvParameter)
{BaseType_t ret = pdFALSE;
	for (;;)
	{
		ret = xSemaphoreTake(LCD_SEM,2000);
		if (ret == pdTRUE)
		{
			LCD_Void_4BitSendCommand(DISPLAYCLEAR);
			LCD_Void_4BitSendString((u8*)"I'm Task 2");
			_delay_ms(1000);			// During this delay the task in the running state
			vTaskDelay(2000);			// During this delay the task in the waiting state
		}
		
		xSemaphoreGive(LCD_SEM);
	}
	
}


