#include "lcd1602.h"

void LCD1602_ClearDisplay()
{
  /*RS - low, RW - low*/
  LCD_RS_Port->BSRR |= PIN_MSK(LCD_RS_Pin) << GPIO_BSRR_BR0_Pos;
  LCD_RW_Port->BSRR |= PIN_MSK(LCD_RW_Pin) << GPIO_BSRR_BR0_Pos;
  
  _LCD1602_EnableData(0x1);//b 0000 0001
  
  _LCD1602_WaitForExecution();
}

void LCD1602_ReturnHome()
{
  /*RS - low, RW - low*/
  LCD_RS_Port->BSRR |= PIN_MSK(LCD_RS_Pin) << GPIO_BSRR_BR0_Pos;
  LCD_RW_Port->BSRR |= PIN_MSK(LCD_RW_Pin) << GPIO_BSRR_BR0_Pos;
  
  _LCD1602_EnableData(0x2);//b 0000 0010
  
  _LCD1602_WaitForExecution();
}

void LCD1602_FunctionSet(enum LCD1602_LineNumber ln, 
                         enum LCD1602_DotsFormat df)
{
  /*RS - low, RW - low*/
  LCD_RS_Port->BSRR |= PIN_MSK(LCD_RS_Pin) << GPIO_BSRR_BR0_Pos;
  LCD_RW_Port->BSRR |= PIN_MSK(LCD_RW_Pin) << GPIO_BSRR_BR0_Pos;
  
  uint8_t data = 0x20;//b 0010 0000
  
  if(LCD_DataLEngth == LCD1602_DL_8bit)
  {
    data |= 0x10;//b 0001 0000
  }
  
  if(ln == LCD1602_LN_2)
  {
    data |= 0x8;//b 0000 1000
  }
  
  if(df == LCD1602_DF_5x11)
  {
    data |= 0x4;//b 0000 0100
  }
  
  _LCD1602_SetDataBus(data);
  _LCD1602_EnableSignal();
  
  _LCD1602_WaitForExecution();
}

void LCD1602_DisplayOn(enum LCD1602_CursorType ct)
{
  /*RS - low, RW - low*/
  LCD_RS_Port->BSRR |= PIN_MSK(LCD_RS_Pin) << GPIO_BSRR_BR0_Pos;
  LCD_RW_Port->BSRR |= PIN_MSK(LCD_RW_Pin) << GPIO_BSRR_BR0_Pos;
  
  uint8_t data = 0xC;//b 0000 1100
  
  if(ct == LCD1602_CT_Single)
  {
    data |= 0x2;//b 0000 0010
  }
  
  if(ct == LCD1602_CT_Blink)
  {
    data |= 0x1;//b 0000 0001
  }
  
  _LCD1602_EnableData(data);
  
  _LCD1602_WaitForExecution();
}

void LCD1602_DisplayOff()
{
  /*RS - low, RW - low*/
  LCD_RS_Port->BSRR |= PIN_MSK(LCD_RS_Pin) << GPIO_BSRR_BR0_Pos;
  LCD_RW_Port->BSRR |= PIN_MSK(LCD_RW_Pin) << GPIO_BSRR_BR0_Pos;
  
  _LCD1602_EnableData(0x8);//b 0000 1000
   
  _LCD1602_WaitForExecution();
}

void LCD1602_WriteData(uint8_t data)
{
  /*RS - high, RW - low*/
  LCD_RS_Port->BSRR |= PIN_MSK(LCD_RS_Pin) << GPIO_BSRR_BS0_Pos;
  LCD_RW_Port->BSRR |= PIN_MSK(LCD_RW_Pin) << GPIO_BSRR_BR0_Pos;
  
  _LCD1602_EnableData(data);
  
  _LCD1602_WaitForExecution();
}

void LCD1602_CursorDisplayShift(enum LCD1602_ShiftTarget st, 
                                enum LCD1602_ShiftDir sd)
{
  /*RS - low, RW - low*/
  LCD_RS_Port->BSRR |= PIN_MSK(LCD_RS_Pin) << GPIO_BSRR_BR0_Pos;
  LCD_RW_Port->BSRR |= PIN_MSK(LCD_RW_Pin) << GPIO_BSRR_BR0_Pos;
  
