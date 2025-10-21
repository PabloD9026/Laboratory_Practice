#include "Init.h"

void SysTick_init(void){
    // Stopping the timer to configure it in case it was on
    CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);

    // enabling interrupts
    SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);

    // make the clock source AHB (48MHz)
    // bit 1 - AHB
    // bit 0 - AHB/8
    SET_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk);

    // setting the max value for the counter
    // since the source clock ticks at 48 MHz, and we want a ms counter
    // then the counter should count till 48 000 - 1 = 47 999
    MODIFY_REG(SysTick->LOAD, SysTick_LOAD_RELOAD_Msk, 47999 << SysTick_CTRL_ENABLE_Pos);

    // setting the counter to 0
    MODIFY_REG(SysTick->LOAD, SysTick_VAL_CURRENT_Msk, 47999 << SysTick_CTRL_ENABLE_Pos);

    // Starting the counter
    SET_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);

}

void ITR_init(void){
    // enabling clock for GPIOB peropherals
    // SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPBEN); // This is done in the GPIO init already
    // setting the button b9 to be an input pull down is also done in GPIO init

    // enabling the clock for alternative functions IO
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);

    // Making an interropt on B9
    // Clear the bits that select the port for EXTI line 9
    CLEAR_BIT(AFIO->EXTICR[2], AFIO_EXTICR3_EXTI9);
    // Set the bits to select Port B as the source for EXTI line 9
    SET_BIT(AFIO->EXTICR[2], AFIO_EXTICR3_EXTI9_PB);

    SET_BIT(EXTI->IMR, EXTI_IMR_MR9); // Interrupt in line 9
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR9); // riing edge trigger
    SET_BIT(EXTI->FTSR, EXTI_FTSR_TR9); // falling edge trigger

    // Making an interrupt a B7
    // Clear the bits that select the port for EXTI line 7
    CLEAR_BIT(AFIO->EXTICR[1], AFIO_EXTICR2_EXTI7);
    // Set the bits to select Port B as the source for EXTI line 7
    SET_BIT(AFIO->EXTICR[1], AFIO_EXTICR2_EXTI7_PB);

    SET_BIT(EXTI->IMR, EXTI_IMR_MR7); // Interrupt in line 7
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR7); // riing edge trigger
    SET_BIT(EXTI->FTSR, EXTI_FTSR_TR7); // falling edge trigger

    // Making an interrupt a B5
    // Clear the bits that select the port for EXTI line 5
    CLEAR_BIT(AFIO->EXTICR[1], AFIO_EXTICR2_EXTI5);
    // Set the bits to select Port B as the source for EXTI line 5
    SET_BIT(AFIO->EXTICR[1], AFIO_EXTICR2_EXTI5_PB);

    SET_BIT(EXTI->IMR, EXTI_IMR_MR5); // Interrupt in line 5
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR5); // riing edge trigger
    SET_BIT(EXTI->FTSR, EXTI_FTSR_TR5); // falling edge trigger

    // setting the priority level.
    // arg 1: This function reads the current system-wide split configuration. 
    // It returns a value that tells NVIC_EncodePriority how the bits are currently divided.
    // arg 2: It determines if an interrupt can interrupt another, already running interrupt.
    // arg 3:  if two interrupts with the same preemption priority occur at the exact same time.
    // The one with the higher subpriority (lower number) will be handled first. 
    NVIC_SetPriority(EXTI9_5_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));

    //enabling the interrupts
    NVIC_EnableIRQ(EXTI9_5_IRQn);

    // Making an interrupt a B3
    // Clear the bits that select the port for EXTI line 3
    CLEAR_BIT(AFIO->EXTICR[0], AFIO_EXTICR1_EXTI3);
    // Set the bits to select Port B as the source for EXTI line 3
    SET_BIT(AFIO->EXTICR[0], AFIO_EXTICR1_EXTI3_PB);

    SET_BIT(EXTI->IMR, EXTI_IMR_MR3); // Interrupt in line 3
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR3); // riing edge trigger
    SET_BIT(EXTI->FTSR, EXTI_FTSR_TR3); // falling edge trigger

    // setting the priority level.
    NVIC_SetPriority(EXTI3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));

    //enabling the interrupts
    NVIC_EnableIRQ(EXTI3_IRQn);

}

void RCC_init(void){
    MODIFY_REG(RCC->CR, RCC_CR_HSITRIM, 0x80U);
    CLEAR_REG(RCC->CFGR);
    while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RESET);
    CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
    while(READ_BIT(RCC->CR, RCC_CR_PLLRDY) != RESET);
    CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_CSSON);
    while(READ_BIT(RCC->CR, RCC_CR_HSERDY) != RESET);
    CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);

    // turning on the HSE resonator and checking that it works
    SET_BIT(RCC->CR, RCC_CR_HSEON);
    while(READ_BIT(RCC->CR, RCC_CR_HSERDY) == RESET);
    CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);
    SET_BIT(RCC->CR, RCC_CR_CSSON);

    // tuning the PLL values to get 48 MHz on SYSCLK
    SET_BIT(RCC->CFGR, RCC_CFGR_PLLSRC); // using the HSE crystal
    SET_BIT(RCC->CFGR, RCC_CFGR_PLLXTPRE_HSE_DIV2); // divide it by 2
    // multiplying the HSE frequency. 4x12 = 48MHz
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PLLMULL, RCC_CFGR_PLLMULL12); 

    SET_BIT(RCC->CR, RCC_CR_PLLON); // turn on the PLL
    while(READ_BIT(RCC->CR, RCC_CR_PLLRDY) == RESET); // check if PLL is working   


    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL); // making SYSCLK feed from PLL
    while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

    MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_CFGR_HPRE_DIV1); // AHB prescaler = 1
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, RCC_CFGR_PPRE1_DIV2); // APB1 prescaler = 2
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, RCC_CFGR_PPRE2_DIV1); // APB2 prescaler = 1
    MODIFY_REG(RCC->CFGR, RCC_CFGR_ADCPRE, RCC_CFGR_ADCPRE_DIV4); // ADC prescaler = 4
    // make an output pin to see the clock. Source PLL/2
    MODIFY_REG(RCC->CFGR, RCC_CFGR_MCO, RCC_CFGR_MCO_PLLCLK_DIV2); 
    
    // adding a wait state to read from memory
    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_1);

    // NVIC_EnableIRQ();
    // NVIC_SetPriority();
}   

