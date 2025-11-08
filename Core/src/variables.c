#include <variables.h>

volatile uint32_t millis = 0;

// button debounde threshold
volatile uint16_t debounce_thresh = 80;
// raw button counters
volatile uint16_t countB9, countB7, countB5, countB3;
// previous values of raw button counters
volatile uint16_t p_countB9, p_countB7, p_countB5, p_countB3;
// button counters
volatile uint16_t counterB9, counterB7, counterB5, counterB3;
// button pressing time stamps
volatile uint16_t TSB9, TSB7, TSB5, TSB3;

// LEDs' duties G,R,B
volatile uint16_t duties[3] = {0, 0, 0};

// encoder raw counter
volatile uint16_t encoder_counter = 0;

// 0 - green; 1 - red; 2 - blue
volatile uint8_t chosenLED = 0;

