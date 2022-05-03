#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define LED_PIN1 4
#define LED_PIN2 2

void led_blink1(void *pvParams) {
    gpio_pad_select_gpio(LED_PIN1);
    gpio_set_direction (LED_PIN1,GPIO_MODE_OUTPUT);
    while (1) {
        gpio_set_level(LED_PIN1,0);
        vTaskDelay(500/portTICK_RATE_MS);
        gpio_set_level(LED_PIN1,1);
        vTaskDelay(500/portTICK_RATE_MS);
	printf("Task1 is running on Core %d\n", xPortGetCoreID());

    }
}

void led_blink2(void *pvParams) {
    gpio_pad_select_gpio(LED_PIN2);
    gpio_set_direction (LED_PIN2,GPIO_MODE_OUTPUT);
    while (1) {
        gpio_set_level(LED_PIN2,0);
        vTaskDelay(1000/portTICK_RATE_MS);
        gpio_set_level(LED_PIN2,1);
        vTaskDelay(1000/portTICK_RATE_MS);
	printf("Task2 is running on Core %d\n", xPortGetCoreID());
    }
}


void blink_led() {
    xTaskCreatePinnedToCore(&led_blink1,"LED_BLINK1",10000,NULL,1,NULL,0);
    xTaskCreatePinnedToCore(&led_blink2,"LED_BLINK2",10000,NULL,1,NULL,1);
}