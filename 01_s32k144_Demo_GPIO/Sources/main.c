/*
 * Ʒ�ǿƼ�S32K144������
 * 00-GPIO��������
 * ��ʾ��β���GPIOд��,���ȡ���ŵ�ƽ
 *
 * IO����
 * KEY1 PTC12
 * KEY2 PTC13
 * KEY3 PTB2
 * LED1 PTD16
 * LED2 PTD15
 * LED3 PTD1
 * LED4 PTD0
*/
#include "Cpu.h"

  volatile int exit_code = 0;



int main(void)
{
  /* Write your local variable definition here */
	uint32_t pins1;
	uint32_t pins2;
	uint32_t pins3;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of Processor Expert internal initialization.                    ***/

	CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
	CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);
	PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr); //��ʼ��IO
    while(1)
    {
	pins1 = (PINS_DRV_ReadPins(PTC) >> 12) & 0x01; //��ȡKEY1 PTC12�� ��ƽ
	pins2 = (PINS_DRV_ReadPins(PTC) >> 13) & 0x01; //��ȡKEY2 PTC13�� ��ƽ
	pins3 = (PINS_DRV_ReadPins(PTB) >> 2) & 0x01;  //��ȡKEY3 PTB2�� ��ƽ

	if(pins1 == 1)
				{
				PINS_DRV_WritePins(PTD, 0<<0 | 0<<1 | 0<<15  | 0<<16 );//���GPIOд��ƽ���� ����LED
				}
			else
				{
				PINS_DRV_WritePins(PTD, 1<<0 | 1<<1 | 1<<15  | 1<<16 );
				}


			if(pins2 == 1)
				{
				PINS_DRV_WritePin(PTD,0,0); //����GPIOд��ƽ���� ����LED
//				PINS_DRV_WritePin(PTD,1,0);
//				PINS_DRV_WritePin(PTD,15,0);
//				PINS_DRV_WritePin(PTD,16,0);
				}
			else
				{
				PINS_DRV_WritePin(PTD,0,1);
//				PINS_DRV_WritePin(PTD,1,1);
//				PINS_DRV_WritePin(PTD,15,1);
//				PINS_DRV_WritePin(PTD,16,1);
				}




    }
  /*** Don't write any code pass th5is line, or it will be deleted during code generation. ***/
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
