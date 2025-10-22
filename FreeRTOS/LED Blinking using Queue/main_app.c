#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED1 GPIO_NUM_13	// Gunakan Pin 13 untuk LED 1
#define LED2 GPIO_NUM_12	// Gunakan Pin 12 untuk LED 2

QueueHandle_t xQueue;	// Deklarasi Queue

void vTaskLED(void *pvParameter){
    int count = 0;
    gpio_reset_pin(LED1);
    gpio_set_direction(LED1, GPIO_MODE_OUTPUT);	

    while(1){
        gpio_set_level(LED1, 1);
        vTaskDelay(pdMS_TO_TICKS(500));  
        gpio_set_level(LED1, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
        count++;
        if(count == 3){		// Jika nilai count = 3
          xQueueSend(xQueue, &count, portMAX_DELAY);	// Mengirim Queue berdasarakan nilai variabel count
          count = 0;		// Nilai variabel count di reset jadi 0
        }  
    }
}


void vTaskLED2(void *pvParameter){
    int receivedCount = 0;
    gpio_reset_pin(LED2);
    gpio_set_direction(LED2, GPIO_MODE_OUTPUT);

    while(1){
        if(xQueueReceive(xQueue, &receivedCount, portMAX_DELAY) == pdPASS){		// Menerima nilai variabel count dengan receivedCount
          gpio_set_level(LED2, 1);
          vTaskDelay(pdMS_TO_TICKS(750));  
          gpio_set_level(LED2, 0);
          vTaskDelay(pdMS_TO_TICKS(1000));
        }
      
    }
}


void app_main(void){
    xQueue = xQueueCreate(5, sizeof(int));	// Ukuran buffer Queue
    xTaskCreate(vTaskLED, "LED Blink", 1024, NULL, 1, NULL);
    xTaskCreate(vTaskLED2, "LED2 Blinking", 1024, NULL, 2, NULL);
}

