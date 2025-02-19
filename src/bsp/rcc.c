#include "rcc.h"

#include <MDR32FxQI_rst_clk.h>

void rcc_config(void)
{
	RST_CLK_DeInit();

	RST_CLK_HSEconfig(RST_CLK_HSE_ON);

	if (RST_CLK_HSEstatus() == ERROR) while (1);

	RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul10);

	RST_CLK_CPU_PLLcmd(ENABLE);

	if (RST_CLK_CPU_PLLstatus() == ERROR) while (1);

	RST_CLK_CPU_PLLuse(ENABLE);

	RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
}

