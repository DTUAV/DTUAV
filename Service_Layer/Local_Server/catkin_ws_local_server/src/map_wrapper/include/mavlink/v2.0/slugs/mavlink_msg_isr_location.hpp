// MESSAGE ISR_LOCATION support class

#pragma once

namespace mavlink {
namespace slugs {
namespace msg {

/**
 * @brief ISR_LOCATION message
 *
 * Transmits the position of watch
 */
struct ISR_LOCATION : mavlink::Message {
    static constexpr msgid_t MSG_ID = 189;
    static constexpr size_t LENGTH = 16;
    static constexpr size_t MIN_LENGTH = 16;
    static constexpr uint8_t CRC_EXTRA = 246;
    static constexpr auto NAME = "ISR_LOCATION";


    uint8_t target; /*<  The system reporting the action */
    float latitude; /*< [deg] ISR Latitude */
    float longitude; /*< [deg] ISR Longitude */
    float height; /*<  ISR Height */
    uint8_t option1; /*<  Option 1 */
    uint8_t option2; /*<  Option 2 */
    uint8_t option3; /*<  Option 3 */


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
        ss << "  height: " << height << std::endl;
        ss << "  option1: " << +option1 << std::endl;
        ss << "  option2: " << +option2 << std::endl;
        ss << "  option3: " << +option3 << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << latitude;                      // offset: 0
        map << longitude;                     // offset: 4
        map << height;                        // offset: 8
        map << target;                        // offset: 12
        map << option1;                       // offset: 13
        map << option2;                       // offset: 14
        map << option3;                       // offset: 15
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> latitude;                      // offset: 0
        map >> longitude;                     // offset: 4
        map >> height;                        // offset: 8
        map >> target;                        // offset: 12
        map >> option1;                       // offset: 13
        map >> option2;                       // offset: 14
        map >> option3;                       // offset: 15
    }
};

} // namespace msg
} // namespace slugs
} // namespace mavlink
