#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"

#define core_0 0
const int led1 = 2;
SemaphoreHandle_t xSemaphore = NULL;

void vTask1()
{
    xSemaphoreTake(xSemaphore, portMAX_DELAY);
    gpio_set_direction(led1, GPIO_MODE_OUTPUT);
    for(int i = 0;i < 25;i++)
    {
        gpio_set_level(led1,0);
        vTaskDelay(1000/portTICK_RATE_MS);
        gpio_set_level(led1,1);
        vTaskDelay(1000/portTICK_RATE_MS);
	    printf("LED BLINK from from core %d!--\n", xPortGetCoreID() );
        printf("--PRIORITY 2--" );
        fflush(stdout);
    }
    printf("\n");
    xSemaphoreGive(xSemaphore);
    vTaskDelete(NULL);
}

void vTask2()
{
    xSemaphoreTake(xSemaphore, portMAX_DELAY);
    gpio_set_direction(led1, GPIO_MODE_OUTPUT);
    for(int i = 0;i < 9999;i++)
    {
        gpio_set_level(led1,0);
        vTaskDelay(1000/portTICK_RATE_MS);
        gpio_set_level(led1,1);
        vTaskDelay(1000/portTICK_RATE_MS);
	    printf("Hello world from core %d!--\n", xPortGetCoreID() );
        printf("--PRIORITY 1--" );

        fflush(stdout);
    }
    printf("\n");
    xSemaphoreGive(xSemaphore);
    vTaskDelete(NULL);
}

void priority(void)
{
    printf("\n");
    xSemaphore = xSemaphoreCreateMutex();

    xTaskCreate(vTask1, "Task1", 2048, NULL, 2, NULL,0);
    xTaskCreate(vTask2, "Task2", 2048, NULL, 1, NULL,0);
}