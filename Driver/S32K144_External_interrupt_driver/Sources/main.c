/* ###################################################################
**     Filename    : main.c
**     Processor   : S32K144
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**         S32 Design Studio for ARM (Version 2.2)
**         S32K144_SDK V3.0.0
**     Contents    :
**         Õ‚≤ø÷–∂œ∂¡»°∞¥º¸÷µ
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
#include "led.h"
#include "key.h"
/*! 
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
int main(void)
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	#ifdef PEX_RTOS_INIT
		PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
	#endif
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */
	CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
	CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);
	PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);  // ≥ı ºªØIO

	PINS_DRV_SetPinIntSel(PORTC, 12, PORT_INT_RISING_EDGE);  // …Ë÷√Õ‚≤ø÷–∂œ«Î«Û PTC12 …œ…˝—ÿ¥•∑¢
	PINS_DRV_SetPinIntSel(PORTC, 13, PORT_INT_RISING_EDGE);  // …Ë÷√Õ‚≤ø÷–∂œ«Î«Û PTC13 …œ…˝—ÿ¥•∑¢
	INT_SYS_InstallHandler(PORTC_IRQn, PORTC_IRQ, (isr_t *)0);  // ≈‰÷√÷–∂œ∫Ø ˝ PORTC_IRQ
	INT_SYS_EnableIRQ(PORTC_IRQn);  //  πƒ‹÷–∂œ
	while(1)
	{
		LED_G(0);  // ¬Ãµ∆
		LED_R(1);  // ∫Ïµ∆
		LED_Y(1);  // ª∆µ∆
		LED_B(1);  // ¿∂µ∆
		OSIF_TimeDelay(500);
		LED_G(1);  // ¬Ãµ∆
		LED_R(0);  // ∫Ïµ∆
		LED_Y(1);  // ª∆µ∆
		LED_B(1);  // ¿∂µ∆
		OSIF_TimeDelay(500);
		LED_G(1);  // ¬Ãµ∆
		LED_R(1);  // ∫Ïµ∆
		LED_Y(0);  // ª∆µ∆
		LED_B(1);  // ¿∂µ∆
		OSIF_TimeDelay(500);
		LED_G(1);  // ¬Ãµ∆
		LED_R(1);  // ∫Ïµ∆
		LED_Y(1);  // ª∆µ∆
		LED_B(0);  // ¿∂µ∆
		OSIF_TimeDelay(500);
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
