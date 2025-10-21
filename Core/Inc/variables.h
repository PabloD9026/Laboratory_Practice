#include <stdint.h>

extern volatile uint32_t millis;

// button debounde threshold
extern volatile uint16_t debounce_thresh;
// raw button counters
extern volatile uint16_t countB9, countB7, countB5, countB3;
// previous values of raw button counters
extern volatile uint16_t p_countB9, p_countB7, p_countB5, p_countB3;
// button counters
extern volatile uint16_t counterB9, counterB7, counterB5, counterB3;
// button pressing time stamps
extern volatile uint16_t TSB9, TSB7, TSB5, TSB3;

// LED status: 1 - on; 2 - off. Named after: ColorPin 
extern volatile uint8_t G0, R1, B2, B5, R6, G7;


// Working mode
// 0 - LEDs turn on in pairs
// 1 - LEDs turn on in singles
extern volatile uint8_t mode;

// 1st mode frequencies
extern volatile float Mode1Freqs[3];
// 1st mode current freq
extern volatile uint8_t currentFreqMode1;

// 2nd mode frequencies
extern volatile float Mode2Freqs[3];
// 2nd mode current frequencies for G0, R1, B2, B5, R6, G7
extern volatile uint8_t currentFreqsMode2[6];
// 2nd mode selected LED
extern volatile uint8_t selLED;