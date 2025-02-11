/* ###################################################################
**     Filename    : main.c
**     Processor   : S32K1xx
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.00
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including necessary module. Cpu.h contains other modules needed for compiling.*/
#include "Cpu.h"

  volatile int exit_code = 0;

/* User includes (#include below this line is not maintained by Processor Expert) */

/*! 
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
int main(void)
{
	/* Write your local variable definition here */
	uint32_t KEY1;
	uint32_t KEY2;
	uint32_t KEY3;
	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	#ifdef PEX_RTOS_INIT
		PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
	#endif
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */
	CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
	CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);
	PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);  // 初始化IO
	while(1)
	{
		KEY1 = (PINS_DRV_ReadPins(PTC) >> 12) & 0x01;  // 读取KEY1 PTC12的 电平
		KEY2 = (PINS_DRV_ReadPins(PTC) >> 13) & 0x01;  // 读取KEY2 PTC13的 电平
		KEY3 = (PINS_DRV_ReadPins(PTB) >> 2) & 0x01;  // 读取KEY3 PTB2的 电平
		if(KEY1 == 1)
		{
			PINS_DRV_WritePin(PTD,16,0);  // 亮绿灯
		}
		else if(KEY2 == 1)
		{
			PINS_DRV_WritePin(PTD,15,0);  // 亮红灯
		}
		else if(KEY3 == 1)
		{
			PINS_DRV_WritePin(PTD,1,0);  // 亮黄灯
		}
		else
		{
			PINS_DRV_WritePin(PTD,0,0);  // 亮蓝灯
		}
		PINS_DRV_WritePin(PTD,16,1);
		PINS_DRV_WritePin(PTD,15,1);
		PINS_DRV_WritePin(PTD,1,1);
		PINS_DRV_WritePin(PTD,0,1);
//		PINS_DRV_WritePins(PTD, 1<<0 | 1<<1 | 1<<15  | 1<<16 );
	}

	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;) {
    if(exit_code != 0) {
      break;
    }
  }
  return exit_code;
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.1 [05.21]
**     for the NXP S32K series of microcontrollers.
**
** ###################################################################
*/
