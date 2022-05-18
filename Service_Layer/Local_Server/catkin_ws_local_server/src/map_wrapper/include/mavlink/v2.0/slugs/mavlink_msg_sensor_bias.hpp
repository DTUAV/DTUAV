// MESSAGE SENSOR_BIAS support class

#pragma once

namespace mavlink {
namespace slugs {
namespace msg {

/**
 * @brief SENSOR_BIAS message
 *
 * Accelerometer and gyro biases.
 */
struct SENSOR_BIAS : mavlink::Message {
    static constexpr msgid_t MSG_ID = 172;
    static constexpr size_t LENGTH = 24;
    static constexpr size_t MIN_LENGTH = 24;
    static constexpr uint8_t CRC_EXTRA = 168;
    static constexpr auto NAME = "SENSOR_BIAS";


    float axBias; /*< [m/s] Accelerometer X bias */
    float ayBias; /*< [m/s] Accelerometer Y bias */
    float azBias; /*< [m/s] Accelerometer Z bias */
    float gxBias; /*< [rad/s] Gyro X bias */
    float gyBias; /*< [rad/s] Gyro Y bias */
    float gzBias; /*< [rad/s] Gyro Z bias */


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
        ss << "  axBias: " << axBias << std::endl;
        ss << "  ayBias: " << ayBias << std::endl;
        ss << "  azBias: " << azBias << std::endl;
        ss << "  gxBias: " << gxBias << std::endl;
        ss << "  gyBias: " << gyBias << std::endl;
        ss << "  gzBias: " << gzBias << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << axBias;                        // offset: 0
        map << ayBias;                        // offset: 4
        map << azBias;                        // offset: 8
        map << gxBias;                        // offset: 12
        map << gyBias;                        // offset: 16
        map << gzBias;                        // offset: 20
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> axBias;                        // offset: 0
        map >> ayBias;                        // offset: 4
        map >> azBias;                        // offset: 8
        map >> gxBias;                        // offset: 12
        map >> gyBias;                        // offset: 16
        map >> gzBias;                        // offset: 20
    }
};

} // namespace msg
} // namespace slugs
} // namespace mavlink
