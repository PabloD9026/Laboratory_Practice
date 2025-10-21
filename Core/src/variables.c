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

// LED status: 1 - on; 2 - off. Named after: ColorPin 
volatile uint8_t G0, R1, B2, B5, R6, G7;

// Working mode
// 0 - LEDs turn on in pairs
// 1 - LEDs turn on in singles
volatile uint8_t mode = 0;

// 1st mode frequencies
volatile float Mode1Freqs[3] = {0.5, 1.7, 2.2};
// 1st mode current freq
volatile uint8_t currentFreqMode1 = 0;

// 2nd mode frequencies
volatile float Mode2Freqs[3] = {0.3, 0.8, 1.4};
// 2nd mode current frequencies for G0, R1, B2, B5, R6, G7
volatile uint8_t currentFreqsMode2[6] = {0,0,0,0,0,0};
// 2nd mode selected LED
volatile uint8_t selLED = 0;
