#ifndef LED_H_
#define LED_H_

#include "Cpu.h"
#include <stdio.h>
#include <stdint.h>

// 0µãÁÁ 1¿ªÆô
// PINS_DRV_WritePins(PTD, 1<<0 | 1<<1 | 1<<15  | 1<<16 );
#define LED_G(x) PINS_DRV_WritePin(PTD,16,x)  // ÂÌµÆ
#define LED_R(x) PINS_DRV_WritePin(PTD,15,x)  // ºìµÆ
#define LED_Y(x) PINS_DRV_WritePin(PTD,1,x)  // »ÆµÆ
#define LED_B(x) PINS_DRV_WritePin(PTD,0,x)  // À¶µÆ

#endif
