#include "lcd_controller.h"
#include "drivers/lcd/lcd.h"
#include "MDR32FxQI_utils.h"

#include <FreeRTOS.h>
#include <task.h>

void DELAY_PROGRAM_WaitLoopsAsm(uint32_t Loops) {}

int8_t lcd_delay(uint32_t us) {
    DELAY_WaitUs(us);
    return 0;
}

void lcd_controller_task(void *pv_arg)
{
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
    DELAY_Init(DELAY_MODE_DWT);

    lcd_init(&lcd0);    

    while (1) {
        vTaskDelay(1);
    }
}