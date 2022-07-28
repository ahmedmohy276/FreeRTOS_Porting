

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


#define TASK1_PRIORITY  (3)
#define TASK2_PRIORITY  (2)

TaskHandle_t task1_handle = NULL , task2_handle = NULL ;

void task1(void *pvParameter);

void task2(void *pvParameter);


int main()
{
	
	LCD_Void_4BitInit();
	
	/* Create the Tasks */
	
	BaseType_t task1_return = pdFALSE, task2_return = pdFALSE ;
	
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
	for (;;)
	{
		LCD_Void_4BitSendCommand(DISPLAYCLEAR);
		LCD_Void_4BitSendString((u8*)"I'm Task 1");
		_delay_ms(1000);			// During this delay the task in the running state
		
		vTaskDelay(2000);			// During this delay the task in the waiting state
	}
}


void task2(void *pvParameter)
{
	for (;;)
	{
		LCD_Void_4BitSendCommand(DISPLAYCLEAR);
		LCD_Void_4BitSendString((u8*)"I'm Task 2");
		//_delay_ms(1000);
		vTaskDelay(2000);
		//LCD_Void_4BitSendString((u8*)"I'm Task 22");
	}
	
}

