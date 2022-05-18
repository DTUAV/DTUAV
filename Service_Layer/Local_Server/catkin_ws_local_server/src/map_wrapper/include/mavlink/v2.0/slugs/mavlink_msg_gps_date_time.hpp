// MESSAGE GPS_DATE_TIME support class

#pragma once

namespace mavlink {
namespace slugs {
namespace msg {

/**
 * @brief GPS_DATE_TIME message
 *
 * Pilot console PWM messges.
 */
struct GPS_DATE_TIME : mavlink::Message {
    static constexpr msgid_t MSG_ID = 179;
    static constexpr size_t LENGTH = 12;
    static constexpr size_t MIN_LENGTH = 12;
    static constexpr uint8_t CRC_EXTRA = 132;
    static constexpr auto NAME = "GPS_DATE_TIME";


    uint8_t year; /*<  Year reported by Gps  */
    uint8_t month; /*<  Month reported by Gps  */
    uint8_t day; /*<  Day reported by Gps  */
    uint8_t hour; /*<  Hour reported by Gps  */
    uint8_t min; /*<  Min reported by Gps  */
    uint8_t sec; /*<  Sec reported by Gps   */
    uint8_t clockStat; /*<  Clock Status. See table 47 page 211 OEMStar Manual   */
    uint8_t visSat; /*<  Visible satellites reported by Gps   */
    uint8_t useSat; /*<  Used satellites in Solution   */
    uint8_t GppGl; /*<  GPS+GLONASS satellites in Solution   */
    uint8_t sigUsedMask; /*<  GPS and GLONASS usage mask (bit 0 GPS_used? bit_4 GLONASS_used?) */
    uint8_t percentUsed; /*< [%] Percent used GPS */


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
        ss << "  year: " << +year << std::endl;
        ss << "  month: " << +month << std::endl;
        ss << "  day: " << +day << std::endl;
        ss << "  hour: " << +hour << std::endl;
        ss << "  min: " << +min << std::endl;
        ss << "  sec: " << +sec << std::endl;
        ss << "  clockStat: " << +clockStat << std::endl;
        ss << "  visSat: " << +visSat << std::endl;
        ss << "  useSat: " << +useSat << std::endl;
        ss << "  GppGl: " << +GppGl << std::endl;
        ss << "  sigUsedMask: " << +sigUsedMask << std::endl;
        ss << "  percentUsed: " << +percentUsed << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << year;                          // offset: 0
        map << month;                         // offset: 1
        map << day;                           // offset: 2
        map << hour;                          // offset: 3
        map << min;                           // offset: 4
        map << sec;                           // offset: 5
        map << clockStat;                     // offset: 6
        map << visSat;                        // offset: 7
        map << useSat;                        // offset: 8
        map << GppGl;                         // offset: 9
        map << sigUsedMask;                   // offset: 10
        map << percentUsed;                   // offset: 11
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> year;                          // offset: 0
        map >> month;                         // offset: 1
        map >> day;                           // offset: 2
        map >> hour;                          // offset: 3
        map >> min;                           // offset: 4
        map >> sec;                           // offset: 5
        map >> clockStat;                     // offset: 6
        map >> visSat;                        // offset: 7
        map >> useSat;                        // offset: 8
        map >> GppGl;                         // offset: 9
        map >> sigUsedMask;                   // offset: 10
        map >> percentUsed;                   // offset: 11
    }
};

} // namespace msg
} // namespace slugs
} // namespace mavlink
