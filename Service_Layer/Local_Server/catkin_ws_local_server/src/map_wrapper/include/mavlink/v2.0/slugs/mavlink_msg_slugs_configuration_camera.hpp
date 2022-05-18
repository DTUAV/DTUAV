// MESSAGE SLUGS_CONFIGURATION_CAMERA support class

#pragma once

namespace mavlink {
namespace slugs {
namespace msg {

/**
 * @brief SLUGS_CONFIGURATION_CAMERA message
 *
 * Control for camara.
 */
struct SLUGS_CONFIGURATION_CAMERA : mavlink::Message {
    static constexpr msgid_t MSG_ID = 188;
    static constexpr size_t LENGTH = 3;
    static constexpr size_t MIN_LENGTH = 3;
    static constexpr uint8_t CRC_EXTRA = 5;
    static constexpr auto NAME = "SLUGS_CONFIGURATION_CAMERA";


    uint8_t target; /*<  The system setting the commands */
    uint8_t idOrder; /*<  ID 0: brightness 1: aperture 2: iris 3: ICR 4: backlight */
    uint8_t order; /*<   1: up/on 2: down/off 3: auto/reset/no action */


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
        ss << "  idOrder: " << +idOrder << std::endl;
        ss << "  order: " << +order << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << target;                        // offset: 0
        map << idOrder;                       // offset: 1
        map << order;                         // offset: 2
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> target;                        // offset: 0
        map >> idOrder;                       // offset: 1
        map >> order;                         // offset: 2
    }
};

} // namespace msg
} // namespace slugs
} // namespace mavlink
