// MESSAGE SLUGS_MOBILE_LOCATION support class

#pragma once

namespace mavlink {
namespace slugs {
namespace msg {

/**
 * @brief SLUGS_MOBILE_LOCATION message
 *
 * Transmits the last known position of the mobile GS to the UAV. Very relevant when Track Mobile is enabled
 */
struct SLUGS_MOBILE_LOCATION : mavlink::Message {
    static constexpr msgid_t MSG_ID = 186;
    static constexpr size_t LENGTH = 9;
    static constexpr size_t MIN_LENGTH = 9;
    static constexpr uint8_t CRC_EXTRA = 101;
    static constexpr auto NAME = "SLUGS_MOBILE_LOCATION";


    uint8_t target; /*<  The system reporting the action */
    float latitude; /*< [deg] Mobile Latitude */
    float longitude; /*< [deg] Mobile Longitude */


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
        ss << "  target: " << +target << std::endl;
        ss << "  latitude: " << latitude << std::endl;
        ss << "  longitude: " << longitude << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << latitude;                      // offset: 0
        map << longitude;                     // offset: 4
        map << target;                        // offset: 8
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> latitude;                      // offset: 0
        map >> longitude;                     // offset: 4
        map >> target;                        // offset: 8
    }
};

} // namespace msg
} // namespace slugs
} // namespace mavlink
