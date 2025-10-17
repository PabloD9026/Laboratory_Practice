#include "Init.h"

void GPIO_init(void){
    // setting the RCC ticks for the A group
    *(uint32_t*)(RCC + APB2ENR) |= 0x04UL;
    // configurating the pins A0, A1, and A2 to output pp 10 mhz
    // clearing the bits for the A0 pin
    *(uint32_t*)(GPIO_A + GPIO_x_config_address) &= ~(0xFUL);
    // setting the A0 to general purpose output pp at 10 mhz
    *(uint32_t*)(GPIO_A + GPIO_x_config_address) |= 0x01UL;
    // clearing the bits for the A1 pin
    *(uint32_t*)(GPIO_A + GPIO_x_config_address) &= ~(0xFUL << 4);
    // setting the A1 to general purpose output pp at 10 mhz
    *(uint32_t*)(GPIO_A + GPIO_x_config_address) |= 0x01UL << 4;
    // clearing the bits for the A2 pin
    *(uint32_t*)(GPIO_A + GPIO_x_config_address) &= ~(0xFUL << 8);
    // setting the A2 to general purpose output pp at 10 mhz
    *(uint32_t*)(GPIO_A + GPIO_x_config_address) |= 0x01UL << 8;

    // configuring Input
    // setting the RCC ticks for the B group
    *(uint32_t*)(RCC + APB2ENR) |= 0x08UL;
    // Clearing the bits for B3
    *(uint32_t*)(GPIO_B + GPIO_x_config_address) &= ~(0xFUL << 12);
    // setting the pin B3 to be an input 
    *(uint32_t*)(GPIO_B + GPIO_x_config_address) |= (0x08UL << 12);
    // Clearing the bits for B5
    *(uint32_t*)(GPIO_B + GPIO_x_config_address) &= ~(0xFUL << 20);
    // setting the pin B3 to be an input 
    *(uint32_t*)(GPIO_B + GPIO_x_config_address) |= (0x08UL << 20);
    // Clearing the bits for B7
    *(uint32_t*)(GPIO_B + GPIO_x_config_address) &= ~(0xFUL << 28);
    // setting the pin B3 to be an input 
    *(uint32_t*)(GPIO_B + GPIO_x_config_address) |= (0x08UL << 28);
    // Clearing the bits for B9
    *(uint32_t*)(GPIO_B + GPIO_x_config_address_2) &= ~(0xFUL << 4);
    // setting the pin B3 to be an input 
    *(uint32_t*)(GPIO_B + GPIO_x_config_address_2) |= (0x08UL << 4);

    // Setting the input to be pull up
    // *(uint32_t*)(GPIO_B + ODR_bit_address) |= 0x08UL; // comment this line to make pull down

}