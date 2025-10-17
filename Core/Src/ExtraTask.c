#include <main.h>
// Lab 1 extra task
uint16_t state_counter[4] = {0,0,0,0};
// [0] - frequencies {0-4}
// [1] - leds {0-2} G,R,B
// [2] - phases {0-2}
uint16_t prev_state_counter[4] = {0,0,0,0};

uint16_t phase [3] = {0,0,0}; // G, R, B

uint16_t FreqCount [3] = {0,0,0}; // G, R, B
uint16_t blinkingFreq [3] = {0,0,0}; // G, R, B
uint16_t prev_blinkingFreq [3] = {0,0,0}; // G, R, B

float freqs [5] = {1, 1.5, 2, 2.5, 3};
uint16_t buttonDelay = 2000;
uint16_t preescaler = 10000;
uint8_t green_on = 0;
uint8_t blue_on = 0;
uint8_t red_on = 0;

uint32_t generalCounter = 0;


void checkForPressedButtonB3(){
    if (((*(uint32_t *)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_3) != 0) && state_counter[0] == prev_state_counter[0])
    {
        state_counter[0]++;
        for (float i = 0; i < buttonDelay; i++)
        {
        }
    }
    if (((*(uint32_t *)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_3) == 0) && state_counter[0] != prev_state_counter[0])
    {
        prev_state_counter[0] = state_counter[0];
        for (float i = 0; i < buttonDelay; i++)
        {
        }
    }
    if (state_counter[0] > 4){
        state_counter[0] = 0;
    }
}

void checkForPressedButtonB5(){
    if (((*(uint32_t *)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_5) != 0) && state_counter[1] == prev_state_counter[1])
    {
        state_counter[1]++;
        for (float i = 0; i < buttonDelay; i++)
        {
        }
    }
    if (((*(uint32_t *)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_5) == 0) && state_counter[1] != prev_state_counter[1])
    {
        prev_state_counter[1] = state_counter[1];
        for (float i = 0; i < buttonDelay; i++)
        {
        }
    }
    if (state_counter[1] > 2)
    {
        state_counter[1] = 0;
    }
}

void checkForPressedButtonB7(){
    if (((*(uint32_t *)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_7) != 0) && state_counter[2] == prev_state_counter[2])
    {
        state_counter[2]++;
        for (float i = 0; i < buttonDelay; i++)
        {
        }
    }
    if (((*(uint32_t *)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_7) == 0) && state_counter[2] != prev_state_counter[2])
    {
        prev_state_counter[2] = state_counter[2];
        for (float i = 0; i < buttonDelay; i++)
        {
        }
        if (state_counter[1] == 0)
        { // G
            phase[0] = phase[0] + 500;
        }
        if (state_counter[1] == 1)
        { // R
            phase[1] = phase[1] + 500;
        }
        if (state_counter[1] == 2)
        { // B
            phase[2] = phase[2] + 500;
        }
    }
}

void checkForPressedButtonB9(){
        if (((*(uint32_t*)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_9) != 0) && state_counter[3] == prev_state_counter[3]){
            state_counter[3]++;
            for (float i = 0; i < buttonDelay; i++){
            }
        }
        if (((*(uint32_t*)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_9) == 0) && state_counter[3] != prev_state_counter[3]){
            prev_state_counter[3] = state_counter[3];
            for (float i = 0; i < buttonDelay; i++){
            }
        }
}

void changeBlinkingFreq(){
    if(state_counter[1] == 0){ // G
        FreqCount[0] = state_counter[0];
        
    }
    if(state_counter[1] == 1){ // R
        FreqCount[1] = state_counter[0];
        
    }
    if(state_counter[1] == 2){ // B
        FreqCount[2] = state_counter[0];
        
    }

    blinkingFreq[0] = (float)(generalCounter + phase[0])*freqs[FreqCount[0]]/preescaler;
    blinkingFreq[1] = (float)(generalCounter + phase[1])*freqs[FreqCount[1]]/preescaler;
    blinkingFreq[2] = (float)(generalCounter + phase[2])*freqs[FreqCount[2]]/preescaler;        
}

void blinkLEDS(){
    // if the time to blink has come
    // green
    if (blinkingFreq[0] != prev_blinkingFreq[0]){
        // if its on
        if (green_on == 1){
            //turn it off
            *(uint32_t*)(GPIO_A + GPIO_x_set_reset_address) |= (0x01UL << 16);
            green_on = 0;
        }else{
            // turn it on
            *(uint32_t*)(GPIO_A + GPIO_x_set_reset_address) |= 0x01UL;
            green_on = 1;
        }
        prev_blinkingFreq[0] = blinkingFreq[0];
    }
    // red
    if (blinkingFreq[1] != prev_blinkingFreq[1]){
        // if its on
        if (red_on == 1){
            //turn it off
            *(uint32_t*)(GPIO_A + GPIO_x_set_reset_address) |= (0x02UL << 16);
            red_on = 0;
        }else{
            // turn it on
            *(uint32_t*)(GPIO_A + GPIO_x_set_reset_address) |= 0x02UL;
            red_on = 1;
        }
        prev_blinkingFreq[1] = blinkingFreq[1];
    }
    // blue
    if (blinkingFreq[2] != prev_blinkingFreq[2]){
        // if its on
        if (blue_on == 1){
            //turn it off
            *(uint32_t*)(GPIO_A + GPIO_x_set_reset_address) |= (0x04UL << 16);
            blue_on = 0;
        }else{
            // turn it on
            *(uint32_t*)(GPIO_A + GPIO_x_set_reset_address) |= 0x04UL;
            blue_on = 1;
        }
        prev_blinkingFreq[2] = blinkingFreq[2];
    }
}

void addPhase(){
    
}

int main(void){
    
    GPIO_init();

    while(1){
        checkForPressedButtonB3();
        checkForPressedButtonB7();
        checkForPressedButtonB5();
        checkForPressedButtonB9();
        generalCounter++;
        changeBlinkingFreq();
        blinkLEDS();



    }
}
