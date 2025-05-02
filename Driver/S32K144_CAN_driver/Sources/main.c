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
**         CAN测试
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
#define Rx_Filter  0x0
char IRQ_CAN0_RX;
char IRQ_CAN1_RX;
char IRQ_CAN2_RX;
can_message_t recvMsg_CAN0;
can_message_t recvMsg_CAN1;
can_message_t recvMsg_CAN2;

#define RX_MAILBOX_CAN0  (0UL)
#define TX_MAILBOX_CAN0  (1UL)

#define RX_MAILBOX_CAN1  (2UL)
#define TX_MAILBOX_CAN1  (3UL)
//
#define RX_MAILBOX_CAN2  (4UL)
#define TX_MAILBOX_CAN2  (5UL)

/* CAN0回调函数 */
void CAN0_Callback_Func (uint32_t instance,can_event_t event,uint32_t buffIdx,void *flexcanState)
{
	(void)flexcanState;  // 此处防止警报
	(void)instance;
	(void)buffIdx;
	CAN_Receive(&can_pal1_instance, RX_MAILBOX_CAN0, &recvMsg_CAN0);  // 接收报文并重新注册回调函数
	switch(event)  // 回调事件
	{
		case CAN_EVENT_RX_COMPLETE:  // 接收完成 事件
			IRQ_CAN0_RX =1;
			break;
		case CAN_EVENT_TX_COMPLETE:  // 发送完成事件
			break;
		default:
			break;
	}
}

void CAN1_Callback_Func (uint32_t instance,can_event_t event,uint32_t buffIdx,void *flexcanState)
{
	(void)flexcanState;
	(void)instance;
	(void)buffIdx;
	CAN_Receive(&can_pal2_instance, RX_MAILBOX_CAN1, &recvMsg_CAN1);
	switch(event)
	{
		case CAN_EVENT_RX_COMPLETE:
			IRQ_CAN1_RX =1;
			break;
		case CAN_EVENT_TX_COMPLETE:
			break;
		default:
			break;
	}
}

void CAN2_Callback_Func (uint32_t instance,can_event_t event,uint32_t buffIdx,void *flexcanState)
{
	(void)flexcanState;
	(void)instance;
	(void)buffIdx;
	CAN_Receive(&can_pal3_instance, RX_MAILBOX_CAN2, &recvMsg_CAN2);
	switch(event)
	{
		case CAN_EVENT_RX_COMPLETE:
			IRQ_CAN2_RX =1;
			break;
		case CAN_EVENT_TX_COMPLETE:
			break;
		default:
			break;
	}
}

void CAN0_Init(void)
{
	CAN_Init(&can_pal1_instance, &can_pal1_Config0);
	can_buff_config_t Rx_buffCfg =  {
		.enableFD = false,
		.enableBRS = false,
		.fdPadding = 0U,
		.idType = CAN_MSG_ID_STD,
		.isRemote = false
	};

	can_buff_config_t Tx_buffCfg =  {
		.enableFD = false,
		.enableBRS = false,
		.fdPadding = 0U,
		.idType = CAN_MSG_ID_STD,
		.isRemote = false
	};
	CAN_ConfigRxBuff(&can_pal1_instance, RX_MAILBOX_CAN0, &Rx_buffCfg, Rx_Filter);  // 注册接收配置和MSGID过滤器(如过滤器配置为0x1，则只接受msgid 0x1发来的报文)
	CAN_ConfigTxBuff(&can_pal1_instance, TX_MAILBOX_CAN0, &Tx_buffCfg);  // 配置发送
	/*设置MSGID的掩码，掩码粗略可以理解为对11bit MSGID地址的过滤
	如果某bit位需要过滤设置为1,不过滤设置为0,例如掩码设置为0x7ff则过滤全部标准id,如果设置为0x7fe,这只能接受0x01的报文(不存在0x0的地址)*/
	CAN_SetRxFilter(&can_pal1_instance,CAN_MSG_ID_STD,RX_MAILBOX_CAN0,0);  // 设置MSGID掩码，
	CAN_InstallEventCallback(&can_pal1_instance,&CAN0_Callback_Func,(void*)0);  // 注册回调函数
	CAN_Receive(&can_pal1_instance, RX_MAILBOX_CAN0, &recvMsg_CAN0);  // *****重点****此函数不只有接收作用 还有续订回调函数的作用.
}

