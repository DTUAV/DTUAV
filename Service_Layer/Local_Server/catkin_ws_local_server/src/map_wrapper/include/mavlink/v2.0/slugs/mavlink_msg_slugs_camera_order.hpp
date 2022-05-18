// MESSAGE SLUGS_CAMERA_ORDER support class

#pragma once

namespace mavlink {
namespace slugs {
namespace msg {

/**
 * @brief SLUGS_CAMERA_ORDER message
 *
 * Orders generated to the SLUGS camera mount. 
 */
struct SLUGS_CAMERA_ORDER : mavlink::Message {
    static constexpr msgid_t MSG_ID = 184;
    static constexpr size_t LENGTH = 5;
    static constexpr size_t MIN_LENGTH = 5;
    static constexpr uint8_t CRC_EXTRA = 45;
    static constexpr auto NAME = "SLUGS_CAMERA_ORDER";


    uint8_t target; /*<  The system reporting the action */
    int8_t pan; /*<  Order the mount to pan: -1 left, 0 No pan motion, +1 right */
    int8_t tilt; /*<  Order the mount to tilt: -1 down, 0 No tilt motion, +1 up */
    int8_t zoom; /*<  Order the zoom values 0 to 10 */
    int8_t moveHome; /*<  Orders the camera mount to move home. The other fields are ignored when this field is set. 1: move home, 0 ignored */


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
        ss << "  pan: " << +pan << std::endl;
        ss << "  tilt: " << +tilt << std::endl;
        ss << "  zoom: " << +zoom << std::endl;
        ss << "  moveHome: " << +moveHome << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << target;                        // offset: 0
        map << pan;                           // offset: 1
        map << tilt;                          // offset: 2
        map << zoom;                          // offset: 3
        map << moveHome;                      // offset: 4
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> target;                        // offset: 0
        map >> pan;                           // offset: 1
        map >> tilt;                          // offset: 2
        map >> zoom;                          // offset: 3
        map >> moveHome;                      // offset: 4
    }
};

} // namespace msg
} // namespace slugs
} // namespace mavlink
