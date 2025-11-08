#include <main.h>
#include <variables.h>

uint16_t LED1, LED2, LED3, cnt;

void checkButtons(){
    // checking button B3
    if (p_countB3 != countB3){
        if((-TSB3 + millis) >= debounce_thresh){
            counterB3++;
            p_countB3 = countB3;
            if (counterB3 % 2){
                chosenLED++;
                if(chosenLED == 6){
                    chosenLED = 0;
                }
            }
        }
    }

    // checking button B5
    if (p_countB5 != countB5){
        if((-TSB5 + millis) >= debounce_thresh){
            counterB5++;
            p_countB5 = countB5;
            TSB5 = millis;
            if(counterB5 % 2){

            }
        }
    }
    // checking button B7
    if (p_countB7 != countB7){
        if((-TSB7 + millis) >= debounce_thresh){
            counterB7++;
            p_countB7 = countB7;
            TSB7 = millis;
            if (counterB7 % 2){

            }
            
        }
    }
    // checking button B9
    if (p_countB9 != countB9){
        if((-TSB9 + millis) >= debounce_thresh){
            counterB9++;
            p_countB9 = countB9;
            TSB9 = millis;
        }
    }
}

void updateBrightness(){
    cnt = TIM1->CNT;
    if(chosenLED == 0){
        duties[0] = TIM1->CNT;
        TIM2->CCR1 = duties[0];
        LED1 = duties[0];

    }else if (chosenLED == 2){
        duties[1] = TIM1->CNT;
        TIM2->CCR2 = duties[1];
        LED2 = duties[1];

    }else if (chosenLED == 4){
        duties[2] = TIM1->CNT;
        TIM2->CCR4 = duties[2];
        LED3 = duties[2];

    }
}

int main(void){
    GPIO_init();
    RCC_init();
    ITR_init();
    SysTick_init();
    PWM_init();
    Encoder_init();

    while(1){
        checkButtons();
        updateBrightness();
    }
}
