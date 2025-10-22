#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED1 2 // LED On Board ESP32 DOIT

void vTaskLED(void *pvParameter){ 
    gpio_reset_pin(LED1); // GPIO Reset
    gpio_set_direction(LED1, GPIO_MODE_OUTPUT); // Sett GPIO LED1 sebagai MODE OUTPUT

    while(1){
        gpio_set_level(LED1, 1); // LED Nyala 
        vTaskDelay(pdMS_TO_TICKS(500)); // 0.5 detik  
        gpio_set_level(LED1, 0); // LED Mati
        vTaskDelay(pdMS_TO_TICKS(500)); // 0.5 detik
    }
}



void app_main(void){
    xTaskCreate(vTaskLED, "LED Blink", 1024, NULL, 1, NULL);
}

