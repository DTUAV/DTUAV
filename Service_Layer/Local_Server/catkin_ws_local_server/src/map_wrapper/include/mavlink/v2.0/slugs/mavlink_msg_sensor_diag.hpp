// MESSAGE SENSOR_DIAG support class

#pragma once

namespace mavlink {
namespace slugs {
namespace msg {

/**
 * @brief SENSOR_DIAG message
 *
 * Diagnostic data Sensor MCU
 */
struct SENSOR_DIAG : mavlink::Message {
    static constexpr msgid_t MSG_ID = 196;
    static constexpr size_t LENGTH = 11;
    static constexpr size_t MIN_LENGTH = 11;
    static constexpr uint8_t CRC_EXTRA = 129;
    static constexpr auto NAME = "SENSOR_DIAG";


    float float1; /*<  Float field 1 */
    float float2; /*<  Float field 2 */
    int16_t int1; /*<  Int 16 field 1 */
    int8_t char1; /*<  Int 8 field 1 */


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
        ss << "  float1: " << float1 << std::endl;
        ss << "  float2: " << float2 << std::endl;
        ss << "  int1: " << int1 << std::endl;
        ss << "  char1: " << +char1 << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << float1;                        // offset: 0
        map << float2;                        // offset: 4
        map << int1;                          // offset: 8
        map << char1;                         // offset: 10
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> float1;                        // offset: 0
        map >> float2;                        // offset: 4
        map >> int1;                          // offset: 8
        map >> char1;                         // offset: 10
    }
};

} // namespace msg
} // namespace slugs
} // namespace mavlink
