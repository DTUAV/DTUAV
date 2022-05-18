// MESSAGE STATUS_GPS support class

#pragma once

namespace mavlink {
namespace slugs {
namespace msg {

/**
 * @brief STATUS_GPS message
 *
 * This contains the status of the GPS readings
 */
struct STATUS_GPS : mavlink::Message {
    static constexpr msgid_t MSG_ID = 194;
    static constexpr size_t LENGTH = 11;
    static constexpr size_t MIN_LENGTH = 11;
    static constexpr uint8_t CRC_EXTRA = 51;
    static constexpr auto NAME = "STATUS_GPS";


    uint16_t csFails; /*<  Number of times checksum has failed */
    uint8_t gpsQuality; /*<  The quality indicator, 0=fix not available or invalid, 1=GPS fix, 2=C/A differential GPS, 6=Dead reckoning mode, 7=Manual input mode (fixed position), 8=Simulator mode, 9= WAAS a */
    uint8_t msgsType; /*<   Indicates if GN, GL or GP messages are being received */
    uint8_t posStatus; /*<   A = data valid, V = data invalid */
    float magVar; /*< [deg] Magnetic variation */
    int8_t magDir; /*<   Magnetic variation direction E/W. Easterly variation (E) subtracts from True course and Westerly variation (W) adds to True course */
    uint8_t modeInd; /*<   Positioning system mode indicator. A - Autonomous;D-Differential; E-Estimated (dead reckoning) mode;M-Manual input; N-Data not valid */


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
        ss << "  csFails: " << csFails << std::endl;
        ss << "  gpsQuality: " << +gpsQuality << std::endl;
        ss << "  msgsType: " << +msgsType << std::endl;
        ss << "  posStatus: " << +posStatus << std::endl;
        ss << "  magVar: " << magVar << std::endl;
        ss << "  magDir: " << +magDir << std::endl;
        ss << "  modeInd: " << +modeInd << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << magVar;                        // offset: 0
        map << csFails;                       // offset: 4
        map << gpsQuality;                    // offset: 6
        map << msgsType;                      // offset: 7
        map << posStatus;                     // offset: 8
        map << magDir;                        // offset: 9
        map << modeInd;                       // offset: 10
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> magVar;                        // offset: 0
        map >> csFails;                       // offset: 4
        map >> gpsQuality;                    // offset: 6
        map >> msgsType;                      // offset: 7
        map >> posStatus;                     // offset: 8
        map >> magDir;                        // offset: 9
        map >> modeInd;                       // offset: 10
    }
};

} // namespace msg
} // namespace slugs
} // namespace mavlink
