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
**         ADC测试
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
#define ADC_VREFH       3.3f
#define ADC_VREFL       0.0f
float adcValue;
uint16_t adcRawValue;
uint16_t adcMax;

float adc0_ch2_read(void)
{
	/* 设置ADC通道,并设置软件触发 */
	ADC_DRV_ConfigChan(INST_ADCONV1, 0U, &adConv1_ChnConfig0);
	/* 等待转换完成 */
	ADC_DRV_WaitConvDone(INST_ADCONV1);
	/* 获取ADC量 */
	ADC_DRV_GetChanResult(INST_ADCONV1, 0U, &adcRawValue);
	/* 转换数值为电压 */
	adcValue = ((float) adcRawValue / adcMax) * (ADC_VREFH - ADC_VREFL);
	return adcValue;
}

float adc0_ch3_read(void)
{
	/* 设置ADC通道,并设置软件触发 */
	ADC_DRV_ConfigChan(INST_ADCONV1, 0U, &adConv1_ChnConfig1);
	/* 等待转换完成 */
	ADC_DRV_WaitConvDone(INST_ADCONV1);
	/* 获取ADC量 */
	ADC_DRV_GetChanResult(INST_ADCONV1, 0U, &adcRawValue);
	/* 转换数值为电压 */
	adcValue = ((float) adcRawValue / adcMax) * (ADC_VREFH - ADC_VREFL);
	return adcValue;
}
int main(void)
{
	/* Write your local variable definition here */
	float adc_Volt1=0.00;
	float adc_Volt2=0.00;
	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	#ifdef PEX_RTOS_INIT
		PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
	#endif
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */
	CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
	CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

	/* 根据配置选择量程 */
if (adConv1_ConvConfig0.resolution == ADC_RESOLUTION_8BIT)
	{
		adcMax = (uint16_t) (1 << 8);
	}
else if (adConv1_ConvConfig0.resolution == ADC_RESOLUTION_10BIT)
	{
		adcMax = (uint16_t) (1 << 10);
	}
else
	{
		adcMax = (uint16_t) (1 << 12);
	}
    ADC_DRV_ConfigConverter(INST_ADCONV1, &adConv1_ConvConfig0);  // 初始化ADC
    ADC_DRV_AutoCalibration(INST_ADCONV1);  // 校准ADC

	EDMA_DRV_Init(&dmaController1_State, &dmaController1_InitConfig0, edmaChnStateArray, edmaChnConfigArray, EDMA_CONFIGURED_CHANNELS_COUNT);  // 初始化 eDMA
	LPUART_DRV_Init(INST_LPUART1, &lpuart1_State, &lpuart1_InitConfig0);  // 初始化串口

	PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);  // 初始化IO
	while(1)
	{
		/*ADC采样*/
		adc_Volt1 = adc0_ch2_read() ;  // 对ADC0_CH2进行采样
		adc_Volt2 = adc0_ch3_read() ;  // 对ADC0_CH3进行采样
		u1_printf("ADC1测量电压为 %f伏\r\n",adc_Volt1);
		u1_printf("ADC2测量电压为 %f伏\r\n",adc_Volt2);
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
