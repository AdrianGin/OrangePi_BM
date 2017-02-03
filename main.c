/*
 * main.c
 *
 *  Created on: 3/02/2017
 *      Author: Adrian Gin
 */


#include <stdint.h>

#define CCU_ADDRESS (0x01C20000)
#define BUS_CLK_GATING_REG2 (CCU_ADDRESS + 0x0068)
#define PIO_GATING_BIT  (1<<5)
#define PIO_BASE_ADDR (0x01C20800)
#define PA_CFG2_REG (PIO_BASE_ADDR + 0x08)
#define PA_DATA_REG (PIO_BASE_ADDR + 0x10)
#define BUS_SOFT_RST_REG3 (CCU_ADDRESS + 0x2D0)


#define CPUS_CLK_BASE_ADDR (0x01f01400)
#define CPUS_APB0_GATE     *(volatile unsigned int*)(CPUS_CLK_BASE_ADDR + 0x28)

#define PIO_L_BASE_ADDR (0x01F02C00)


#define R_PIO_GATING_BIT  (1<<0)

#define PL_CFG1_REG *(volatile unsigned int*)(PIO_L_BASE_ADDR + 0x04)
#define PL_DATA_REG *(volatile unsigned int*)(PIO_L_BASE_ADDR + 0x10)


/* A workaround for https://patchwork.ozlabs.org/patch/622173 */
void __attribute__((section(".text"))) __attribute__((naked)) _start(void)
{
	asm volatile("b     main             \n"
		     ".long 0xffffffff       \n"
		     ".long 0xffffffff       \n"
		     ".long 0xffffffff       \n");
}


#define BUS_CLK_GATE2 *(volatile unsigned int*)(BUS_CLK_GATING_REG2)
volatile unsigned int* BUS_SOFT_RST3;
#define PA_CFG2 *(volatile unsigned int*)(PA_CFG2_REG)
#define PA_DATA *(volatile unsigned int*)(PA_DATA_REG)

int main(void)
{

	asm volatile("mov sp, #0x8000\n");

	uint32_t tim;
	uint32_t tim2;
	uint32_t tim3;

	CPUS_APB0_GATE |= R_PIO_GATING_BIT;

		BUS_CLK_GATE2 |= PIO_GATING_BIT;


		PA_CFG2 &= ~(0x07 << 4);
		PA_CFG2 |=  (0x01 << 4);

		PL_CFG1_REG &= ~(0x07 << 8);
		PL_CFG1_REG |= (0x01 << 8);

	while(1)
	{

		PL_DATA_REG &= ~(0x01 << 10);
		PA_DATA |= (0x1 << 17);


		for(tim = 0; tim < 2000; tim++)
		{
			for(tim2 = 0; tim2 < 10000; tim2++)
			{
				asm volatile("nop\n");
			}

		}

		PA_DATA &= (~(0x1 << 17));
		PL_DATA_REG |= (0x01 << 10);


		for(tim = 0; tim < 2000; tim++)
		{
			for(tim2 = 0; tim2 < 10000; tim2++)
			{
				asm volatile("nop\n");
			}

		}
	}

	return 0;
}
