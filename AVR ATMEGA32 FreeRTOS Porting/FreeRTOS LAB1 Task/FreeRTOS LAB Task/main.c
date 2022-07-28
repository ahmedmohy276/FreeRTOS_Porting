/*
 * FreeRTOS LAB Task.c
 *
 * Created: 7/15/2022 2:45:01 PM
 * Author : ahmed
 */ 

/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_INTERFACE.h"


#include "FreeRTOS.h"
#include "task.h"


#define F_CPU 8000000

#define LED1_PRIORITY	(3)
#define LED2_PRIORITY  	(1)

TaskHandle_t LED1_handle = NULL , LED2_handle = NULL ;

void LED1(void *pvParameter);
void LED2(void *pvParameter);

void system_init(void)
{
	DIO_VoidSetPinDirection(0,portD,OUTPUT);
	DIO_VoidSetPinDirection(1,portD,OUTPUT);
}

int main(void)
{
	
	system_init();
    
    BaseType_t task1_return = pdFALSE, task2_return = pdFALSE ;
    /* Create the Tasks */
    task1_return = xTaskCreate((pdTASK_CODE)LED1, (signed char *)"LED1", configMINIMAL_STACK_SIZE, NULL, LED1_PRIORITY, &LED1_handle);
    task2_return = xTaskCreate((pdTASK_CODE)LED2, (signed char *)"LED2", configMINIMAL_STACK_SIZE, NULL, LED2_PRIORITY, &LED2_handle);
    
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




void LED1(void *pvParameter)
{
	DIO_Status port = portD;
	for(;;)
	{
		DIO_VoidTogglePin(0,port);
		vTaskDelay(500);
	}
}



void LED2(void *pvParameter)
{
	DIO_Status port = portD;
	for(;;)
	{
		DIO_VoidTogglePin(1,port);
		vTaskDelay(1000);
	}
}