#ifndef __PIODEFS_H
#define __PIODEFS_H

enum IO_Pins
{
  PIN_0 = 0x00000001,
  PIN_1 = 0x00010002,
  PIN_2 = 0x00020004,
  PIN_3 = 0x00030008,
  PIN_4 = 0x00040010,
  PIN_5 = 0x00050020,
  PIN_6 = 0x00060040,
  PIN_7 = 0x00070080,
  PIN_8 = 0x00080100,
  PIN_9 = 0x00090200,
  PIN_10 = 0x000A0400,
  PIN_11 = 0x000B0800,
  PIN_12 = 0x000C1000,
  PIN_13 = 0x000D2000,
  PIN_14 = 0x000E4000,
  PIN_15 = 0x000F8000
};

#define PIN_MSK(X)              ((uint16_t)(((uint32_t)X)&0x0000FFFF))        /*Get pin mask macro*/
#define PIN_NUM(X)              ((uint16_t)(((uint32_t)X)>>16))               /*Get pin number macro*/

#endif