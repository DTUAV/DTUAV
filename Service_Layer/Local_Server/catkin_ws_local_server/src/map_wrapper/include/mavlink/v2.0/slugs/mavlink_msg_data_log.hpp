// MESSAGE DATA_LOG support class

#pragma once

namespace mavlink {
namespace slugs {
namespace msg {

/**
 * @brief DATA_LOG message
 *
 * Configurable data log probes to be used inside Simulink
 */
struct DATA_LOG : mavlink::Message {
    static constexpr msgid_t MSG_ID = 177;
    static constexpr size_t LENGTH = 24;
    static constexpr size_t MIN_LENGTH = 24;
    static constexpr uint8_t CRC_EXTRA = 167;
    static constexpr auto NAME = "DATA_LOG";


    float fl_1; /*<  Log value 1  */
    float fl_2; /*<  Log value 2  */
    float fl_3; /*<  Log value 3  */
    float fl_4; /*<  Log value 4  */
    float fl_5; /*<  Log value 5  */
    float fl_6; /*<  Log value 6  */


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
        ss << "  fl_1: " << fl_1 << std::endl;
        ss << "  fl_2: " << fl_2 << std::endl;
        ss << "  fl_3: " << fl_3 << std::endl;
        ss << "  fl_4: " << fl_4 << std::endl;
        ss << "  fl_5: " << fl_5 << std::endl;
        ss << "  fl_6: " << fl_6 << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << fl_1;                          // offset: 0
        map << fl_2;                          // offset: 4
        map << fl_3;                          // offset: 8
        map << fl_4;                          // offset: 12
        map << fl_5;                          // offset: 16
        map << fl_6;                          // offset: 20
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> fl_1;                          // offset: 0
        map >> fl_2;                          // offset: 4
        map >> fl_3;                          // offset: 8
        map >> fl_4;                          // offset: 12
        map >> fl_5;                          // offset: 16
        map >> fl_6;                          // offset: 20
    }
};

} // namespace msg
} // namespace slugs
} // namespace mavlink
