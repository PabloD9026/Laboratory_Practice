#include <stdint.h>
#define APB2ENR (0x18UL)
#define RCC (0x40021000UL)
#define GPIO_A (0x40010800UL)
#define GPIO_B (0x40010C00UL)
#define GPIO_x_config_address (0x00UL)
#define GPIO_x_config_address_2 (0x04UL)
#define GPIO_x_set_reset_address (0x10UL)
#define ODR_bit_address (0x0CUL)
#define IN_DATA_REG (0x08UL)
#define IN_DATA_REG_3 (0x08UL)
#define IN_DATA_REG_5 (0x20UL)
#define IN_DATA_REG_7 (0x80UL)
#define IN_DATA_REG_9 (0x200UL)

void GPIO_init(void);