void GPIO_init(void){
    // setting the RCC ticks for the A group
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN); // cmsis way

    // setting the pin A8 at max speed push pull open drain
    CLEAR_BIT(GPIOA->CRH, GPIO_CRH_CNF8 | GPIO_CRH_MODE8);
    SET_BIT(GPIOA->CRH, GPIO_CRH_MODE8 | GPIO_CRH_CNF8_1);

    // configurating the pins A0, A1, and A2 to output pp 10 mhz

    // A0
    // clearing the bits for the MODE register and seeting output 10mhz
    MODIFY_REG(GPIOA->CRL, GPIO_CRL_MODE0, GPIO_CRL_MODE0_0);
    // general purpose output push pull is the reset state
    CLEAR_BIT(GPIOA->CRL, GPIO_CRL_CNF0);

    // A1
    // clearing the bits for the MODE register and seeting output 10mhz
    MODIFY_REG(GPIOA->CRL, GPIO_CRL_MODE1, GPIO_CRL_MODE1_0);
    // general purpose output push pull is the reset state
    CLEAR_BIT(GPIOA->CRL, GPIO_CRL_CNF1);
    
    // A2
    // clearing the bits for the MODE register and seeting output 10mhz
    MODIFY_REG(GPIOA->CRL, GPIO_CRL_MODE2, GPIO_CRL_MODE2_0);
    // general purpose output push pull is the reset state
    CLEAR_BIT(GPIOA->CRL, GPIO_CRL_CNF2);

    // A5
    // clearing the bits for the MODE register and seeting output 10mhz
    MODIFY_REG(GPIOA->CRL, GPIO_CRL_MODE5, GPIO_CRL_MODE5_0);
    // general purpose output push pull is the reset state
    CLEAR_BIT(GPIOA->CRL, GPIO_CRL_CNF5);

    // A6
    // clearing the bits for the MODE register and seeting output 10mhz
    MODIFY_REG(GPIOA->CRL, GPIO_CRL_MODE6, GPIO_CRL_MODE6_0);
    // general purpose output push pull is the reset state
    CLEAR_BIT(GPIOA->CRL, GPIO_CRL_CNF6);
    
    // A7
    // clearing the bits for the MODE register and seeting output 10mhz
    MODIFY_REG(GPIOA->CRL, GPIO_CRL_MODE7, GPIO_CRL_MODE7_0);
    // general purpose output push pull is the reset state
    CLEAR_BIT(GPIOA->CRL, GPIO_CRL_CNF7);

    // configuring Inputs

    // setting the RCC ticks for the B group
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPBEN); // cmsis way

    // making B3 an input pull down
    // clearing the bits
    CLEAR_BIT(GPIOB->CRL, GPIO_CRL_CNF3); // cnf bit
    CLEAR_BIT(GPIOB->CRL, GPIO_CRL_MODE3); // mode bit
    // making the button an input pullup/pulldown
    SET_BIT(GPIOB->CRL, GPIO_CRL_CNF3_1);
    // selecting pull down
    CLEAR_BIT(GPIOB->ODR, GPIO_ODR_ODR3);

    // making B5 an input pull down
    // clearing the bits
    CLEAR_BIT(GPIOB->CRL, GPIO_CRL_CNF5); // cnf bit
    CLEAR_BIT(GPIOB->CRL, GPIO_CRL_MODE5); // mode bit
    // making the button an input pullup/pulldown
    SET_BIT(GPIOB->CRL, GPIO_CRL_CNF5_1);
    // selecting pull down
    CLEAR_BIT(GPIOB->ODR, GPIO_ODR_ODR5);

    // making B7 an input pull down
    // clearing the bits
    CLEAR_BIT(GPIOB->CRL, GPIO_CRL_CNF7); // cnf bit
    CLEAR_BIT(GPIOB->CRL, GPIO_CRL_MODE7); // mode bit
    // making the button an input pullup/pulldown
    SET_BIT(GPIOB->CRL, GPIO_CRL_CNF7_1);
    // selecting pull down
    CLEAR_BIT(GPIOB->ODR, GPIO_ODR_ODR7);

    // making B9 an input pull down
    // clearing the bits
    CLEAR_BIT(GPIOB->CRH, GPIO_CRH_CNF9); // cnf bit
    CLEAR_BIT(GPIOB->CRH, GPIO_CRH_MODE9); // mode bit
    // making the button an input pullup/pulldown
    SET_BIT(GPIOB->CRH, GPIO_CRH_CNF9_1);
    // selecting pull down
    CLEAR_BIT(GPIOB->ODR, GPIO_ODR_ODR9);
}
