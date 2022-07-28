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
#include <avr/interrupt.h>

#define F_CPU 8000000


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_INTERFACE.h"
#include "LCD_INTERFACE.h"
#include "LCD_CONFIG.h"
#include "Interrupt_INTERFACE.h"




/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


/* I assign the same priority for the two tasks to see 
the effect of using semaphore on the shared resource (LCD) */
#define TASK1_PRIORITY  (3)
#define TASK2_PRIORITY  (3)

TaskHandle_t task1_handle = NULL , task2_handle = NULL ;

SemaphoreHandle_t LCD_SEM = NULL ;

void task1(void *pvParameter);

void INT2_CallBack(void);

void system_init(void)
{
	
	LCD_Void_4BitInit();
	
	INT_Status INT_index = INT_2;
	INT_Status INT_type = FALLING_EDGE;
	
	/* activate pull up resistor on INT2 */
	DIO_VoidSetPinDirection(2,portB,INPUT);
	DIO_VoidSetPinValue(2,portB,HIGH);

	Interrupt_VoidInterruptActivate(INT_index,INT_type);
	Interrupt_SetCallBackFunction(INT2_CallBack,INT_index);
}


int main()
{
	
	system_init();
	
	/*  We can use counting semaphore with initial val=0 and max count =1 */
	//LCD_SEM = xSemaphoreCreateCounting(1,0); 
	
	LCD_SEM = xSemaphoreCreateBinary();

	if (LCD_SEM != NULL)
	{
		/* semaphore created successfully*/
	}
	
	BaseType_t task1_return = pdFALSE, task2_return = pdFALSE ;
	/* Create the Tasks */
	task1_return = xTaskCreate((pdTASK_CODE)task1, (signed char *)"task1", configMINIMAL_STACK_SIZE, NULL, TASK1_PRIORITY, &task1_handle);
	
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
		ret = xSemaphoreTake(LCD_SEM,portMAX_DELAY);
		if (ret == pdTRUE)
		{
			LCD_Void_4BitSendString((u8*)"Button Pressed");
			_delay_ms(3000);			// During this delay the task in the running state
			LCD_Void_4BitSendCommand(DISPLAYCLEAR);
		}
	}
}



void INT2_CallBack(void)
{
	// This clarifies how to synchronize task with an interrupt using semaphore
	// Release the semaphore
	xSemaphoreGiveFromISR(LCD_SEM,NULL);
}


