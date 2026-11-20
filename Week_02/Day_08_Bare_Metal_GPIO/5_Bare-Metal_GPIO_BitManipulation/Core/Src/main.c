#include <stdint.h>


//Base address of the clock control block(RCC)
#define RCC_BASE 0x40023800U

//Hardware Turnning Register
#define RCC_AHB1ENR (*(volatile uint32_t*)(RCC_BASE + 0x30U))   //First take a Address and DeRefference

//Base address for GPIO ports
#define GPIOA_BASE 0x40020000
#define GPIOB_BASE 0x40020400
#define GPIOC_BASE 0x40020800
//GPIOA Registers
#define GPIOA_MODER (*(volatile uint32_t*)(GPIOA_BASE +  0x00U)  )
#define GPIOA_BSRR (*(volatile uint32_t*)(GPIOA_BASE  + 0x18U )  )

//GPIOB Registers
#define GPIOB_MODER (*(volatile uint32_t*)(GPIOB_BASE +  0x00U ) )
#define GPIOB_BSRR (*(volatile uint32_t*)(GPIOB_BASE  + 0x18U  ) )

//GPIOC Registers
#define GPIOC_MODER (*(volatile uint32_t*)(GPIOC_BASE +  0x00U ) )
#define GPIOC_BSRR (*(volatile uint32_t*)(GPIOC_BASE  + 0x18U  ) )

int main(void){

	//Turn on the clock for GPIOs
	RCC_AHB1ENR |= 0b111 ;

	//First clear Mode settings
	GPIOA_MODER &= 0x3C000000U;  // keep bits 31:26 (PA13–PA15), clear everything else ;

	//Set those pins to "output mode"
	GPIOA_MODER |=  0x41555555U;

	//Do the same to GPIOB
	GPIOB_MODER &=  0xFC000000U;
	GPIOB_MODER |=  0x55555555U;

	//Do the same to GPIOC
	GPIOC_MODER &=  0xFC000000U;
	GPIOC_MODER |=  0x51555555U;

	//Set GPIO pins high (turn them ON)
	GPIOA_BSRR |= 0x00009FFF;
	GPIOB_BSRR |= 0x0000FFFF;
	GPIOC_BSRR |= 0x0000FFFF;



}
