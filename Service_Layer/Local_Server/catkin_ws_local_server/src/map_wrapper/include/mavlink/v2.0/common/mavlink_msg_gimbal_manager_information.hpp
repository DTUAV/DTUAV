// MESSAGE GIMBAL_MANAGER_INFORMATION support class

#pragma once

namespace mavlink {
namespace common {
namespace msg {

/**
 * @brief GIMBAL_MANAGER_INFORMATION message
 *
 * Information about a high level gimbal manager. This message should be requested by a ground station using MAV_CMD_REQUEST_MESSAGE.
 */
struct GIMBAL_MANAGER_INFORMATION : mavlink::Message {
    static constexpr msgid_t MSG_ID = 280;
    static constexpr size_t LENGTH = 33;
    static constexpr size_t MIN_LENGTH = 33;
    static constexpr uint8_t CRC_EXTRA = 166;
    static constexpr auto NAME = "GIMBAL_MANAGER_INFORMATION";


    uint32_t time_boot_ms; /*< [ms] Timestamp (time since system boot). */
    uint32_t cap_flags; /*<  Bitmap of gimbal capability flags. */
    uint8_t gimbal_device_id; /*<  Gimbal device ID that this gimbal manager is responsible for. */
    float tilt_max; /*< [rad] Maximum tilt/pitch angle (positive: up, negative: down) */
    float tilt_min; /*< [rad] Minimum tilt/pitch angle (positive: up, negative: down) */
    float tilt_rate_max; /*< [rad/s] Maximum tilt/pitch angular rate (positive: up, negative: down) */
    float pan_max; /*< [rad] Maximum pan/yaw angle (positive: to the right, negative: to the left) */
    float pan_min; /*< [rad] Minimum pan/yaw angle (positive: to the right, negative: to the left) */
    float pan_rate_max; /*< [rad/s] Minimum pan/yaw angular rate (positive: to the right, negative: to the left) */


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
        ss << "  time_boot_ms: " << time_boot_ms << std::endl;
        ss << "  cap_flags: " << cap_flags << std::endl;
        ss << "  gimbal_device_id: " << +gimbal_device_id << std::endl;
        ss << "  tilt_max: " << tilt_max << std::endl;
        ss << "  tilt_min: " << tilt_min << std::endl;
        ss << "  tilt_rate_max: " << tilt_rate_max << std::endl;
        ss << "  pan_max: " << pan_max << std::endl;
        ss << "  pan_min: " << pan_min << std::endl;
        ss << "  pan_rate_max: " << pan_rate_max << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << time_boot_ms;                  // offset: 0
        map << cap_flags;                     // offset: 4
        map << tilt_max;                      // offset: 8
        map << tilt_min;                      // offset: 12
        map << tilt_rate_max;                 // offset: 16
        map << pan_max;                       // offset: 20
        map << pan_min;                       // offset: 24
        map << pan_rate_max;                  // offset: 28
        map << gimbal_device_id;              // offset: 32
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> time_boot_ms;                  // offset: 0
        map >> cap_flags;                     // offset: 4
        map >> tilt_max;                      // offset: 8
        map >> tilt_min;                      // offset: 12
        map >> tilt_rate_max;                 // offset: 16
        map >> pan_max;                       // offset: 20
        map >> pan_min;                       // offset: 24
        map >> pan_rate_max;                  // offset: 28
        map >> gimbal_device_id;              // offset: 32
    }
};

} // namespace msg
} // namespace common
} // namespace mavlink
