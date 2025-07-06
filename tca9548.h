#ifndef TCA9548_TCA9548_H
#define TCA9548_TCA9548_H

#include "tca9548_config.h"
#include "tca9548_registers.h"

typedef struct {
    tca9548_config_t config;
    tca9548_interface_t interface;
} tca9548_t;

tca9548_err_t tca9548_initialize(tca9548_t* tca9548,
                                 tca9548_config_t const* config,
                                 tca9548_interface_t const* interface);
tca9548_err_t tca9548_deinitialize(tca9548_t* tca9548);

tca9548_err_t tca9548_set_reset(tca9548_t const* tca9548, bool reset);
tca9548_err_t tca9548_set_channel(tca9548_t const* tca9548, tca9548_channel_t channel);

tca9548_err_t tca9548_get_control_reg(tca9548_t const* tca9548, tca9548_control_reg_t* reg);
tca9548_err_t tca9548_set_control_reg(tca9548_t const* tca9548, tca9548_control_reg_t const* reg);

#endif // TCA9548_TCA9548_H