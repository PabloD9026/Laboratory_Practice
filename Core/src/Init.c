#include "Init.h"

void Encoder_init(void){
    // Enable clock for TIM 1
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);

    // configure channel 1 and 2 as inputs
    // channel 1
    MODIFY_REG(TIM1->CCMR1, TIM_CCMR1_CC1S, TIM_CCMR1_CC1S_0);
    // channel 2
    MODIFY_REG(TIM1->CCMR1, TIM_CCMR1_CC2S, TIM_CCMR1_CC2S_0);

    // set input polarity to non inverted and rising edge
    CLEAR_BIT(TIM1->CCER, TIM_CCER_CC1P); // channel 1
    CLEAR_BIT(TIM1->CCER, TIM_CCER_CC2P); // channel 2

    // Configure the timer in Encoder Mode 3 (x4 counting)
    // SMS='011': Counts on both edges of TI1 and TI2
    MODIFY_REG(TIM1->SMCR, TIM_SMCR_SMS, (TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1));

    // Set the auto-reload register to 6 ticks per rotation (cause buttons)
    WRITE_REG(TIM1->ARR, 6*4 - 1);

    // For advanced timers (TIM1/TIM8), the Main Output Enable (MOE) bit
    SET_BIT(TIM1->BDTR, TIM_BDTR_MOE);

    // Enable the timer counter
    SET_BIT(TIM1->CR1, TIM_CR1_CEN);
}

void PWM_init(void){
    // Enabling timer 2
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);

    // setting the prescaler to make the hpb1 clock tick at 1mhz
    TIM2->PSC = 48-1;
    // auto reload register = 100 cause timer will be at 10 KHz
    // 1 000 000 Hz / 100 Hz = 10 000 Hz
    TIM2->ARR = 100-1;

    // Configure Channel 1 in PWM mode 1 (OC1M = 110)
    CLEAR_BIT(TIM2->CCMR1, TIM_CCMR1_OC1M_0); // 0
    SET_BIT(TIM2->CCMR1, TIM_CCMR1_OC1M_1); // 1 
    SET_BIT(TIM2->CCMR1, TIM_CCMR1_OC1M_2); // 1

    // Configure Channel 2 in PWM mode 1 (OC1M = 110)
    CLEAR_BIT(TIM2->CCMR1, TIM_CCMR1_OC2M_0); // 0
    SET_BIT(TIM2->CCMR1, TIM_CCMR1_OC2M_1); // 1 
    SET_BIT(TIM2->CCMR1, TIM_CCMR1_OC2M_2); // 1

    // Configure Channel 4 in PWM mode 1 (OC1M = 110)
    CLEAR_BIT(TIM2->CCMR2, TIM_CCMR2_OC4M_0); // 0
    SET_BIT(TIM2->CCMR2, TIM_CCMR2_OC4M_1); // 1 
    SET_BIT(TIM2->CCMR2, TIM_CCMR2_OC4M_2); // 1

    // Enable the output compare 1 preload for CCR1
    SET_BIT(TIM2->CCMR1, TIM_CCMR1_OC1PE);

    // Enable the output compare 1 preload for CCR2
    SET_BIT(TIM2->CCMR1, TIM_CCMR1_OC2PE);

    // Enable the output compare 1 preload for CCR4
    SET_BIT(TIM2->CCMR2, TIM_CCMR2_OC4PE);

    // set it at 50% (testing)
    TIM2->CCR1 = 50;
    TIM2->CCR2 = 30;
    TIM2->CCR4 = 50;

    // Enable the output for channel 1
    SET_BIT(TIM2->CCER, TIM_CCER_CC1E);
    // Enable the output for channel 2
    SET_BIT(TIM2->CCER, TIM_CCER_CC2E);
    // Enable the output for channel 4
    SET_BIT(TIM2->CCER, TIM_CCER_CC4E);

    // Enable the auto-reload preload
    SET_BIT(TIM2->CR1, TIM_CR1_ARPE);

    // Enable the main timer counter to start PWM generation
    SET_BIT(TIM2->CR1, TIM_CR1_CEN);

}

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
    // MODIFY_REG(RCC->CFGR, RCC_CFGR_MCO, RCC_CFGR_MCO_PLLCLK_DIV2); 
    
    // adding a wait state to read from memory
    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_2);
}   

void GPIO_init(void){
    // setting the RCC ticks for the A group
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN); 

    // configurating the pins A0, A1, and A2 to output alternate function 50 MHz

    // A0
    // clearing the bits for the MODE register and seeting output 50mhz
    MODIFY_REG(GPIOA->CRL, GPIO_CRL_MODE0, GPIO_CRL_MODE0);
    // alternate function (in this case, will be PWM output)
    MODIFY_REG(GPIOA->CRL, GPIO_CRL_CNF0, GPIO_CRL_CNF0_1);

    // A1
    // clearing the bits for the MODE register and seeting output 50mhz
    MODIFY_REG(GPIOA->CRL, GPIO_CRL_MODE1, GPIO_CRL_MODE1);
    // alternate function (in this case, will be PWM output)
    MODIFY_REG(GPIOA->CRL, GPIO_CRL_CNF1, GPIO_CRL_CNF1_1);

    // A2
    // clearing the bits for the MODE register and seeting output 50mhz
    MODIFY_REG(GPIOA->CRL, GPIO_CRL_MODE3, GPIO_CRL_MODE3);
    // alternate function (in this case, will be PWM output)
    MODIFY_REG(GPIOA->CRL, GPIO_CRL_CNF3, GPIO_CRL_CNF3_1);

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

    // setting up A8 and A9 to be inputs for encoder mode
    // making A8 an input pull down
    // clearing the bits
    CLEAR_BIT(GPIOA->CRH, GPIO_CRH_CNF8); // cnf bit
    CLEAR_BIT(GPIOA->CRH, GPIO_CRH_MODE8); // mode bit
    // making the button an input pullup/pulldown
    SET_BIT(GPIOA->CRH, GPIO_CRH_CNF8_1);
    // making B3 an input pull down
    // clearing the bits
    CLEAR_BIT(GPIOA->CRH, GPIO_CRH_CNF9); // cnf bit
    CLEAR_BIT(GPIOA->CRH, GPIO_CRH_MODE9); // mode bit
    // making the button an input pullup/pulldown
    SET_BIT(GPIOA->CRH, GPIO_CRH_CNF9_1);

}