  uint8_t data = 0x10;//b 0001 0000
  
  if(st == LCD1602_ST_Display)
  {
    data |= 0x8;//b 0000 1000
  }
  
  if(sd == LCD1602_SD_Right)
  {
    data |= 0x4;//b 0000 0100
  }
  
  _LCD1602_EnableData(data);
  
  _LCD1602_WaitForExecution();
}

void LCD1602_SetDdramAddress(uint8_t addr)
{  
  /*RS - low, RW - low*/
  LCD_RS_Port->BSRR |= PIN_MSK(LCD_RS_Pin) << GPIO_BSRR_BR0_Pos;
  LCD_RW_Port->BSRR |= PIN_MSK(LCD_RW_Pin) << GPIO_BSRR_BR0_Pos;
  
  uint8_t data = 0x80;//b 1000 0000
  data |= (addr & 0x7F);//b 0111 1111
  
  _LCD1602_EnableData(data);
  
  _LCD1602_WaitForExecution();
}

void LCD1602_SetCgramAddress(uint8_t addr)
{
  /*RS - low, RW - low*/
  LCD_RS_Port->BSRR |= PIN_MSK(LCD_RS_Pin) << GPIO_BSRR_BR0_Pos;
  LCD_RW_Port->BSRR |= PIN_MSK(LCD_RW_Pin) << GPIO_BSRR_BR0_Pos;
  
  uint8_t data = 0x40;//b 0100 0000
  data |= (addr & 0x3F);//b 0011 1111
  
  _LCD1602_EnableData(data);
  
  _LCD1602_WaitForExecution();
}

