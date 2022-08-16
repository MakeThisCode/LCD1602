# LCD1602
Library for 1602 display based on ST7066 controller

The library is suitable for STM32F1 and STM32F4 microcontrollers.
The library uses CMSIS. To use the library, you need to include CMSIS header - "stm32f1xx.h" or "stm32f4xx.h" in your project.

# Quick guide

First you need to initialize the pins to work with the display. Use the following settings:

<table>
<tr>
  <td>GPIO output level</td>
  <td>Low</td>
</tr>
<tr>
  <td>GPIO mode</td>
  <td>Output Push Pull</td>
</tr>
<tr>
  <td>GPIO Pull-up/Pull-down</td>
  <td>Pull-down</td>
</tr>
</table>

In 4-bit mode, the outputs of the display module `D0-D3` must be physically pulled to the ground.

***Warning!***

***If you are using a 5 volt LCD, check if the microcontroller pins are 5 volt tolerant. Otherwise, use the voltage level converter.***

In the header file `lcd1602.h` there is a define block where you can set your own values:

```c
#define LCD_D0_Port     GPIOA               //D0 I/O port
#define LCD_D0_Pin      PIN_7               //D0 I/O pin
#define LCD_D1_Port     GPIOA               //...
#define LCD_D1_Pin      PIN_6               //...
#define LCD_D2_Port     GPIOA               //...
#define LCD_D2_Pin      PIN_5               //...
#define LCD_D3_Port     GPIOA               //...
#define LCD_D3_Pin      PIN_4               //...
#define LCD_D4_Port     GPIOA               //...
#define LCD_D4_Pin      PIN_3               //...
#define LCD_D5_Port     GPIOA               //...
#define LCD_D5_Pin      PIN_2               //...
#define LCD_D6_Port     GPIOA               //...
#define LCD_D6_Pin      PIN_1               //...
#define LCD_D7_Port     GPIOA               //...
#define LCD_D7_Pin      PIN_0               //...
#define LCD_E_Port      GPIOA               //Enable signal I/O port
#define LCD_E_Pin       PIN_8               //Enable signal I/O pin
#define LCD_RS_Port     GPIOA               //Register select I/O port
#define LCD_RS_Pin      PIN_10              //Register select I/O pin
#define LCD_RW_Port     GPIOA               //Read/Write signal I/O port
#define LCD_RW_Pin      PIN_9               //Read/Write signal I/O pin

#define LCD_DataLEngth  LCD1602_DL_8bit     //4-bit or 8-bit MPU interface

#define SYSFREQ         84000000            //HCLK frequency (Hz)
```

In 4-bit mode, leave the default values for `D0-D3`. In this mode, they will not be used.

It is recommended to use functions with `LCD1602` prefix. Functions with the prefix `_LCD1602` are private and are used for internal purposes.
