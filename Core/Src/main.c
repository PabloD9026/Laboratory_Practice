#include <main.h>
// Lab 1 main task
uint16_t state_counter = 0;
uint16_t prev_state_counter = 0;
uint8_t green_on = 0;
uint8_t blue_on = 0;
uint8_t red_on = 0;

void firstCaseControl(){
    // B5 turns blue (A2)
            if ((*(uint32_t*)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_5) != 0){
                // setting the pin A2 high
                *(uint32_t*)(GPIO_A + GPIO_x_set_reset_address) |= 0x04UL;
                blue_on = 1;

            }else if ((*(uint32_t*)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_5) == 0)
            {
                // resetting the pin A2 
                *(uint32_t*)(GPIO_A + GPIO_x_set_reset_address) |= (0x04UL << 16);
                blue_on = 0;
            }

            // B7 turns red (A1)
            if ((*(uint32_t*)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_7) != 0){
                // setting the pin A1 high
                *(uint32_t*)(GPIO_A + GPIO_x_set_reset_address) |= 0x02UL;
                red_on = 1;
                
            }else if ((*(uint32_t*)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_7) == 0)
            {
                // resetting the pin A1
                *(uint32_t*)(GPIO_A + GPIO_x_set_reset_address) |= (0x02UL << 16);
                red_on = 0;
            }
            
            // B7 turns green (A0)
            if ((*(uint32_t*)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_9) != 0){
                // setting the pin A0 high
                *(uint32_t*)(GPIO_A + GPIO_x_set_reset_address) |= 0x01UL;
                green_on = 1;
                
            }else if ((*(uint32_t*)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_9) == 0)
            {
                // resetting the pin A0
                *(uint32_t*)(GPIO_A + GPIO_x_set_reset_address) |= (0x01UL << 16);
                green_on = 0;
            }
}

void secondCaseControl(){
    // B5 turns red (A1)
    if ((*(uint32_t *)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_5) != 0)
    {
        // setting the pin A1 high
        *(uint32_t *)(GPIO_A + GPIO_x_set_reset_address) |= 0x02UL;
        red_on = 1;
    }
    else if ((*(uint32_t *)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_5) == 0)
    {
        // resetting the pin A2
        *(uint32_t *)(GPIO_A + GPIO_x_set_reset_address) |= (0x02UL << 16);
        red_on = 0;
    }

    // B7 turns green (A0)
    if ((*(uint32_t *)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_7) != 0)
    {
        // setting the pin A0 high
        *(uint32_t *)(GPIO_A + GPIO_x_set_reset_address) |= 0x01UL;
        green_on = 1;
    }
    else if ((*(uint32_t *)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_7) == 0)
    {
        // resetting the pin A0
        *(uint32_t *)(GPIO_A + GPIO_x_set_reset_address) |= (0x01UL << 16);
        green_on = 0;
    }

    // B7 turns blue (A2)
    if ((*(uint32_t *)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_9) != 0)
    {
        // setting the pin A2 high
        *(uint32_t *)(GPIO_A + GPIO_x_set_reset_address) |= 0x04UL;
        blue_on = 1;
    }
    else if ((*(uint32_t *)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_9) == 0)
    {
        // resetting the pin A2
        *(uint32_t *)(GPIO_A + GPIO_x_set_reset_address) |= (0x04UL << 16);
        blue_on = 0;
    }
}

void thirdCaseControl(){
    // B5 turns green (A0)
    if ((*(uint32_t *)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_5) != 0)
    {
        // setting the pin A0 high
        *(uint32_t *)(GPIO_A + GPIO_x_set_reset_address) |= 0x01UL;
        green_on = 1;
    }
    else if ((*(uint32_t *)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_5) == 0)
    {
        // resetting the pin A0
        *(uint32_t *)(GPIO_A + GPIO_x_set_reset_address) |= (0x01UL << 16);
        green_on = 0;
    }

    // B7 turns blue (A2)
    if ((*(uint32_t *)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_7) != 0)
    {
        // setting the pin A2 high
        *(uint32_t *)(GPIO_A + GPIO_x_set_reset_address) |= 0x04UL;
        blue_on = 1;
    }
    else if ((*(uint32_t *)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_7) == 0)
    {
        // resetting the pin A2
        *(uint32_t *)(GPIO_A + GPIO_x_set_reset_address) |= (0x04UL << 16);
        blue_on = 0;
    }

    // B7 turns red (A1)
    if ((*(uint32_t *)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_9) != 0)
    {
        // setting the pin A0 high
        *(uint32_t *)(GPIO_A + GPIO_x_set_reset_address) |= 0x02UL;
        red_on = 1;
    }
    else if ((*(uint32_t *)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_9) == 0)
    {
        // resetting the pin A0
        *(uint32_t *)(GPIO_A + GPIO_x_set_reset_address) |= (0x02UL << 16);
        red_on = 0;
    }
}

void mainButtonControl(){
    if (((*(uint32_t *)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_3) != 0) && state_counter == prev_state_counter)
    {
        state_counter++;
        for (float i = 0; i < 7000; i++)
        {
        }
    }
    if (((*(uint32_t *)(GPIO_B + IN_DATA_REG) & IN_DATA_REG_3) == 0) && state_counter != prev_state_counter)
    {
        prev_state_counter = state_counter;
        for (float i = 0; i < 7000; i++)
        {
        }
    }
    if (state_counter >= 3)
    {
        state_counter = 0;
    }
}

int main(void){
    
    GPIO_init();

    while(1){
        mainButtonControl();

        if (state_counter == 0){
            firstCaseControl();
        }

        else if (state_counter == 1){
            secondCaseControl();
        }

        else if (state_counter == 2){
            thirdCaseControl();
        }

    }
}