uint8_t LCD1602_ReadAddrCounter()
{
  /*RS - low, RW - high*/
  LCD_RS_Port->BSRR |= PIN_MSK(LCD_RS_Pin) << GPIO_BSRR_BR0_Pos;
  LCD_RW_Port->BSRR |= PIN_MSK(LCD_RW_Pin) << GPIO_BSRR_BS0_Pos;
  
  uint8_t addr = 0;
  
  _LCD1602_PinToInputMode(LCD_D0_Port, LCD_D0_Pin);
  _LCD1602_PinToInputMode(LCD_D1_Port, LCD_D1_Pin);
  _LCD1602_PinToInputMode(LCD_D2_Port, LCD_D2_Pin);
  _LCD1602_PinToInputMode(LCD_D3_Port, LCD_D3_Pin);
  _LCD1602_PinToInputMode(LCD_D4_Port, LCD_D4_Pin);
  _LCD1602_PinToInputMode(LCD_D5_Port, LCD_D5_Pin);
  _LCD1602_PinToInputMode(LCD_D6_Port, LCD_D6_Pin);
  _LCD1602_PinToInputMode(LCD_D7_Port, LCD_D7_Pin);
  
  if(LCD_DataLEngth == LCD1602_DL_8bit)
  {
    LCD_E_Port->BSRR |= PIN_MSK(LCD_E_Pin) << GPIO_BSRR_BS0_Pos;
    _LCD1602_Delay(1);
    addr |= (LCD_D0_Port->IDR & PIN_MSK(LCD_D0_Pin)) ? (0x1 << 0x0) : 0x0;
    addr |= (LCD_D1_Port->IDR & PIN_MSK(LCD_D1_Pin)) ? (0x1 << 0x1) : 0x0;
    addr |= (LCD_D2_Port->IDR & PIN_MSK(LCD_D2_Pin)) ? (0x1 << 0x2) : 0x0;
    addr |= (LCD_D3_Port->IDR & PIN_MSK(LCD_D3_Pin)) ? (0x1 << 0x3) : 0x0;
    addr |= (LCD_D4_Port->IDR & PIN_MSK(LCD_D4_Pin)) ? (0x1 << 0x4) : 0x0;
    addr |= (LCD_D5_Port->IDR & PIN_MSK(LCD_D5_Pin)) ? (0x1 << 0x5) : 0x0;
    addr |= (LCD_D6_Port->IDR & PIN_MSK(LCD_D6_Pin)) ? (0x1 << 0x6) : 0x0;
    LCD_E_Port->BSRR |= PIN_MSK(LCD_E_Pin) << GPIO_BSRR_BR0_Pos;
  }
  else
  {
    LCD_E_Port->BSRR |= PIN_MSK(LCD_E_Pin) << GPIO_BSRR_BS0_Pos;
    _LCD1602_Delay(1);
    addr |= (LCD_D4_Port->IDR & PIN_MSK(LCD_D4_Pin)) ? (0x1 << 0x0) : 0x0;
    addr |= (LCD_D5_Port->IDR & PIN_MSK(LCD_D5_Pin)) ? (0x1 << 0x1) : 0x0;
    addr |= (LCD_D6_Port->IDR & PIN_MSK(LCD_D6_Pin)) ? (0x1 << 0x2) : 0x0;
    addr |= (LCD_D7_Port->IDR & PIN_MSK(LCD_D7_Pin)) ? (0x1 << 0x3) : 0x0;
    LCD_E_Port->BSRR |= PIN_MSK(LCD_E_Pin) << GPIO_BSRR_BR0_Pos;
    
    _LCD1602_Delay(1);
    LCD_E_Port->BSRR |= PIN_MSK(LCD_E_Pin) << GPIO_BSRR_BS0_Pos;
    _LCD1602_Delay(1);
    addr |= (LCD_D4_Port->IDR & PIN_MSK(LCD_D4_Pin)) ? (0x1 << 0x4) : 0x0;
    addr |= (LCD_D5_Port->IDR & PIN_MSK(LCD_D5_Pin)) ? (0x1 << 0x5) : 0x0;
    addr |= (LCD_D6_Port->IDR & PIN_MSK(LCD_D6_Pin)) ? (0x1 << 0x6) : 0x0;
    LCD_E_Port->BSRR |= PIN_MSK(LCD_E_Pin) << GPIO_BSRR_BR0_Pos;
  }
  
  _LCD1602_PinToOutputMode(LCD_D0_Port, LCD_D0_Pin);
  _LCD1602_PinToOutputMode(LCD_D1_Port, LCD_D1_Pin);
  _LCD1602_PinToOutputMode(LCD_D2_Port, LCD_D2_Pin);
  _LCD1602_PinToOutputMode(LCD_D3_Port, LCD_D3_Pin);
  _LCD1602_PinToOutputMode(LCD_D4_Port, LCD_D4_Pin);
  _LCD1602_PinToOutputMode(LCD_D5_Port, LCD_D5_Pin);
  _LCD1602_PinToOutputMode(LCD_D6_Port, LCD_D6_Pin);
  _LCD1602_PinToOutputMode(LCD_D7_Port, LCD_D7_Pin);
  
  return addr;
}

