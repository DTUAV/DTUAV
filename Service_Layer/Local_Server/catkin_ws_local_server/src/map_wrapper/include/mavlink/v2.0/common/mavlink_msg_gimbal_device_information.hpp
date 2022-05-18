// MESSAGE GIMBAL_DEVICE_INFORMATION support class

#pragma once

namespace mavlink {
namespace common {
namespace msg {

/**
 * @brief GIMBAL_DEVICE_INFORMATION message
 *
 * Information about a low level gimbal. This message should be requested by the gimbal manager or a ground station using MAV_CMD_REQUEST_MESSAGE.
 */
struct GIMBAL_DEVICE_INFORMATION : mavlink::Message {
    static constexpr msgid_t MSG_ID = 283;
    static constexpr size_t LENGTH = 98;
    static constexpr size_t MIN_LENGTH = 98;
    static constexpr uint8_t CRC_EXTRA = 247;
    static constexpr auto NAME = "GIMBAL_DEVICE_INFORMATION";


    uint32_t time_boot_ms; /*< [ms] Timestamp (time since system boot). */
    std::array<uint8_t, 32> vendor_name; /*<  Name of the gimbal vendor */
    std::array<uint8_t, 32> model_name; /*<  Name of the gimbal model */
    uint32_t firmware_version; /*<  Version of the gimbal firmware, encoded as: (Dev & 0xff) << 24 | (Patch & 0xff) << 16 | (Minor & 0xff) << 8 | (Major & 0xff) */
    uint16_t cap_flags; /*<  Bitmap of gimbal capability flags. */
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
        ss << "  vendor_name: [" << to_string(vendor_name) << "]" << std::endl;
        ss << "  model_name: [" << to_string(model_name) << "]" << std::endl;
        ss << "  firmware_version: " << firmware_version << std::endl;
        ss << "  cap_flags: " << cap_flags << std::endl;
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
        map << firmware_version;              // offset: 4
        map << tilt_max;                      // offset: 8
        map << tilt_min;                      // offset: 12
        map << tilt_rate_max;                 // offset: 16
        map << pan_max;                       // offset: 20
        map << pan_min;                       // offset: 24
        map << pan_rate_max;                  // offset: 28
        map << cap_flags;                     // offset: 32
        map << vendor_name;                   // offset: 34
        map << model_name;                    // offset: 66
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> time_boot_ms;                  // offset: 0
        map >> firmware_version;              // offset: 4
        map >> tilt_max;                      // offset: 8
        map >> tilt_min;                      // offset: 12
        map >> tilt_rate_max;                 // offset: 16
        map >> pan_max;                       // offset: 20
        map >> pan_min;                       // offset: 24
        map >> pan_rate_max;                  // offset: 28
        map >> cap_flags;                     // offset: 32
        map >> vendor_name;                   // offset: 34
        map >> model_name;                    // offset: 66
    }
};

} // namespace msg
} // namespace common
} // namespace mavlink
