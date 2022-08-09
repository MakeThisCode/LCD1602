#ifndef __LCD1602_H
#define __LCD1602_H

//#include "stm32f1xx.h"
#include "stm32f4xx.h"
#include "piodefs.h"

enum LCD1602_DataLength
{
  LCD1602_DL_8bit,
  LCD1602_DL_4bit
};

enum LCD1602_LineNumber
{
  LCD1602_LN_1,
  LCD1602_LN_2
};

enum LCD1602_DotsFormat
{
  LCD1602_DF_5x8,
  LCD1602_DF_5x11
};

enum LCD1602_CursorType
{
  LCD1602_CT_Single,
  LCD1602_CT_Blink,
  LCD1602_CT_None
};

enum LCD1602_ShiftTarget
{
  LCD1602_ST_Cursor,
  LCD1602_ST_Display
};

enum LCD1602_ShiftDir
{
  LCD1602_SD_Left,
  LCD1602_SD_Right
};

#define LCD_D0_Port     GPIOA
#define LCD_D0_Pin      PIN_7
#define LCD_D1_Port     GPIOA
#define LCD_D1_Pin      PIN_6
#define LCD_D2_Port     GPIOA
#define LCD_D2_Pin      PIN_5
#define LCD_D3_Port     GPIOA
#define LCD_D3_Pin      PIN_4
#define LCD_D4_Port     GPIOA
#define LCD_D4_Pin      PIN_3
#define LCD_D5_Port     GPIOA
#define LCD_D5_Pin      PIN_2
#define LCD_D6_Port     GPIOA
#define LCD_D6_Pin      PIN_1
#define LCD_D7_Port     GPIOA
#define LCD_D7_Pin      PIN_0
#define LCD_E_Port      GPIOA
#define LCD_E_Pin       PIN_8
#define LCD_RS_Port     GPIOA
#define LCD_RS_Pin      PIN_10
#define LCD_RW_Port     GPIOA
#define LCD_RW_Pin      PIN_9

#define LCD_DataLEngth  LCD1602_DL_8bit

#define SYSFREQ         84000000


/*Base functions*/
void LCD1602_ClearDisplay(void);
void LCD1602_ReturnHome(void);
void LCD1602_FunctionSet(enum LCD1602_LineNumber, 
                         enum LCD1602_DotsFormat);
void LCD1602_DisplayOn(enum LCD1602_CursorType);
void LCD1602_DisplayOff(void);
void LCD1602_WriteData(uint8_t);
void LCD1602_CursorDisplayShift(enum LCD1602_ShiftTarget, 
                                enum LCD1602_ShiftDir);
void LCD1602_SetDdramAddress(uint8_t);
void LCD1602_SetCgramAddress(uint8_t);
uint8_t LCD1602_ReadAddrCounter(void);
uint8_t LCD1602_ReadRamData(void);
/*Additional functions*/
void LCD1602_WriteString(char*);
/*Private functions*/
void _LCD1602_SetDataBus(uint8_t);
void _LCD1602_EnableData(uint8_t);
void _LCD1602_Delay(uint16_t);
void _LCD1602_EnableSignal(void);
void _LCD1602_WaitForExecution(void);
void _LCD1602_PinToInputMode(GPIO_TypeDef*, 
                             enum IO_Pins);
void _LCD1602_PinToOutputMode(GPIO_TypeDef*,
                              enum IO_Pins);

#endif
