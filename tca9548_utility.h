#ifndef TCA9548_TCA9548_UTILITY_H
#define TCA9548_TCA9548_UTILITY_H

#ifdef __cplusplus
extern "C" {
#endif

#define TCA9548_MIN_PULLUP_VOLTAGE (1.65F)
#define TCA9548_MAX_PULLUP_VOLTAGE (5.5F)
#define TCA9548_RISE_TIME_NS (300.0F)
#define TCA9548_BUS_CAPACITANCE (400.0F)

inline float tca9548_get_min_pullup_resistance(float pullup_voltage,
                                               float max_logic0_voltage,
                                               float logic0_current)
{
    if (pullup_voltage > TCA9548_MAX_PULLUP_VOLTAGE) {
        pullup_voltage = TCA9548_MAX_PULLUP_VOLTAGE;
    } else if (pullup_voltage < TCA9548_MIN_PULLUP_VOLTAGE) {
        pullup_voltage = TCA9548_MIN_PULLUP_VOLTAGE;
    }

    return (pullup_voltage - max_logic0_voltage) / logic0_current;
}

inline float tca9548_get_max_pullup_resistance(float pullup_voltage,
                                               float max_logic0_voltage,
                                               float logic0_current)
{
    return TCA9548_RISE_TIME_NS / (0.8473F * TCA9548_BUS_CAPACITANCE);
}

#ifdef __cplusplus
}
#endif

#endif // TCA9548_TCA9548_UTILITY_H