#include "cpu.h"
#include "key.h"
#include "led.h"

void PORTC_IRQ(void)
{
	uint32_t flag = PINS_DRV_GetPortIntFlag(PORTC) & ((1 << 12) | (1 << 13));  // ��ȡ�жϱ�־λ״̬
	if(((flag >> 12) & 0x01) == 1)
	{
		LED_G(1);  // �̵�
		LED_R(0);  // ���
		LED_Y(1);  // �Ƶ�
		LED_B(0);  // ����
	}
	else if(((flag >> 13) & 0x01) == 1)
	{
		LED_G(0);  // �̵�
		LED_R(1);  // ���
		LED_Y(0);  // �Ƶ�
		LED_B(1);  // ����
	}
	else
	{
	}
	PINS_DRV_ClearPortIntFlagCmd(PORTC);  // ��� IRQ ��־
}
