#include "led_controller.h"
#include "drivers/led/led.h"
#include "drivers/lcd/lcd.h"

#include <FreeRTOS.h>
#include <task.h>

int8_t lcd_delay(uint32_t ms) {
    vTaskDelay(ms);
    return 0;
}

void led0_controller_task(void *pv_arg)
{
    struct led led0 = {
        .port = MDR_PORTB,
        .pin = PORT_Pin_0,
    };

    struct lcd lcd0 = {
        .db_pins = {PORT_Pin_0, PORT_Pin_1, PORT_Pin_2, PORT_Pin_3, PORT_Pin_4, PORT_Pin_5, PORT_Pin_2, PORT_Pin_3},
        .db_ports = {MDR_PORTA, MDR_PORTA, MDR_PORTA, MDR_PORTA, MDR_PORTA, MDR_PORTA, MDR_PORTF, MDR_PORTF},
        .a0_pin = PORT_Pin_0,
        .a0_port = MDR_PORTC,
        .e_pin = PORT_Pin_1,
        .e_port = MDR_PORTC,
        .e1_pin = PORT_Pin_7,
        .e1_port = MDR_PORTB,
        .e2_pin = PORT_Pin_8,
        .e2_port = MDR_PORTB,
        .res_pin = PORT_Pin_9,
        .res_port = MDR_PORTB,
        .rw_pin = PORT_Pin_10,
        .rw_port = MDR_PORTB
    };

    lcd_init(&lcd0);    

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

