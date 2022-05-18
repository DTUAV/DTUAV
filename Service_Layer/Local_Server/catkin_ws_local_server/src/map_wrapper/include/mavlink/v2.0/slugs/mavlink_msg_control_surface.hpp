// MESSAGE CONTROL_SURFACE support class

#pragma once

namespace mavlink {
namespace slugs {
namespace msg {

/**
 * @brief CONTROL_SURFACE message
 *
 * Control for surface; pending and order to origin.
 */
struct CONTROL_SURFACE : mavlink::Message {
    static constexpr msgid_t MSG_ID = 185;
    static constexpr size_t LENGTH = 10;
    static constexpr size_t MIN_LENGTH = 10;
    static constexpr uint8_t CRC_EXTRA = 113;
    static constexpr auto NAME = "CONTROL_SURFACE";


    uint8_t target; /*<  The system setting the commands */
    uint8_t idSurface; /*<  ID control surface send 0: throttle 1: aileron 2: elevator 3: rudder */
    float mControl; /*<  Pending */
    float bControl; /*<  Order to origin */


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
        ss << "  idSurface: " << +idSurface << std::endl;
        ss << "  mControl: " << mControl << std::endl;
        ss << "  bControl: " << bControl << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << mControl;                      // offset: 0
        map << bControl;                      // offset: 4
        map << target;                        // offset: 8
        map << idSurface;                     // offset: 9
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> mControl;                      // offset: 0
        map >> bControl;                      // offset: 4
        map >> target;                        // offset: 8
        map >> idSurface;                     // offset: 9
    }
};

} // namespace msg
} // namespace slugs
} // namespace mavlink