uint8_t LCD1602_ReadRamData()
{
  /*RS - high, RW - high*/
  LCD_RS_Port->BSRR |= PIN_MSK(LCD_RS_Pin) << GPIO_BSRR_BS0_Pos;
  LCD_RW_Port->BSRR |= PIN_MSK(LCD_RW_Pin) << GPIO_BSRR_BS0_Pos;
  
  uint8_t addr = 0;
  
  _LCD1602_PinToInputMode(LCD_D0_Port, LCD_D0_Pin);
  _LCD1602_PinToInputMode(LCD_D1_Port, LCD_D1_Pin);
  _LCD1602_PinToInputMode(LCD_D2_Port, LCD_D2_Pin);
  _LCD1602_PinToInputMode(LCD_D3_Port, LCD_D3_Pin);
  _LCD1602_PinToInputMode(LCD_D4_Port, LCD_D4_Pin);
  _LCD1602_PinToInputMode(LCD_D5_Port, LCD_D5_Pin);
  _LCD1602_PinToInputMode(LCD_D6_Port, LCD_D6_Pin);
  _LCD1602_PinToInputMode(LCD_D7_Port, LCD_D7_Pin);
  
  if(LCD_DataLEngth == LCD1602_DL_8bit)
  {
    LCD_E_Port->BSRR |= PIN_MSK(LCD_E_Pin) << GPIO_BSRR_BS0_Pos;
    _LCD1602_Delay(1);
    addr |= (LCD_D0_Port->IDR & PIN_MSK(LCD_D0_Pin)) ? (0x1 << 0x0) : 0x0;
    addr |= (LCD_D1_Port->IDR & PIN_MSK(LCD_D1_Pin)) ? (0x1 << 0x1) : 0x0;
    addr |= (LCD_D2_Port->IDR & PIN_MSK(LCD_D2_Pin)) ? (0x1 << 0x2) : 0x0;
    addr |= (LCD_D3_Port->IDR & PIN_MSK(LCD_D3_Pin)) ? (0x1 << 0x3) : 0x0;
    addr |= (LCD_D4_Port->IDR & PIN_MSK(LCD_D4_Pin)) ? (0x1 << 0x4) : 0x0;
    addr |= (LCD_D5_Port->IDR & PIN_MSK(LCD_D5_Pin)) ? (0x1 << 0x5) : 0x0;
    addr |= (LCD_D6_Port->IDR & PIN_MSK(LCD_D6_Pin)) ? (0x1 << 0x6) : 0x0;
    addr |= (LCD_D7_Port->IDR & PIN_MSK(LCD_D7_Pin)) ? (0x1 << 0x7) : 0x0;
    LCD_E_Port->BSRR |= PIN_MSK(LCD_E_Pin) << GPIO_BSRR_BR0_Pos;
  }
  else
  {
    LCD_E_Port->BSRR |= PIN_MSK(LCD_E_Pin) << GPIO_BSRR_BS0_Pos;
    _LCD1602_Delay(1);
    addr |= (LCD_D4_Port->IDR & PIN_MSK(LCD_D4_Pin)) ? (0x1 << 0x0) : 0x0;
    addr |= (LCD_D5_Port->IDR & PIN_MSK(LCD_D5_Pin)) ? (0x1 << 0x1) : 0x0;
    addr |= (LCD_D6_Port->IDR & PIN_MSK(LCD_D6_Pin)) ? (0x1 << 0x2) : 0x0;
    addr |= (LCD_D7_Port->IDR & PIN_MSK(LCD_D7_Pin)) ? (0x1 << 0x3) : 0x0;
    LCD_E_Port->BSRR |= PIN_MSK(LCD_E_Pin) << GPIO_BSRR_BR0_Pos;
    
    _LCD1602_Delay(1);
    LCD_E_Port->BSRR |= PIN_MSK(LCD_E_Pin) << GPIO_BSRR_BS0_Pos;
    _LCD1602_Delay(1);
    addr |= (LCD_D4_Port->IDR & PIN_MSK(LCD_D4_Pin)) ? (0x1 << 0x4) : 0x0;
    addr |= (LCD_D5_Port->IDR & PIN_MSK(LCD_D5_Pin)) ? (0x1 << 0x5) : 0x0;
    addr |= (LCD_D6_Port->IDR & PIN_MSK(LCD_D6_Pin)) ? (0x1 << 0x6) : 0x0;
    addr |= (LCD_D7_Port->IDR & PIN_MSK(LCD_D7_Pin)) ? (0x1 << 0x7) : 0x0;
    LCD_E_Port->BSRR |= PIN_MSK(LCD_E_Pin) << GPIO_BSRR_BR0_Pos;
  }
  
  _LCD1602_PinToOutputMode(LCD_D0_Port, LCD_D0_Pin);
  _LCD1602_PinToOutputMode(LCD_D1_Port, LCD_D1_Pin);
  _LCD1602_PinToOutputMode(LCD_D2_Port, LCD_D2_Pin);
  _LCD1602_PinToOutputMode(LCD_D3_Port, LCD_D3_Pin);
  _LCD1602_PinToOutputMode(LCD_D4_Port, LCD_D4_Pin);
  _LCD1602_PinToOutputMode(LCD_D5_Port, LCD_D5_Pin);
  _LCD1602_PinToOutputMode(LCD_D6_Port, LCD_D6_Pin);
  _LCD1602_PinToOutputMode(LCD_D7_Port, LCD_D7_Pin);
  
  return addr;
}

/*Additional functions*/
void LCD1602_WriteString(char* str)
{
  if(!str)
    return;
  
  int count = 0;
  
  while(*(str) && count < 0x50)
  {
    LCD1602_WriteData((uint8_t)*str++);
    count++;
  }
}

