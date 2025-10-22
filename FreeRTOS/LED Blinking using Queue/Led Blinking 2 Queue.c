#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

#define LED1 12
#define LED2 13
#define LED3 14

QueueHandle_t xQueue1, xQueue2;  // Buat 2 Queue

void vTaskLED1(void *pvParameter){
  int count = 0;
  gpio_reset_pin(LED1);
  gpio_set_direction(LED1, GPIO_MODE_OUTPUT);

  while(1){
    gpio_set_level(LED1, 1);
    vTaskDelay(pdMS_TO_TICKS(500));
    gpio_set_level(LED1, 0);
    vTaskDelay(pdMS_TO_TICKS(500));

    count++;
    if(count == 10){    // 10 kali LED Blinking
        xQueueSend(xQueue1, &count, portMAX_DELAY);  // xQueue1, kirim data
        count = 0;
    }
  }
  
}

void vTaskLED2(void *pvParameter){
    int count = 0;
    gpio_reset_pin(LED2);
    gpio_set_direction(LED2, GPIO_MODE_OUTPUT);

    while(1){
        gpio_set_level(LED2, 1);
        vTaskDelay(pdMS_TO_TICKS(1000));
        gpio_set_level(LED2, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));

        count++;

        if(count == 5){    // 5 kali LED Blinking
            xQueueSend(xQueue2, &count, portMAX_DELAY);  // xQueue2, kirim data
            count = 0;
        }
    }
}

void vTaskLED3(void *pvParameter){
    int receivedCount = 0;

    gpio_reset_pin(LED3);
    gpio_set_direction(LED3, GPIO_MODE_OUTPUT);

    while(1){
      if((xQueueReceive(xQueue1, &receivedCount, portMAX_DELAY) == pdPASS) || (xQueueReceive(xQueue2, &receivedCount, portMAX_DELAY) == pdPASS)){
      //xQueue1 dan xQueue2 dipisah dalam if karena ada 2 kondisi untuk pengiriman buffer Queue 
        gpio_set_level(LED3, 1);
        vTaskDelay(pdMS_TO_TICKS(1000));
        gpio_set_level(LED3, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));
      }
    }
}

void app_main(){
  xQueue1 = xQueueCreate(5, sizeof(int));    // Create Queue1
  xQueue2 = xQueueCreate(5, sizeof(int));    // Create Queue2
  xTaskCreate(vTaskLED1, "LED1", 1024, NULL, 3, NULL);
  xTaskCreate(vTaskLED2, "LED2", 1024, NULL, 2, NULL);
  xTaskCreate(vTaskLED3, "LED3", 1024, NULL, 1, NULL);

}
