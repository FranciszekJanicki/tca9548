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
    TCA9548_SLAVE_ADDRESS_A2H_A1H_A0H = 0b1110111,
    TCA9548_SLAVE_ADDRESS_A2H_A1H_A0L = 0b1110110,
    TCA9548_SLAVE_ADDRESS_A2H_A1L_A0H = 0b1110101,
    TCA9548_SLAVE_ADDRESS_A2L_A1H_A0H = 0b1110011,
    TCA9548_SLAVE_ADDRESS_A2H_A1L_A0L = 0b1110100,
    TCA9548_SLAVE_ADDRESS_A2L_A1H_A0L = 0b1110010,
    TCA9548_SLAVE_ADDRESS_A2L_A1L_A0H = 0b1110001,
    TCA9548_SLAVE_ADDRESS_A2L_A1L_A0L = 0b1110000,
} tca9548_slave_address_t;

typedef enum {
    TCA9548_CHANNEL_0 = 0,
    TCA9548_CHANNEL_1 = 1,
    TCA9548_CHANNEL_2 = 2,
    TCA9548_CHANNEL_3 = 3,
    TCA9548_CHANNEL_4 = 4,
    TCA9548_CHANNEL_5 = 5,
    TCA9548_CHANNEL_6 = 6,
    TCA9548_CHANNEL_7 = 7,
    TCA9548_CHANNEL_NONE = 8,
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

    tca9548_err_t (*bus_slave_transmit_data)(void*, uint16_t, uint8_t const*, size_t);
    tca9548_err_t (*bus_slave_receive_data)(void*, uint16_t, uint8_t*, size_t);
    tca9548_err_t (*bus_slave_write_data)(void*, uint16_t, uint8_t, uint8_t const*, size_t);
    tca9548_err_t (*bus_slave_read_data)(void*, uint16_t, uint8_t, uint8_t*, size_t);
} tca9548_interface_t;

#endif // TCA9548_TCA9548_CONFIG_H
