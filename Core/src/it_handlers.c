#include <it_handlers.h>
#include <variables.h>

void SysTick_Handler(void){
    millis++;
}
void EXTI9_5_IRQHandler(void){
    // Chek which one of the buttons was
    // B9 button
    if(READ_BIT(EXTI->PR, EXTI_PR_PR9)){
        countB9++;
        TSB9 = millis;
        // interrupt handled (basically finished)
        SET_BIT(EXTI->PR, EXTI_PR_PR9);
    }
    // B7 button
    if(READ_BIT(EXTI->PR, EXTI_PR_PR7)){
        countB7++;
        TSB7 = millis;
        // interrupt handled (basically finished)
        SET_BIT(EXTI->PR, EXTI_PR_PR7);
    }
    // B5 button
    if(READ_BIT(EXTI->PR, EXTI_PR_PR5)){
        countB5++;
        TSB5 = millis;
        // interrupt handled (basically finished)
        SET_BIT(EXTI->PR, EXTI_PR_PR5);
    }

}
void EXTI3_IRQHandler(void){
        // B3 button
    if(READ_BIT(EXTI->PR, EXTI_PR_PR3)){
        countB3++;
        TSB3 = millis;
        // interrupt handled (basically finished)
        SET_BIT(EXTI->PR, EXTI_PR_PR3);
    }
}