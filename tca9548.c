#include "tca9548.h"
#include <assert.h>
#include <string.h>

static tca9548_err_t tca9548_gpio_initialize(tca9548_t const* tca9548)
{
    return tca9548->interface.gpio_initialize
               ? tca9548->interface.gpio_initialize(tca9548->interface.gpio_user)
               : TCA9548_ERR_NULL;
}

static tca9548_err_t tca9548_gpio_deinitialize(tca9548_t const* tca9548)
{
    return tca9548->interface.gpio_deinitialize
               ? tca9548->interface.gpio_deinitialize(tca9548->interface.gpio_user)
               : TCA9548_ERR_NULL;
}

static tca9548_err_t tca9548_gpio_write_pin(tca9548_t const* tca9548, uint32_t pin, bool state)
{
    return tca9548->interface.gpio_write_pin
               ? tca9548->interface.gpio_write_pin(tca9548->interface.gpio_user, pin, state)
               : TCA9548_ERR_NULL;
}

static tca9548_err_t tca9548_bus_initialize(tca9548_t const* tca9548)
{
    return tca9548->interface.bus_initialize
               ? tca9548->interface.bus_initialize(tca9548->interface.bus_user)
               : TCA9548_ERR_NULL;
}

static tca9548_err_t tca9548_bus_deinitialize(tca9548_t const* tca9548)
{
    return tca9548->interface.bus_deinitialize
               ? tca9548->interface.bus_deinitialize(tca9548->interface.bus_user)
               : TCA9548_ERR_NULL;
}

static tca9548_err_t tca9548_bus_transmit_data(tca9548_t const* tca9548,
                                               uint8_t const* data,
                                               size_t data_size)
{
    return tca9548->interface.bus_transmit_data
               ? tca9548->interface.bus_transmit_data(tca9548->interface.bus_user, data, data_size)
               : TCA9548_ERR_NULL;
}

static tca9548_err_t tca9548_bus_receive_data(tca9548_t const* tca9548,
                                              uint8_t* data,
                                              size_t data_size)
{
    return tca9548->interface.bus_receive_data
               ? tca9548->interface.bus_receive_data(tca9548->interface.bus_user, data, data_size)
               : TCA9548_ERR_NULL;
}

tca9548_err_t tca9548_initialize(tca9548_t* tca9548,
                                 tca9548_config_t const* config,
                                 tca9548_interface_t const* interface)
{
    assert(tca9548 && config && interface);

    memset(tca9548, 0, sizeof(*tca9548));
    memcpy(&tca9548->config, config, sizeof(*config));
    memcpy(&tca9548->interface, interface, sizeof(*interface));

    tca9548_err_t err = tca9548_gpio_initialize(tca9548);
    err |= tca9548_bus_initialize(tca9548);

    return err;
}

tca9548_err_t tca9548_deinitialize(tca9548_t* tca9548)
{
    assert(tca9548);

    tca9548_err_t err = tca9548_gpio_deinitialize(tca9548);
    err |= tca9548_bus_deinitialize(tca9548);

    memset(tca9548, 0, sizeof(*tca9548));

    return err;
}

tca9548_err_t tca9548_set_reset(tca9548_t const* tca9548, bool reset)
{
    return tca9548_gpio_write_pin(tca9548, tca9548->config.reset_pin, !reset);
}

tca9548_err_t tca9548_set_channel(tca9548_t const* tca9548, tca9548_channel_t channel)
{
    assert(tca9548);

    uint8_t data = {};

    if (channel == TCA9548_CHANNEL_NONE) {
        data = 0U;
    } else {
        data = 1U << (channel & 0xFFU);
    }

    return tca9548_bus_transmit_data(tca9548, &data, sizeof(data));
}

tca9548_err_t tca9548_get_control_reg(tca9548_t const* tca9548, tca9548_control_reg_t* reg)
{
    assert(tca9548 && reg);

    uint8_t data = {};

    tca9548_err_t err = tca9548_bus_receive_data(tca9548, &data, sizeof(data));

    reg->channel_7 = (data >> 7U) & 0x01U;
    reg->channel_6 = (data >> 6U) & 0x01U;
    reg->channel_5 = (data >> 5U) & 0x01U;
    reg->channel_4 = (data >> 4U) & 0x01U;
    reg->channel_3 = (data >> 3U) & 0x01U;
    reg->channel_2 = (data >> 2U) & 0x01U;
    reg->channel_1 = (data >> 1U) & 0x01U;
    reg->channel_0 = data & 0x01U;

    return err;
}

tca9548_err_t tca9548_set_control_reg(tca9548_t const* tca9548, tca9548_control_reg_t const* reg)
{
    assert(tca9548);

    assert(tca9548 && reg);

    uint8_t data = {};

    data |= (reg->channel_7 & 0x01U) << 7U;
    data |= (reg->channel_6 & 0x01U) << 6U;
    data |= (reg->channel_5 & 0x01U) << 5U;
    data |= (reg->channel_4 & 0x01U) << 4U;
    data |= (reg->channel_3 & 0x01U) << 3U;
    data |= (reg->channel_2 & 0x01U) << 2U;
    data |= (reg->channel_1 & 0x01U) << 1U;
    data |= reg->channel_0 & 0x01U;

    return tca9548_bus_transmit_data(tca9548, &data, sizeof(data));
}
