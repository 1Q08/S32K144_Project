#include "cpu.h"
#include "uart.h"

#include <stdio.h>
#include <string.h>
#include "stdarg.h"
#include <stdint.h>
#include <stdbool.h>

char USART1_TX_BUF[200];
void u1_printf(char* fmt,...)
{
	uint32_t bytesRemaining;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART1_TX_BUF,fmt,ap);
	va_end(ap);
	LPUART_DRV_SendData(INST_LPUART1, (uint8_t *)USART1_TX_BUF, strlen(USART1_TX_BUF));  // ����
	while (LPUART_DRV_GetTransmitStatus(INST_LPUART1, &bytesRemaining)
			!= STATUS_SUCCESS)  {}
}

#define BUFFER_SIZE 256U
uint8_t buffer[200];
uint8_t rxdata[200];
uint8_t bufferIdx;
uint32_t bytesRemaining;
status_t status;
uint8_t triger;
void LPUART1_RX_ISR (void *driverState, uart_event_t event, void *userData)
 {
	(void) driverState;
	(void) userData;

	if(LPUART_DRV_GetReceiveStatus(INST_LPUART1, &bytesRemaining) != STATUS_BUSY)
	{
		status = LPUART_DRV_GetReceiveStatus(INST_LPUART1, &bytesRemaining); //�������ݽ��ճɹ�
		if(status == STATUS_SUCCESS)
		{
			/* Ϊ���յ����ַ��������ֹ�� */
			bufferIdx++;
			triger =1;
			buffer[bufferIdx] = 0U;
			/* �����ջ����ļ����Ƶ�rxdata���� */
			memcpy(rxdata,buffer,bufferIdx);
			memset(buffer,0,sizeof(buffer));
			//LPUART_DRV_SendDataBlocking(INST_LPUART1, buffer, bufferIdx, 100UL);
			/* Reset the buffer index to start a new reception */
			bufferIdx = 0U;
			/* ��ɲ���������жϱ�־λ�����¿�ʼ���մ������� */
			LPUART_DRV_ReceiveData(INST_LPUART1, buffer, 1U);
		}
		else
		{
			// error handle
			LPUART_DRV_ReceiveData(INST_LPUART1, buffer, 1U);
		}
	   }

	/* ���ڽ��ջ������¼� */
	if(event==UART_EVENT_RX_FULL)
		{
		/* �ж��Ƿ��յ����з� */
		if ((buffer[bufferIdx] != '\n') && (bufferIdx != (BUFFER_SIZE - 2U)))
			{
			/* ÿ����һ�ֽ�����,�ͽ�����λ��ָ���������һλ,ֱ�����յ����з� */
				bufferIdx++;
				LPUART_DRV_SetRxBuffer(INST_LPUART1, &buffer[bufferIdx], 1U);
			}
		}
}
