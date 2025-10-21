#include <main.h>
#include <variables.h>

void checkButtons(){
    // checking button B3
    if (p_countB3 != countB3){
        if((-TSB3 + millis) >= debounce_thresh){
            counterB3++;
            p_countB3 = countB3;
            if (counterB3 % 2){
                mode = !mode;
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
                if (!mode){
                    currentFreqMode1++;
                    if (currentFreqMode1 > 2){
                        currentFreqMode1 = 0;
                    }
                }else if(mode){
                    currentFreqsMode2[selLED]++;
                    if (currentFreqsMode2[selLED] > 2){
                        currentFreqsMode2[selLED] = 0;
                    }
                }
                
                
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
                if (mode){
                    selLED++;
                    if (selLED > 5){selLED = 0;}
                }
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

void updateLEDs(){
    if(G0){
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS0);
    }else if (!G0){
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR0);
    }
    if(R1){
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS1);
    }else if (!R1){
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR1);
    }
    if(B2){
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS2);
    }else if (!B2){
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR2);
    }
    if(B5){
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS5);
    }else if (!B5){
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR5);
    }
    if(R6){
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS6);
    }else if (!R6){
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR6);
    }
    if(G7){
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS7);
    }else if (!G7){
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR7);
    }
}

uint32_t Hz2ms(float hz){
    return (float)(1/hz)*1000;
}

void LEDsOff(){
    B2 = 0;
    B5 = 0;
    G0 = 0;
    R1 = 0;
    R6 = 0;
    G7 = 0;
}

void function1(){
    static uint16_t step = 0; // variable to know the step of the commutation
    static uint16_t t_step = 0; // how long will the commutation last
    static uint32_t t_prev_step = 0; // starting time of current step
    
    // calculate the time to wait next
    t_step = Hz2ms((float)Mode1Freqs[currentFreqMode1]);
    // update the current step based on the time
    if (t_step <= millis - t_prev_step){
        step++;
        t_prev_step = millis;
        if (step > 2){step = 0;}
    }
    // updating LEDs' states
    if(step == 0){
        LEDsOff();
        B2 = 1;
        B5 = 1;
    }else if(step == 1){
        LEDsOff();
        R1 = 1;
        R6 = 1;
    }else if (step == 2){
        LEDsOff();
        G0 = 1;
        G7 = 1;
    }

}

void function2(){
    // last change of state for G0, R1, B2, B5, R6, G7
    static uint32_t t_prev[6] = {0,0,0,0,0,0};
    // current delay each LED has to wait to change states
    static uint16_t t_step[6] = {0,0,0,0,0,0};
    static uint8_t LEDstates[6] = {0,0,0,0,0,0};

    // calculate ALL needed waiting times
    for (uint8_t i = 0; i < 6; i++){
        t_step[i] = Hz2ms((float)Mode2Freqs[currentFreqsMode2[i]]);
    }

    // update states for all LEDs
    for (uint8_t i = 0; i < 6; i++){
        if(t_step[i] <= millis - t_prev[i]){
            //change state
            LEDstates[i] = !LEDstates[i];
            // update time
            t_prev[i] = millis;
        }
    }

    G0 = LEDstates[0];
    R1 = LEDstates[1];
    B2 = LEDstates[2];
    B5 = LEDstates[3];
    R6 = LEDstates[4];
    G7 = LEDstates[5];
}

int main(void){
    GPIO_init();
    RCC_init();
    ITR_init();
    SysTick_init();

    while(1){
        checkButtons();
        updateLEDs();
        if(!mode){
            function1();
        }else if (mode){
            function2();
        }

    }
}
