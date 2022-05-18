// MESSAGE NOVATEL_DIAG support class

#pragma once

namespace mavlink {
namespace slugs {
namespace msg {

/**
 * @brief NOVATEL_DIAG message
 *
 * Transmits the diagnostics data from the Novatel OEMStar GPS
 */
struct NOVATEL_DIAG : mavlink::Message {
    static constexpr msgid_t MSG_ID = 195;
    static constexpr size_t LENGTH = 14;
    static constexpr size_t MIN_LENGTH = 14;
    static constexpr uint8_t CRC_EXTRA = 59;
    static constexpr auto NAME = "NOVATEL_DIAG";


    uint8_t timeStatus; /*<  The Time Status. See Table 8 page 27 Novatel OEMStar Manual */
    uint32_t receiverStatus; /*<  Status Bitfield. See table 69 page 350 Novatel OEMstar Manual */
    uint8_t solStatus; /*<  solution Status. See table 44 page 197 */
    uint8_t posType; /*<  position type. See table 43 page 196 */
    uint8_t velType; /*<  velocity type. See table 43 page 196 */
    float posSolAge; /*< [s] Age of the position solution */
    uint16_t csFails; /*<  Times the CRC has failed since boot */


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
        ss << "  timeStatus: " << +timeStatus << std::endl;
        ss << "  receiverStatus: " << receiverStatus << std::endl;
        ss << "  solStatus: " << +solStatus << std::endl;
        ss << "  posType: " << +posType << std::endl;
        ss << "  velType: " << +velType << std::endl;
        ss << "  posSolAge: " << posSolAge << std::endl;
        ss << "  csFails: " << csFails << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << receiverStatus;                // offset: 0
        map << posSolAge;                     // offset: 4
        map << csFails;                       // offset: 8
        map << timeStatus;                    // offset: 10
        map << solStatus;                     // offset: 11
        map << posType;                       // offset: 12
        map << velType;                       // offset: 13
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> receiverStatus;                // offset: 0
        map >> posSolAge;                     // offset: 4
        map >> csFails;                       // offset: 8
        map >> timeStatus;                    // offset: 10
        map >> solStatus;                     // offset: 11
        map >> posType;                       // offset: 12
        map >> velType;                       // offset: 13
    }
};

} // namespace msg
} // namespace slugs
} // namespace mavlink
