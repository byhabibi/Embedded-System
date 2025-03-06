/***********************************************************
 * File: main.c
 * Author: Burhanudin Yusuf Habibi
 * Date: 06/03/2025
 * Description: C To Make Communication with UART Protocols
 *              Using USART1 on APB2ENR
 ***********************************************************/

#include "stm32f103xb.h"

void UART1(void) {
    RCC->APB2ENR |= (1 << 2);  // Activated clock GPIOA
    RCC->APB2ENR |= (1 << 14); // Activated clock USART1 with clock default 72MHz

    GPIOA->CRH &= ~(0xF << 4); // Clear PA9 (TX)
    GPIOA->CRH |= (0xB << 4);  // PA9 as an Alternate Function Push-Pull

    USART1->BRR = 0x271; // Baud rate 115200 (72MHz / 115200 = 625 = 0x217 Hex)
    USART1->CR1 |= (1 << 3) | (1 << 13); // Enable TX (bit 3), USART (bit 13)
}

void UART1_Char(char c) {
    while (!(USART1->SR & (1 << 7))); // Waiting untill TXE = 0, if TXE = 1 while is not run
    USART1->DR = c;                   // Send char
}

void UART1_Sendchar(char *str) {
    while (*str) {
        UART1_Char(*str++);        
    }
}

int main(void) {
    UART1();

    while (1) {
        UART1_Sendchar("Hii STM32\r\n");
        for (volatile int i = 0; i < 500000; i++); // Delay
    }
}
