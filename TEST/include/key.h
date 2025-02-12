#ifndef KEY_H_
#define KEY_H_

#include "Cpu.h"
#include <stdio.h>
#include <stdint.h>

#define KEY1 ((PINS_DRV_ReadPins(PTC) >> 12) & 0x01)  // 读取KEY1 PTC12的 电平
#define KEY2 ((PINS_DRV_ReadPins(PTC) >> 13) & 0x01)  // 读取KEY2 PTC13的 电平
#define KEY3 ((PINS_DRV_ReadPins(PTB) >> 2) & 0x01)  // 读取KEY3 PTB2的 电平

#endif