/*Private functions*/
void _LCD1602_SetDataBus(uint8_t data)
{
  LCD_D0_Port->BSRR |= ((data >> 0) & 0x1) ? (PIN_MSK(LCD_D0_Pin) << GPIO_BSRR_BS0_Pos) 
    : (PIN_MSK(LCD_D0_Pin) << GPIO_BSRR_BR0_Pos);
  LCD_D1_Port->BSRR |= ((data >> 1) & 0x1) ? (PIN_MSK(LCD_D1_Pin) << GPIO_BSRR_BS0_Pos) 
    : (PIN_MSK(LCD_D1_Pin) << GPIO_BSRR_BR0_Pos);
  LCD_D2_Port->BSRR |= ((data >> 2) & 0x1) ? (PIN_MSK(LCD_D2_Pin) << GPIO_BSRR_BS0_Pos) 
    : (PIN_MSK(LCD_D2_Pin) << GPIO_BSRR_BR0_Pos);
  LCD_D3_Port->BSRR |= ((data >> 3) & 0x1) ? (PIN_MSK(LCD_D3_Pin) << GPIO_BSRR_BS0_Pos) 
    : (PIN_MSK(LCD_D3_Pin) << GPIO_BSRR_BR0_Pos);
  LCD_D4_Port->BSRR |= ((data >> 4) & 0x1) ? (PIN_MSK(LCD_D4_Pin) << GPIO_BSRR_BS0_Pos) 
    : (PIN_MSK(LCD_D4_Pin) << GPIO_BSRR_BR0_Pos);
  LCD_D5_Port->BSRR |= ((data >> 5) & 0x1) ? (PIN_MSK(LCD_D5_Pin) << GPIO_BSRR_BS0_Pos) 
    : (PIN_MSK(LCD_D5_Pin) << GPIO_BSRR_BR0_Pos);
  LCD_D6_Port->BSRR |= ((data >> 6) & 0x1) ? (PIN_MSK(LCD_D6_Pin) << GPIO_BSRR_BS0_Pos) 
    : (PIN_MSK(LCD_D6_Pin) << GPIO_BSRR_BR0_Pos);
  LCD_D7_Port->BSRR |= ((data >> 7) & 0x1) ? (PIN_MSK(LCD_D7_Pin) << GPIO_BSRR_BS0_Pos) 
    : (PIN_MSK(LCD_D7_Pin) << GPIO_BSRR_BR0_Pos);
}

void _LCD1602_EnableData(uint8_t data)
{
  if(LCD_DataLEngth == LCD1602_DL_8bit)
  {
    _LCD1602_SetDataBus(data);
    _LCD1602_EnableSignal();
  }
  else
  {
    _LCD1602_SetDataBus(data & 0xF0);
    _LCD1602_EnableSignal();
    
    _LCD1602_SetDataBus(data << 4);
    _LCD1602_EnableSignal();
  }
}

void _LCD1602_Delay(uint16_t us)
{
  if(!us) return;
  uint32_t count = SYSFREQ / (us * 1000000);
  for(int i = 0; i < count; i++) asm("NOP");
}

void _LCD1602_EnableSignal()
{
  LCD_E_Port->BSRR |= PIN_MSK(LCD_E_Pin) << GPIO_BSRR_BS0_Pos;
  _LCD1602_Delay(1);
  LCD_E_Port->BSRR |= PIN_MSK(LCD_E_Pin) << GPIO_BSRR_BR0_Pos;
}

