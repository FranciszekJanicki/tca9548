#ifndef TCA9548_TCA9548_CONFIG_H
#define TCA9548_TCA9548_CONFIG_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum {
    TCA9548_ERR_OK = 0,
    TCA9548_ERR_FAIL = 1 << 0,
    TCA9548_ERR_NULL = 1 << 1,
} tca9548_err_t;

typedef enum {

    TCA9548_DEV_ADDRESS_A2_H_A1_H_A0_H = 0b1110111,
    TCA9548_DEV_ADDRESS_A2_H_A1_H_A0_L = 0b1110110,
    TCA9548_DEV_ADDRESS_A2_H_A1_L_A0_H = 0b1110101,
    TCA9548_DEV_ADDRESS_A2_L_A1_H_A0_H = 0b1110011,
    TCA9548_DEV_ADDRESS_A2_H_A1_L_A0_L = 0b1110100,
    TCA9548_DEV_ADDRESS_A2_L_A1_H_A0_L = 0b1110010,
    TCA9548_DEV_ADDRESS_A2_L_A1_L_A0_H = 0b1110001,
    TCA9548_DEV_ADDRESS_A2_L_A1_L_A0_L = 0b1110000,
} tca9548_dev_address_t;

typedef enum {
    TCA9548_CHANNEL_0 = 0,
    TCA9548_CHANNEL_1 = 1,
    TCA9548_CHANNEL_2 = 2,
    TCA9548_CHANNEL_3 = 3,
    TCA9548_CHANNEL_4 = 4,
    TCA9548_CHANNEL_5 = 5,
    TCA9548_CHANNEL_6 = 6,
    TCA9548_CHANNEL_7 = 7,
    TCA9548_CHANNEL_NONE,
} tca9548_channel_t;

typedef struct {
    uint32_t reset_pin;
} tca9548_config_t;

typedef struct {
    void* gpio_user;
    tca9548_err_t (*gpio_initialize)(void*);
    tca9548_err_t (*gpio_deinitialize)(void*);
    tca9548_err_t (*gpio_write_pin)(void*, uint32_t, bool);

    void* bus_user;
    tca9548_err_t (*bus_initialize)(void*);
    tca9548_err_t (*bus_deinitialize)(void*);
    tca9548_err_t (*bus_transmit_data)(void*, uint8_t const*, size_t);
    tca9548_err_t (*bus_receive_data)(void*, uint8_t*, size_t);
} tca9548_interface_t;

#endif // TCA9548_TCA9548_CONFIG_H