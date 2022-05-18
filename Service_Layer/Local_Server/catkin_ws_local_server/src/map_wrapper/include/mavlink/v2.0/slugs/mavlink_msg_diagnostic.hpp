// MESSAGE DIAGNOSTIC support class

#pragma once

namespace mavlink {
namespace slugs {
namespace msg {

/**
 * @brief DIAGNOSTIC message
 *
 * Configurable diagnostic messages.
 */
struct DIAGNOSTIC : mavlink::Message {
    static constexpr msgid_t MSG_ID = 173;
    static constexpr size_t LENGTH = 18;
    static constexpr size_t MIN_LENGTH = 18;
    static constexpr uint8_t CRC_EXTRA = 2;
    static constexpr auto NAME = "DIAGNOSTIC";


    float diagFl1; /*<  Diagnostic float 1 */
    float diagFl2; /*<  Diagnostic float 2 */
    float diagFl3; /*<  Diagnostic float 3 */
    int16_t diagSh1; /*<  Diagnostic short 1 */
    int16_t diagSh2; /*<  Diagnostic short 2 */
    int16_t diagSh3; /*<  Diagnostic short 3 */


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
        ss << "  diagFl1: " << diagFl1 << std::endl;
        ss << "  diagFl2: " << diagFl2 << std::endl;
        ss << "  diagFl3: " << diagFl3 << std::endl;
        ss << "  diagSh1: " << diagSh1 << std::endl;
        ss << "  diagSh2: " << diagSh2 << std::endl;
        ss << "  diagSh3: " << diagSh3 << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << diagFl1;                       // offset: 0
        map << diagFl2;                       // offset: 4
        map << diagFl3;                       // offset: 8
        map << diagSh1;                       // offset: 12
        map << diagSh2;                       // offset: 14
        map << diagSh3;                       // offset: 16
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> diagFl1;                       // offset: 0
        map >> diagFl2;                       // offset: 4
        map >> diagFl3;                       // offset: 8
        map >> diagSh1;                       // offset: 12
        map >> diagSh2;                       // offset: 14
        map >> diagSh3;                       // offset: 16
    }
};

} // namespace msg
} // namespace slugs
} // namespace mavlink
