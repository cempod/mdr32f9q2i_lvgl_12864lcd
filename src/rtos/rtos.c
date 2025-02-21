#include "rtos.h"
#include "modules/led_controller/led_controller.h"
#include "modules/lcd_controller/lcd_controller.h"
#include <FreeRTOSConfig.h>

void threads_init(void)
{
    xTaskCreate(led0_controller_task, "led0_controller", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

    xTaskCreate(led1_controller_task, "led1_controller", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

    xTaskCreate(led2_controller_task, "led2_controller", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

    xTaskCreate(led3_controller_task, "led3_controller", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

    xTaskCreate(lcd_controller_task, "lcd_controller", configMINIMAL_STACK_SIZE * 3, NULL, tskIDLE_PRIORITY, NULL);

}

void kernel_start(void)
{
    vTaskStartScheduler();
}