void CAN1_Init(void)
{
	CAN_Init(&can_pal2_instance, &can_pal2_Config0);
	can_buff_config_t Rx_buffCfg =  {
		.enableFD = false,
		.enableBRS = false,
		.fdPadding = 0U,
		.idType = CAN_MSG_ID_STD,
		.isRemote = false
	};

	can_buff_config_t Tx_buffCfg =  {
		.enableFD = false,
		.enableBRS = false,
		.fdPadding = 0U,
		.idType = CAN_MSG_ID_STD,
		.isRemote = false
	};
	CAN_ConfigRxBuff(&can_pal2_instance, RX_MAILBOX_CAN1, &Rx_buffCfg, Rx_Filter);
	CAN_ConfigTxBuff(&can_pal2_instance, TX_MAILBOX_CAN1, &Tx_buffCfg);
	CAN_SetRxFilter(&can_pal2_instance,CAN_MSG_ID_STD,RX_MAILBOX_CAN1,0);
	CAN_InstallEventCallback(&can_pal2_instance,&CAN1_Callback_Func,(void*)0);
	CAN_Receive(&can_pal2_instance, RX_MAILBOX_CAN1, &recvMsg_CAN1);
}

void CAN2_Init(void)
{
	CAN_Init(&can_pal3_instance, &can_pal3_Config0);
	can_buff_config_t Rx_buffCfg =  {
		.enableFD = false,
		.enableBRS = false,
		.fdPadding = 0U,
		.idType = CAN_MSG_ID_STD,
		.isRemote = false
	};

	can_buff_config_t Tx_buffCfg =  {
		.enableFD = false,
		.enableBRS = false,
		.fdPadding = 0U,
		.idType = CAN_MSG_ID_STD,
		.isRemote = false
	};
	CAN_ConfigRxBuff(&can_pal3_instance, RX_MAILBOX_CAN2, &Rx_buffCfg, Rx_Filter);
	CAN_ConfigTxBuff(&can_pal3_instance, TX_MAILBOX_CAN2, &Tx_buffCfg);
	CAN_SetRxFilter(&can_pal3_instance,CAN_MSG_ID_STD,RX_MAILBOX_CAN2,0);
	CAN_InstallEventCallback(&can_pal3_instance,&CAN2_Callback_Func,(void*)0);
	CAN_Receive(&can_pal3_instance, RX_MAILBOX_CAN2, &recvMsg_CAN2);
}
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

	EDMA_DRV_Init(&dmaController1_State, &dmaController1_InitConfig0, edmaChnStateArray, edmaChnConfigArray, EDMA_CONFIGURED_CHANNELS_COUNT);  // 初始化 eDMA
	LPUART_DRV_Init(INST_LPUART1, &lpuart1_State, &lpuart1_InitConfig0);  // 初始化串口
	LPUART_DRV_InstallRxCallback(INST_LPUART1, LPUART1_RX_ISR, NULL);  // 安装接收中断回调函数
	LPUART_DRV_ReceiveData(INST_LPUART1, buffer, 1);  // 开启串口接收,每次接收一个字节,并安装中断

	CAN0_Init();
	CAN1_Init();
	CAN2_Init();

	PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);  // 初始化IO
	while(1)
	{
		can_message_t Tx_msg1 = {
			.cs = 0U,
			.id = 0x01,
			.data[0] = 0x0,
			.data[1] = 0x1,
			.data[2] = 0x2,
			.data[3] = 0x3,
			.data[4] = 0x4,
			.data[5] = 0x5,
			.data[6] = 0x6,
			.data[7] = 0x7,
			.length = 8
		};
		CAN_Send(&can_pal1_instance, TX_MAILBOX_CAN0, &Tx_msg1);
		u1_printf("CAN0发送报文\r\n");
		OSIF_TimeDelay(500);

		can_message_t Tx_msg2 = {
			.cs = 0U,
			.id = 0x02,
			.data[0] = 0x20,
			.data[1] = 0x21,
			.data[2] = 0x22,
			.data[3] = 0x23,
			.data[4] = 0x24,
			.data[5] = 0x25,
			.data[6] = 0x26,
			.data[7] = 0x27,
			.length = 8
		};
		CAN_Send(&can_pal2_instance, TX_MAILBOX_CAN1, &Tx_msg2);
		u1_printf("CAN1发送报文\r\n");
		OSIF_TimeDelay(500);

		can_message_t Tx_msg3 = {
			.cs = 0U,
			.id = 0x03,
			.data[0] = 0x30,
			.data[1] = 0x31,
			.data[2] = 0x32,
			.data[3] = 0x33,
			.data[4] = 0x34,
			.data[5] = 0x35,
			.data[6] = 0x36,
			.data[7] = 0x37,
			.length = 8
		};
		CAN_Send(&can_pal3_instance, TX_MAILBOX_CAN2, &Tx_msg3);
		u1_printf("CAN2发送报文\r\n");
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
