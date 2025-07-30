#ifndef TCA9548_TCA9548_REGISTERS_H
#define TCA9548_TCA9548_REGISTERS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t channel_7 : 1;
    uint8_t channel_6 : 1;
    uint8_t channel_5 : 1;
    uint8_t channel_4 : 1;
    uint8_t channel_3 : 1;
    uint8_t channel_2 : 1;
    uint8_t channel_1 : 1;
    uint8_t channel_0 : 1;
} tca9548_control_reg_t;

#ifdef __cplusplus
}
#endif

#endif // TCA9548_TCA9548_REGISTERS_H