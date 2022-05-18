// MESSAGE PTZ_STATUS support class

#pragma once

namespace mavlink {
namespace slugs {
namespace msg {

/**
 * @brief PTZ_STATUS message
 *
 * Transmits the actual Pan, Tilt and Zoom values of the camera unit
 */
struct PTZ_STATUS : mavlink::Message {
    static constexpr msgid_t MSG_ID = 192;
    static constexpr size_t LENGTH = 5;
    static constexpr size_t MIN_LENGTH = 5;
    static constexpr uint8_t CRC_EXTRA = 187;
    static constexpr auto NAME = "PTZ_STATUS";


    uint8_t zoom; /*<  The actual Zoom Value */
    int16_t pan; /*<  The Pan value in 10ths of degree */
    int16_t tilt; /*<  The Tilt value in 10ths of degree */


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
        ss << "  zoom: " << +zoom << std::endl;
        ss << "  pan: " << pan << std::endl;
        ss << "  tilt: " << tilt << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << pan;                           // offset: 0
        map << tilt;                          // offset: 2
        map << zoom;                          // offset: 4
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> pan;                           // offset: 0
        map >> tilt;                          // offset: 2
        map >> zoom;                          // offset: 4
    }
};

} // namespace msg
} // namespace slugs
} // namespace mavlink
