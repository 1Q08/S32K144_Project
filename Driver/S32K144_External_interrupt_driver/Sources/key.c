#include "cpu.h"
#include "key.h"
#include "led.h"

void PORTC_IRQ(void)
{
	uint32_t flag = PINS_DRV_GetPortIntFlag(PORTC) & ((1 << 12) | (1 << 13));  // »ñÈ¡ÖÐ¶Ï±êÖ¾Î»×´Ì¬
	if(((flag >> 12) & 0x01) == 1)
	{
		LED_G(1);  // ÂÌµÆ
		LED_R(0);  // ºìµÆ
		LED_Y(1);  // »ÆµÆ
		LED_B(0);  // À¶µÆ
	}
	else if(((flag >> 13) & 0x01) == 1)
	{
		LED_G(0);  // ÂÌµÆ
		LED_R(1);  // ºìµÆ
		LED_Y(0);  // »ÆµÆ
		LED_B(1);  // À¶µÆ
	}
	else
	{
	}
	PINS_DRV_ClearPortIntFlagCmd(PORTC);  // Çå³ý IRQ ±êÖ¾
}
