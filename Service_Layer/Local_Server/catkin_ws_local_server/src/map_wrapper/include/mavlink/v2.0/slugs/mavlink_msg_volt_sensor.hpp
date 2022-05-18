// MESSAGE VOLT_SENSOR support class

#pragma once

namespace mavlink {
namespace slugs {
namespace msg {

/**
 * @brief VOLT_SENSOR message
 *
 * Transmits the readings from the voltage and current sensors
 */
struct VOLT_SENSOR : mavlink::Message {
    static constexpr msgid_t MSG_ID = 191;
    static constexpr size_t LENGTH = 5;
    static constexpr size_t MIN_LENGTH = 5;
    static constexpr uint8_t CRC_EXTRA = 17;
    static constexpr auto NAME = "VOLT_SENSOR";


    uint8_t r2Type; /*<  It is the value of reading 2: 0 - Current, 1 - Foreward Sonar, 2 - Back Sonar, 3 - RPM */
    uint16_t voltage; /*<  Voltage in uS of PWM. 0 uS = 0V, 20 uS = 21.5V  */
    uint16_t reading2; /*<  Depends on the value of r2Type (0) Current consumption in uS of PWM, 20 uS = 90Amp (1) Distance in cm (2) Distance in cm (3) Absolute value */


    inline std::string get_name(void) const override
    {
            return NAME;
    }

    inline Info get_message_info(void) const override
    {
            return { MSG_ID, LENGTH, MIN_LENGTH, CRC_EXTRA };
    }

    inline std::string to_yaml(void) const override
    {
        std::stringstream ss;

        ss << NAME << ":" << std::endl;
        ss << "  r2Type: " << +r2Type << std::endl;
        ss << "  voltage: " << voltage << std::endl;
        ss << "  reading2: " << reading2 << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << voltage;                       // offset: 0
        map << reading2;                      // offset: 2
        map << r2Type;                        // offset: 4
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> voltage;                       // offset: 0
        map >> reading2;                      // offset: 2
        map >> r2Type;                        // offset: 4
    }
};

} // namespace msg
} // namespace slugs
} // namespace mavlink
