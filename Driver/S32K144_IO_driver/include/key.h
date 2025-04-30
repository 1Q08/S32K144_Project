#ifndef KEY_H_
#define KEY_H_

#include "Cpu.h"
#include <stdio.h>
#include <stdint.h>

#define KEY1 ((PINS_DRV_ReadPins(PTC) >> 12) & 0x01)  // ��ȡKEY1 PTC12�� ��ƽ
#define KEY2 ((PINS_DRV_ReadPins(PTC) >> 13) & 0x01)  // ��ȡKEY2 PTC13�� ��ƽ
#define KEY3 ((PINS_DRV_ReadPins(PTB) >> 2) & 0x01)  // ��ȡKEY3 PTB2�� ��ƽ

#endif
