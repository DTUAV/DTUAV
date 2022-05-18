// MESSAGE CPU_LOAD support class

#pragma once

namespace mavlink {
namespace slugs {
namespace msg {

/**
 * @brief CPU_LOAD message
 *
 * Sensor and DSC control loads.
 */
struct CPU_LOAD : mavlink::Message {
    static constexpr msgid_t MSG_ID = 170;
    static constexpr size_t LENGTH = 4;
    static constexpr size_t MIN_LENGTH = 4;
    static constexpr uint8_t CRC_EXTRA = 75;
    static constexpr auto NAME = "CPU_LOAD";


    uint8_t sensLoad; /*<  Sensor DSC Load */
    uint8_t ctrlLoad; /*<  Control DSC Load */
    uint16_t batVolt; /*< [mV] Battery Voltage */


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
        ss << "  sensLoad: " << +sensLoad << std::endl;
        ss << "  ctrlLoad: " << +ctrlLoad << std::endl;
        ss << "  batVolt: " << batVolt << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << batVolt;                       // offset: 0
        map << sensLoad;                      // offset: 2
        map << ctrlLoad;                      // offset: 3
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> batVolt;                       // offset: 0
        map >> sensLoad;                      // offset: 2
        map >> ctrlLoad;                      // offset: 3
    }
};

} // namespace msg
} // namespace slugs
} // namespace mavlink
