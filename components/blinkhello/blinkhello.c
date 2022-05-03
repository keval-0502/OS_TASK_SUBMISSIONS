#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define LED_PIN1 19
#define LED_PIN2 2

void led_blink1(void *pvParams) {
    gpio_pad_select_gpio(LED_PIN1);
    gpio_set_direction (LED_PIN1,GPIO_MODE_OUTPUT);
    while (1) {
        gpio_set_level(LED_PIN1,0);
        vTaskDelay(500/portTICK_RATE_MS);
        gpio_set_level(LED_PIN1,1);
        vTaskDelay(500/portTICK_RATE_MS);
	printf("LED is blinking on Core %d\n", xPortGetCoreID());

    }
}

void hello_world(void *pvParams) {
    gpio_pad_select_gpio(LED_PIN2);
    gpio_set_direction (LED_PIN2,GPIO_MODE_OUTPUT);
    while (1) {
        gpio_set_level(LED_PIN2,0);
        vTaskDelay(500/portTICK_RATE_MS);
        gpio_set_level(LED_PIN2,1);
        vTaskDelay(500/portTICK_RATE_MS);
	printf("Hello World is printing on % d \n", xPortGetCoreID());
    }
}
void blink_hello() {
    xTaskCreatePinnedToCore(&led_blink1,"LED_BLINK1",10000,NULL,1,NULL,0);
    xTaskCreatePinnedToCore(&hello_world,"hello world",10000,NULL,1,NULL,1);
}