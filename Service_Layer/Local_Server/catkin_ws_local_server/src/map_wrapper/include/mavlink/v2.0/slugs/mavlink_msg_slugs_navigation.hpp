// MESSAGE SLUGS_NAVIGATION support class

#pragma once

namespace mavlink {
namespace slugs {
namespace msg {

/**
 * @brief SLUGS_NAVIGATION message
 *
 * Data used in the navigation algorithm.
 */
struct SLUGS_NAVIGATION : mavlink::Message {
    static constexpr msgid_t MSG_ID = 176;
    static constexpr size_t LENGTH = 32;
    static constexpr size_t MIN_LENGTH = 32;
    static constexpr uint8_t CRC_EXTRA = 228;
    static constexpr auto NAME = "SLUGS_NAVIGATION";


    float u_m; /*< [m/s] Measured Airspeed prior to the nav filter */
    float phi_c; /*<  Commanded Roll */
    float theta_c; /*<  Commanded Pitch */
    float psiDot_c; /*<  Commanded Turn rate */
    float ay_body; /*<  Y component of the body acceleration */
    float totalDist; /*<  Total Distance to Run on this leg of Navigation */
    float dist2Go; /*<  Remaining distance to Run on this leg of Navigation */
    uint8_t fromWP; /*<  Origin WP */
    uint8_t toWP; /*<  Destination WP */
    uint16_t h_c; /*< [dm] Commanded altitude (MSL) */


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
        ss << "  u_m: " << u_m << std::endl;
        ss << "  phi_c: " << phi_c << std::endl;
        ss << "  theta_c: " << theta_c << std::endl;
        ss << "  psiDot_c: " << psiDot_c << std::endl;
        ss << "  ay_body: " << ay_body << std::endl;
        ss << "  totalDist: " << totalDist << std::endl;
        ss << "  dist2Go: " << dist2Go << std::endl;
        ss << "  fromWP: " << +fromWP << std::endl;
        ss << "  toWP: " << +toWP << std::endl;
        ss << "  h_c: " << h_c << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << u_m;                           // offset: 0
        map << phi_c;                         // offset: 4
        map << theta_c;                       // offset: 8
        map << psiDot_c;                      // offset: 12
        map << ay_body;                       // offset: 16
        map << totalDist;                     // offset: 20
        map << dist2Go;                       // offset: 24
        map << h_c;                           // offset: 28
        map << fromWP;                        // offset: 30
        map << toWP;                          // offset: 31
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> u_m;                           // offset: 0
        map >> phi_c;                         // offset: 4
        map >> theta_c;                       // offset: 8
        map >> psiDot_c;                      // offset: 12
        map >> ay_body;                       // offset: 16
        map >> totalDist;                     // offset: 20
        map >> dist2Go;                       // offset: 24
        map >> h_c;                           // offset: 28
        map >> fromWP;                        // offset: 30
        map >> toWP;                          // offset: 31
    }
};

} // namespace msg
} // namespace slugs
} // namespace mavlink
