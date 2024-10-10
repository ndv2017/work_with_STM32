#include "stm32f10x.h"
#include <stdio.h>
#include <stdint.h>



#define RCC_ADD			0x40021000

#define PORTA_ADD		0x40010800
#define PORTC_ADD		0x40011000



struct my_RCC_t
{
	uint32_t my_RC;
	uint32_t my_CFGR;
	uint32_t my_CIR;
	uint32_t my_APB2RSTR;
	uint32_t my_APB1RSTR;
	uint32_t my_AHBENR;
	uint32_t my_APB2ENR;
	uint32_t my_APB1ENR;
	uint32_t my_BDCR;
	uint32_t my_CSR;
};

typedef struct
{
	uint32_t my_CRL;
	uint32_t my_CRH;
	uint32_t my_IDR;
	uint32_t my_ODR;
	uint32_t my_BSRR;
	uint32_t my_BRR;
	uint32_t my_LCKR;
}my_GPIO_t;



/* Declare variables */
struct my_RCC_t *my_RCC = (struct my_RCC_t *)RCC_ADD;

my_GPIO_t *PORTC = (my_GPIO_t *)PORTC_ADD;



void my_Delay_ms(uint16_t time)
{
	uint32_t time_n = time*12000;
	while(time_n)
		time_n--;
}

void my_GPIO_Config(void)
{
	/* or 0b10000, to enable clock for PORTC */
	my_RCC->my_APB2ENR |= 0x10;
	/* Reset pin 13 */
	PORTC->my_CRH &= ~(0xF << 20);
	/* 11: Output mode, max speed 50 MHz */
	PORTC->my_CRH |=  (0x3 << 20);
}



int main(void)
{
	my_GPIO_Config();
  while (1)
  {
		PORTC->my_ODR |= 0x2000;
		my_Delay_ms(50);

		PORTC->my_ODR &= ~0x2000;
		my_Delay_ms(50);
  }
}