void _LCD1602_WaitForExecution()
{
  /*RS - low, RW - high*/
  LCD_RS_Port->BSRR |= PIN_MSK(LCD_RS_Pin) << GPIO_BSRR_BR0_Pos;
  LCD_RW_Port->BSRR |= PIN_MSK(LCD_RW_Pin) << GPIO_BSRR_BS0_Pos;
  
  _LCD1602_PinToInputMode(LCD_D7_Port, LCD_D7_Pin);
  
  uint16_t pinMsk = PIN_MSK(LCD_D7_Pin);
  
  if(LCD_DataLEngth == LCD1602_DL_8bit)
  {
    while(1)
    {
      LCD_E_Port->BSRR |= PIN_MSK(LCD_E_Pin) << GPIO_BSRR_BS0_Pos;
      _LCD1602_Delay(1);
      if(!(LCD_D7_Port->IDR & pinMsk)) break;
      LCD_E_Port->BSRR |= PIN_MSK(LCD_E_Pin) << GPIO_BSRR_BR0_Pos;
    }
  }
  else
  {
    while(1)
    {
      _LCD1602_EnableSignal();
      LCD_E_Port->BSRR |= PIN_MSK(LCD_E_Pin) << GPIO_BSRR_BS0_Pos;
      _LCD1602_Delay(1);
      if(!(LCD_D7_Port->IDR & pinMsk)) break;
      LCD_E_Port->BSRR |= PIN_MSK(LCD_E_Pin) << GPIO_BSRR_BR0_Pos;
      
    }
  }
  
  _LCD1602_PinToOutputMode(LCD_D7_Port, LCD_D7_Pin);
}

void _LCD1602_PinToInputMode(GPIO_TypeDef* port,
                             enum IO_Pins pin)
{
  uint16_t pinNum = PIN_NUM(pin);
  uint16_t pinMsk = PIN_MSK(pin);
  
  #ifdef STM32F1
  if(pinNum > 7)
  {
    port->ODR &= ~pinMsk;
    port->CRH &= ~(GPIO_CRH_MODE8_Msk << ((pinNum - 8)*4));
    port->CRH &= ~(GPIO_CRH_CNF8_Msk << ((pinNum - 8)*4));
    port->CRH |= (0x2 << GPIO_CRH_CNF8_Pos) << ((pinNum - 8)*4);
  }
  else
  {
    port->ODR &= ~pinMsk;
    port->CRL &= ~(GPIO_CRL_MODE0_Msk << (pinNum*4));
    port->CRL &= ~(GPIO_CRL_CNF0_Msk << (pinNum*4));
    port->CRL |= (0x2 << GPIO_CRL_CNF0_Pos) << (pinNum*4);
  }
  #else
  #ifdef STM32F4
    port->BSRR |= GPIO_BSRR_BR0_Msk << pinNum;
    port->MODER &= ~(GPIO_MODER_MODER0_Msk << (pinNum * 2));
    port->OTYPER &= ~pinMsk;
    port->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (pinNum * 2));
    port->OSPEEDR |= 0x1 << (pinNum * 2);
    port->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << (pinNum * 2));
    port->PUPDR |= 0x2 << (pinNum * 2);
  #else
  while(1);
  #endif
  #endif
}

void _LCD1602_PinToOutputMode(GPIO_TypeDef* port,
                              enum IO_Pins pin)
{
  uint16_t pinNum = PIN_NUM(pin);
  
  #ifdef STM32F1
  if(pinNum > 7)
  {
    port->CRH &= ~(GPIO_CRH_MODE8_Msk << ((pinNum - 8)*4));
    port->CRH |= (0x1 << GPIO_CRH_MODE8_Pos) << ((pinNum - 8)*4);
    port->CRH &= ~(GPIO_CRH_CNF8_Msk << ((pinNum - 8)*4));
  }
  else
  {
    port->CRL &= ~(GPIO_CRL_MODE0_Msk << (pinNum*4));
    port->CRL |= (0x1 << GPIO_CRL_MODE0_Pos) << (pinNum*4);
    port->CRL &= ~(GPIO_CRL_CNF0_Msk << (pinNum*4));
  }
  #else
  #ifdef STM32F4
    uint16_t pinMsk = PIN_MSK(pin);
    port->BSRR |= GPIO_BSRR_BR0_Msk << pinNum;
    port->MODER &= ~(GPIO_MODER_MODER0_Msk << (pinNum * 2));
    port->MODER |= 0x1 << (pinNum * 2);
    port->OTYPER &= ~pinMsk;
    port->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (pinNum * 2));
    port->OSPEEDR |= 0x1 << (pinNum * 2);
    port->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << (pinNum * 2));
    port->PUPDR |= 0x2 << (pinNum * 2);
  #else
  while(1);
  #endif
  #endif
}
