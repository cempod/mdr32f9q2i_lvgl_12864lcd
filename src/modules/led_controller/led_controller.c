#include "led_controller.h"
#include "drivers/led/led.h"
#include "drivers/lcd/lcd.h"

#include <FreeRTOS.h>
#include <task.h>

void led0_controller_task(void *pv_arg)
{
    struct led led0 = {
        .port = MDR_PORTB,
        .pin = PORT_Pin_0,
    };
    
    while (1) {
        led_toggle(&led0);
        vTaskDelay(200);
    }
}

void led1_controller_task(void *pv_arg)
{
    struct led led1 = {
        .port = MDR_PORTB,
        .pin = PORT_Pin_1,
    };

    while (1) {
        led_toggle(&led1);
        vTaskDelay(400);
    }
}

void led2_controller_task(void *pv_arg)
{
    struct led led2 = {
        .port = MDR_PORTB,
        .pin = PORT_Pin_2,
    };

    while (1) {
        led_toggle(&led2);
        vTaskDelay(800);
    }
}

void led3_controller_task(void *pv_arg)
{
    struct led led3 = {
        .port = MDR_PORTB,
        .pin = PORT_Pin_3,
    };

    while (1) {
        led_toggle(&led3);
        vTaskDelay(1600);
    }
}

