/**************************************************************
 * File: main.c
 * Author: Burhanudin Yusuf Habibi
 * Date: 05/03/2025
 * Description: C To Make LED ON with Push Button Bare Metal C 
 *              on STM32F103x Blue Pill
 **************************************************************/

#include <stdint.h>
#include "stm32f103xb.h"

#define RCC_BASE   0x40021000
#define GPIOA_BASE 0x40010800

int main(void){
  RCC->APB2ENR |= (1 << 2);      // Activated GPIOA Pin

  GPIOA->CRL &= ~(0xF << 20);    // Choose the PA5 GPIOA at bit 20 in Control Register Low and Clear bit for PA5
  GPIOA->CRL |= (0x2 << 20);     // Set mode PA5 for Output with 2MHz clock

  GPIOA->CRL &= ~(0xF << 0);     // Choose the PA0 GPIOA at bit 0 in Control Register Low and Clear bit for PA0
  GPIOA->CRL |= (0x8 << 0);      // Set mode PA0 for Input    

  GPIOA->ODR |= (1 << 0);        // Set PA0 for input with pull up based condition for PA0 is HIGH

  while(1){
    if(!(GPIOA->IDR & (1 << 0))){  // Make condition with NOT operator (!) for if Push Button is pressed condition is HIGH
      GPIOA->ODR |= (1 << 5);      // LED ON at PA5
    }else{
      GPIOA->ODR &= ~(1 << 5);     // LED OFF at PA5
    }
  }
}
