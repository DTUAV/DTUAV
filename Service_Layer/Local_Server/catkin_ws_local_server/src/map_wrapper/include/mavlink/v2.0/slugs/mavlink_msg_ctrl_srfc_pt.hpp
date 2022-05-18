// MESSAGE CTRL_SRFC_PT support class

#pragma once

namespace mavlink {
namespace slugs {
namespace msg {

/**
 * @brief CTRL_SRFC_PT message
 *
 * This message sets the control surfaces for selective passthrough mode.
 */
struct CTRL_SRFC_PT : mavlink::Message {
    static constexpr msgid_t MSG_ID = 181;
    static constexpr size_t LENGTH = 3;
    static constexpr size_t MIN_LENGTH = 3;
    static constexpr uint8_t CRC_EXTRA = 104;
    static constexpr auto NAME = "CTRL_SRFC_PT";


    uint8_t target; /*<  The system setting the commands */
    uint16_t bitfieldPt; /*<  Bitfield containing the passthrough configuration, see CONTROL_SURFACE_FLAG ENUM. */


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
        ss << "  bitfieldPt: " << bitfieldPt << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << bitfieldPt;                    // offset: 0
        map << target;                        // offset: 2
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> bitfieldPt;                    // offset: 0
        map >> target;                        // offset: 2
    }
};

} // namespace msg
} // namespace slugs
} // namespace mavlink
