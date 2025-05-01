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
**         ��ʱ���жϿ��ƴ��ڶ�ʱ������Ϣ
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
#include <string.h>
#include "uart.h"
/*! 
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
uint8_t FTM_flag1;
uint8_t FTM_flag2;
/* FTM�����жϼ��㹫ʽ:
* ��װ��ֵ  /(��Ƶ/��Ƶ) ��λ:��
* ��������100ms���ж�����:
* 37500 (����ֵ)/(48000000hz(��Ƶ)/128(��Ƶ)) = 1/10�� = 100ms
*/
void ftmTimer1ISR(void)
{
	// ftm�����ж����Ҳ��174�������� ��������100msΪ����  �����1��һ��,�Ǿ�ֻ������10���ٷ�תled
    static uint8_t count = 0U;
    if(count < 4)
    {
 	   count++;
    }
    else
    {
        FTM_flag1 = 1;
        count = 0;
    }
    FTM_DRV_ClearStatusFlags(INST_FLEXTIMER_MC1, (uint32_t)FTM_TIME_OVER_FLOW_FLAG);  //���FTM״̬��־λ
}
void ftmTimer2ISR(void)
{
	// ftm�����ж����Ҳ��174�������� ��������100msΪ����  �����1��һ��,�Ǿ�ֻ������10���ٷ�תled
    static uint8_t count = 0U;
    if(count < 9)
    {
 	   count++;
    }
    else
    {
        FTM_flag2 = 1;
        count = 0;
    }
    FTM_DRV_ClearStatusFlags(INST_FLEXTIMER_MC2, (uint32_t)FTM_TIME_OVER_FLOW_FLAG);  //���FTM״̬��־λ
}
int main(void)
{
	/* Write your local variable definition here */
	ftm_state_t ftmStateStruct;
	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	#ifdef PEX_RTOS_INIT
		PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
	#endif
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */
	CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
	CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

	FTM_DRV_Init(INST_FLEXTIMER_MC1, &flexTimer_mc1_InitConfig, &ftmStateStruct);  // ��ʼ��FTMģ��
	INT_SYS_InstallHandler(FTM0_Ovf_Reload_IRQn, &ftmTimer1ISR,(isr_t*) 0U);  // ���ò�ʹ��ʱ��������ж�
	INT_SYS_EnableIRQ(FTM0_Ovf_Reload_IRQn);  // ʹ�ܶ�ʱ���ж�
	FTM_DRV_InitCounter(INST_FLEXTIMER_MC1, &flexTimer_mc1_TimerConfig);  // ��ʼ��������
	FTM_DRV_CounterStart(INST_FLEXTIMER_MC1);  // ��ʼ������

	FTM_DRV_Init(INST_FLEXTIMER_MC2, &flexTimer_mc2_InitConfig, &ftmStateStruct);
	INT_SYS_InstallHandler(FTM1_Ovf_Reload_IRQn, &ftmTimer2ISR,(isr_t*) 0U);  // ���ò�ʹ��ʱ��������ж�
	INT_SYS_EnableIRQ(FTM1_Ovf_Reload_IRQn);  // ʹ�ܶ�ʱ���ж�
	FTM_DRV_InitCounter(INST_FLEXTIMER_MC2, &flexTimer_mc2_TimerConfig);  // ��ʼ��������
	FTM_DRV_CounterStart(INST_FLEXTIMER_MC2);  // ��ʼ������

	PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);  // ��ʼ��IO
	EDMA_DRV_Init(&dmaController1_State, &dmaController1_InitConfig0, edmaChnStateArray, edmaChnConfigArray, EDMA_CONFIGURED_CHANNELS_COUNT);  // ��ʼ�� eDMA
	LPUART_DRV_Init(INST_LPUART1, &lpuart1_State, &lpuart1_InitConfig0);  // ��ʼ������
	LPUART_DRV_InstallRxCallback(INST_LPUART1, LPUART1_RX_ISR, NULL);  // ��װ�����жϻص�����
	LPUART_DRV_ReceiveData(INST_LPUART1, buffer, 1);  // �������ڽ���,ÿ�ν���һ���ֽ�,����װ�ж�
	while(1)
	{
		if(FTM_flag1 == 1)
		{
			u1_printf("��ʱ��һ\r\n");
			FTM_flag1=0;
		}
		else if(FTM_flag2 == 1)
		{
			u1_printf("��ʱ����\r\n");
			FTM_flag2=0;
		}
		else{}
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
