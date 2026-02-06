#include <esp_log.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <driver/gpio.h>

#define delay(ms) vTaskDelay(pdMS_TO_TICKS(ms))

static const int GPIO[] = {4, 7, 17, 19, 9, 11, 14, 2};
static const int PWR[] = {5, 15, 18, 3, 10, 13, 45, 1};
static const int DIR[] = {6, 16, 8, 20, 46, 12, 48, 38};

static const char *TAG = "main";



extern "C" void app_main(void)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL < GPIO_NUM_2),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
    

    while (1) {
        int level = gpio_get_level(GPIO_NUM_2);
        ESP_LOGI(TAG,"Hello World");

        delay(1000);
    }
}
