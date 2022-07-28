



/*
 * this program is for porting FreeRTOS with STM32F103C8
 * in this project we created two tasks to see their behavior
 * the two tasks use hardware resource 7-segment to display numbers to it
*/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "SEVSEG_interface.h"


#include "FreeRTOS.h"
#include "task.h"



#define TASK1_PRIORITY		(3)
#define TASK2_PRIORITY		(2)



TaskHandle_t task1_handle = NULL , task2_handle = NULL;


void task1(void *pvParameter);
void task2(void *pvParameter);

void system_init(void);



int main(void)
{
	system_init();
	/* create tasks */
	BaseType_t task1_ret = pdFALSE , task2_ret = pdFALSE;

	task1_ret = xTaskCreate((pdTASK_CODE)task1,"task1",configMINIMAL_STACK_SIZE,NULL,TASK1_PRIORITY,&task1_handle);
	task2_ret = xTaskCreate((pdTASK_CODE)task2,"task2",configMINIMAL_STACK_SIZE,NULL,TASK2_PRIORITY,&task2_handle);


	if(task1_ret == pdTRUE)
	{
		/* task1 created successfully */
	}

	if(task2_ret == pdTRUE)
	{
		/* task1 created successfully */
	}

	vTaskStartScheduler();

	for( ;; );

	return 0;
}



void system_init(void)
{
	/* Enable external crystal clock 8 mHZ */
	MRCC_voidInitSysClock();
	/* Enable portA clock */
	MRCC_voidEnableClock(RCC_APB2 , IOPAEN);
	/* initialize 7-segment */
	SEVSEG_voidInit();
}



void task1(void *pvParameter)
{
	char num = 1 ;
	for(;;)
	{
		SEVSEG_voidDisplay(num);

		/* software delay */
		for(u64 i=0 ; i< 350000 ; i++);

		vTaskDelay(500);
	}
}



void task2(void *pvParameter)
{
	char num = 2 ;
	for(;;)
	{
		SEVSEG_voidDisplay(num);

		vTaskDelay(500);
	}
}
















