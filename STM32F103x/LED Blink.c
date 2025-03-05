/*******************************************************
 * File: main.c
 * Author: Burhanudin Yusuf Habibi
 * Date: 05/03/2025
 * Description: C To Make LED Blinking with Bare Metal C 
 *              on STM32F103x Blue Pill
 ********************************************************/

#define RCC_BASE  0x40021000
#define GPIOA_BASE 0x40010800

#define RCC_APB2ENR  (*(volatile unsigned int *)(RCC_BASE + 0x18))
#define GPIOA_CRL    (*(volatile unsigned int *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR    (*(volatile unsigned int *)(GPIOA_BASE + 0x0C))

// You can also using #inlcude "stm32f103.h" library

void delay_ms(int ms) {
    for (int i = 0; i < ms * 1000; i++) {
        __NOP(); 
    }
}        // This function to make delay for LED


int main(void){
  RCC->APB2ENR | (1 << 2);         // Activated GPIO pins at APB2ENR
  
  GPIOA->CRL &= ~(0xF << 20);      // Choose the PA5 GPIOA at bit 20 at Control Register Low and Clear bit for PA5
  GPIOA->CRL |= (0x2 << 20);      // Set mode PA5 for Output with 2MHz clock
  
  while(1){
    GPIOA->ODR ^= (1 << 5);      // Set 1 (HIGH) for PA5 at bit 5 and clear to set 0 (LOW) for PA5
    delay_ms(1000);              // Delay 1000ms or 1s
  }
}

