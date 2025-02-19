#include "bsp.h"
#include "rtos.h"

#include <stdint.h>

#include <MDR32FxQI_port.h>
#include <MDR32FxQI_utils.h>

void led0_task(void *pv_arg);
void led1_task(void *pv_arg);
void led2_task(void *pv_arg);
void led3_task(void *pv_arg);

int main(void)
{
    bsp_init();

    threads_init();

    kernel_start();

    while (1) {
        ;
    }
}


