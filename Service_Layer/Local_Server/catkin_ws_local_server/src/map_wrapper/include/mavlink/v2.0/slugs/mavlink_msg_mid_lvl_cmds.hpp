// MESSAGE MID_LVL_CMDS support class

#pragma once

namespace mavlink {
namespace slugs {
namespace msg {

/**
 * @brief MID_LVL_CMDS message
 *
 * Mid Level commands sent from the GS to the autopilot. These are only sent when being operated in mid-level commands mode from the ground.
 */
struct MID_LVL_CMDS : mavlink::Message {
    static constexpr msgid_t MSG_ID = 180;
    static constexpr size_t LENGTH = 13;
    static constexpr size_t MIN_LENGTH = 13;
    static constexpr uint8_t CRC_EXTRA = 146;
    static constexpr auto NAME = "MID_LVL_CMDS";


    uint8_t target; /*<  The system setting the commands */
    float hCommand; /*< [m] Commanded altitude (MSL) */
    float uCommand; /*< [m/s] Commanded Airspeed */
    float rCommand; /*< [rad/s] Commanded Turnrate */


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
        ss << "  hCommand: " << hCommand << std::endl;
        ss << "  uCommand: " << uCommand << std::endl;
        ss << "  rCommand: " << rCommand << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << hCommand;                      // offset: 0
        map << uCommand;                      // offset: 4
        map << rCommand;                      // offset: 8
        map << target;                        // offset: 12
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> hCommand;                      // offset: 0
        map >> uCommand;                      // offset: 4
        map >> rCommand;                      // offset: 8
        map >> target;                        // offset: 12
    }
};

} // namespace msg
} // namespace slugs
} // namespace mavlink
