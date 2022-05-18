// MESSAGE UAV_STATUS support class

#pragma once

namespace mavlink {
namespace slugs {
namespace msg {

/**
 * @brief UAV_STATUS message
 *
 * Transmits the actual status values UAV in flight
 */
struct UAV_STATUS : mavlink::Message {
    static constexpr msgid_t MSG_ID = 193;
    static constexpr size_t LENGTH = 21;
    static constexpr size_t MIN_LENGTH = 21;
    static constexpr uint8_t CRC_EXTRA = 160;
    static constexpr auto NAME = "UAV_STATUS";


    uint8_t target; /*<  The ID system reporting the action */
    float latitude; /*< [deg] Latitude UAV */
    float longitude; /*< [deg] Longitude UAV */
    float altitude; /*< [m] Altitude UAV */
    float speed; /*< [m/s] Speed UAV */
    float course; /*<  Course UAV */


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
        ss << "  altitude: " << altitude << std::endl;
        ss << "  speed: " << speed << std::endl;
        ss << "  course: " << course << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << latitude;                      // offset: 0
        map << longitude;                     // offset: 4
        map << altitude;                      // offset: 8
        map << speed;                         // offset: 12
        map << course;                        // offset: 16
        map << target;                        // offset: 20
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> latitude;                      // offset: 0
        map >> longitude;                     // offset: 4
        map >> altitude;                      // offset: 8
        map >> speed;                         // offset: 12
        map >> course;                        // offset: 16
        map >> target;                        // offset: 20
    }
};

} // namespace msg
} // namespace slugs
} // namespace mavlink
