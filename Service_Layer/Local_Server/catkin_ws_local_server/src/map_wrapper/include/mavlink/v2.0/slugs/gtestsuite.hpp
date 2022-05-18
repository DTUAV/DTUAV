/** @file
 *	@brief MAVLink comm testsuite protocol generated from slugs.xml
 *	@see http://mavlink.org
 */

#pragma once

#include <gtest/gtest.h>
#include "slugs.hpp"

#ifdef TEST_INTEROP
using namespace mavlink;
#undef MAVLINK_HELPER
#include "mavlink.h"
#endif


TEST(slugs, CPU_LOAD)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::slugs::msg::CPU_LOAD packet_in{};
    packet_in.sensLoad = 139;
    packet_in.ctrlLoad = 206;
    packet_in.batVolt = 17235;

    mavlink::slugs::msg::CPU_LOAD packet1{};
    mavlink::slugs::msg::CPU_LOAD packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.sensLoad, packet2.sensLoad);
    EXPECT_EQ(packet1.ctrlLoad, packet2.ctrlLoad);
    EXPECT_EQ(packet1.batVolt, packet2.batVolt);
}

#ifdef TEST_INTEROP
TEST(slugs_interop, CPU_LOAD)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_cpu_load_t packet_c {
         17235, 139, 206
    };

    mavlink::slugs::msg::CPU_LOAD packet_in{};
    packet_in.sensLoad = 139;
    packet_in.ctrlLoad = 206;
    packet_in.batVolt = 17235;

    mavlink::slugs::msg::CPU_LOAD packet2{};

    mavlink_msg_cpu_load_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.sensLoad, packet2.sensLoad);
    EXPECT_EQ(packet_in.ctrlLoad, packet2.ctrlLoad);
    EXPECT_EQ(packet_in.batVolt, packet2.batVolt);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(slugs, SENSOR_BIAS)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::slugs::msg::SENSOR_BIAS packet_in{};
    packet_in.axBias = 17.0;
    packet_in.ayBias = 45.0;
    packet_in.azBias = 73.0;
    packet_in.gxBias = 101.0;
    packet_in.gyBias = 129.0;
    packet_in.gzBias = 157.0;

    mavlink::slugs::msg::SENSOR_BIAS packet1{};
    mavlink::slugs::msg::SENSOR_BIAS packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.axBias, packet2.axBias);
    EXPECT_EQ(packet1.ayBias, packet2.ayBias);
    EXPECT_EQ(packet1.azBias, packet2.azBias);
    EXPECT_EQ(packet1.gxBias, packet2.gxBias);
    EXPECT_EQ(packet1.gyBias, packet2.gyBias);
    EXPECT_EQ(packet1.gzBias, packet2.gzBias);
}

#ifdef TEST_INTEROP
TEST(slugs_interop, SENSOR_BIAS)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_sensor_bias_t packet_c {
         17.0, 45.0, 73.0, 101.0, 129.0, 157.0
    };

    mavlink::slugs::msg::SENSOR_BIAS packet_in{};
    packet_in.axBias = 17.0;
    packet_in.ayBias = 45.0;
    packet_in.azBias = 73.0;
    packet_in.gxBias = 101.0;
    packet_in.gyBias = 129.0;
    packet_in.gzBias = 157.0;

    mavlink::slugs::msg::SENSOR_BIAS packet2{};

    mavlink_msg_sensor_bias_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.axBias, packet2.axBias);
    EXPECT_EQ(packet_in.ayBias, packet2.ayBias);
    EXPECT_EQ(packet_in.azBias, packet2.azBias);
    EXPECT_EQ(packet_in.gxBias, packet2.gxBias);
    EXPECT_EQ(packet_in.gyBias, packet2.gyBias);
    EXPECT_EQ(packet_in.gzBias, packet2.gzBias);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(slugs, DIAGNOSTIC)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::slugs::msg::DIAGNOSTIC packet_in{};
    packet_in.diagFl1 = 17.0;
    packet_in.diagFl2 = 45.0;
    packet_in.diagFl3 = 73.0;
    packet_in.diagSh1 = 17859;
    packet_in.diagSh2 = 17963;
    packet_in.diagSh3 = 18067;

    mavlink::slugs::msg::DIAGNOSTIC packet1{};
    mavlink::slugs::msg::DIAGNOSTIC packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.diagFl1, packet2.diagFl1);
    EXPECT_EQ(packet1.diagFl2, packet2.diagFl2);
    EXPECT_EQ(packet1.diagFl3, packet2.diagFl3);
    EXPECT_EQ(packet1.diagSh1, packet2.diagSh1);
    EXPECT_EQ(packet1.diagSh2, packet2.diagSh2);
    EXPECT_EQ(packet1.diagSh3, packet2.diagSh3);
}

#ifdef TEST_INTEROP
TEST(slugs_interop, DIAGNOSTIC)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_diagnostic_t packet_c {
         17.0, 45.0, 73.0, 17859, 17963, 18067
    };

    mavlink::slugs::msg::DIAGNOSTIC packet_in{};
    packet_in.diagFl1 = 17.0;
    packet_in.diagFl2 = 45.0;
    packet_in.diagFl3 = 73.0;
    packet_in.diagSh1 = 17859;
    packet_in.diagSh2 = 17963;
    packet_in.diagSh3 = 18067;

    mavlink::slugs::msg::DIAGNOSTIC packet2{};

    mavlink_msg_diagnostic_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.diagFl1, packet2.diagFl1);
    EXPECT_EQ(packet_in.diagFl2, packet2.diagFl2);
    EXPECT_EQ(packet_in.diagFl3, packet2.diagFl3);
    EXPECT_EQ(packet_in.diagSh1, packet2.diagSh1);
    EXPECT_EQ(packet_in.diagSh2, packet2.diagSh2);
    EXPECT_EQ(packet_in.diagSh3, packet2.diagSh3);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(slugs, SLUGS_NAVIGATION)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::slugs::msg::SLUGS_NAVIGATION packet_in{};
    packet_in.u_m = 17.0;
    packet_in.phi_c = 45.0;
    packet_in.theta_c = 73.0;
    packet_in.psiDot_c = 101.0;
    packet_in.ay_body = 129.0;
    packet_in.totalDist = 157.0;
    packet_in.dist2Go = 185.0;
    packet_in.fromWP = 223;
    packet_in.toWP = 34;
    packet_in.h_c = 18691;

    mavlink::slugs::msg::SLUGS_NAVIGATION packet1{};
    mavlink::slugs::msg::SLUGS_NAVIGATION packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.u_m, packet2.u_m);
    EXPECT_EQ(packet1.phi_c, packet2.phi_c);
    EXPECT_EQ(packet1.theta_c, packet2.theta_c);
    EXPECT_EQ(packet1.psiDot_c, packet2.psiDot_c);
    EXPECT_EQ(packet1.ay_body, packet2.ay_body);
    EXPECT_EQ(packet1.totalDist, packet2.totalDist);
    EXPECT_EQ(packet1.dist2Go, packet2.dist2Go);
    EXPECT_EQ(packet1.fromWP, packet2.fromWP);
    EXPECT_EQ(packet1.toWP, packet2.toWP);
    EXPECT_EQ(packet1.h_c, packet2.h_c);
}

#ifdef TEST_INTEROP
TEST(slugs_interop, SLUGS_NAVIGATION)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_slugs_navigation_t packet_c {
         17.0, 45.0, 73.0, 101.0, 129.0, 157.0, 185.0, 18691, 223, 34
    };

    mavlink::slugs::msg::SLUGS_NAVIGATION packet_in{};
    packet_in.u_m = 17.0;
    packet_in.phi_c = 45.0;
    packet_in.theta_c = 73.0;
    packet_in.psiDot_c = 101.0;
    packet_in.ay_body = 129.0;
    packet_in.totalDist = 157.0;
    packet_in.dist2Go = 185.0;
    packet_in.fromWP = 223;
    packet_in.toWP = 34;
    packet_in.h_c = 18691;

    mavlink::slugs::msg::SLUGS_NAVIGATION packet2{};

    mavlink_msg_slugs_navigation_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.u_m, packet2.u_m);
    EXPECT_EQ(packet_in.phi_c, packet2.phi_c);
    EXPECT_EQ(packet_in.theta_c, packet2.theta_c);
    EXPECT_EQ(packet_in.psiDot_c, packet2.psiDot_c);
    EXPECT_EQ(packet_in.ay_body, packet2.ay_body);
    EXPECT_EQ(packet_in.totalDist, packet2.totalDist);
    EXPECT_EQ(packet_in.dist2Go, packet2.dist2Go);
    EXPECT_EQ(packet_in.fromWP, packet2.fromWP);
    EXPECT_EQ(packet_in.toWP, packet2.toWP);
    EXPECT_EQ(packet_in.h_c, packet2.h_c);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(slugs, DATA_LOG)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::slugs::msg::DATA_LOG packet_in{};
    packet_in.fl_1 = 17.0;
    packet_in.fl_2 = 45.0;
    packet_in.fl_3 = 73.0;
    packet_in.fl_4 = 101.0;
    packet_in.fl_5 = 129.0;
    packet_in.fl_6 = 157.0;

    mavlink::slugs::msg::DATA_LOG packet1{};
    mavlink::slugs::msg::DATA_LOG packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.fl_1, packet2.fl_1);
    EXPECT_EQ(packet1.fl_2, packet2.fl_2);
    EXPECT_EQ(packet1.fl_3, packet2.fl_3);
    EXPECT_EQ(packet1.fl_4, packet2.fl_4);
    EXPECT_EQ(packet1.fl_5, packet2.fl_5);
    EXPECT_EQ(packet1.fl_6, packet2.fl_6);
}

#ifdef TEST_INTEROP
TEST(slugs_interop, DATA_LOG)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_data_log_t packet_c {
         17.0, 45.0, 73.0, 101.0, 129.0, 157.0
    };

    mavlink::slugs::msg::DATA_LOG packet_in{};
    packet_in.fl_1 = 17.0;
    packet_in.fl_2 = 45.0;
    packet_in.fl_3 = 73.0;
    packet_in.fl_4 = 101.0;
    packet_in.fl_5 = 129.0;
    packet_in.fl_6 = 157.0;

    mavlink::slugs::msg::DATA_LOG packet2{};

    mavlink_msg_data_log_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.fl_1, packet2.fl_1);
    EXPECT_EQ(packet_in.fl_2, packet2.fl_2);
    EXPECT_EQ(packet_in.fl_3, packet2.fl_3);
    EXPECT_EQ(packet_in.fl_4, packet2.fl_4);
    EXPECT_EQ(packet_in.fl_5, packet2.fl_5);
    EXPECT_EQ(packet_in.fl_6, packet2.fl_6);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(slugs, GPS_DATE_TIME)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::slugs::msg::GPS_DATE_TIME packet_in{};
    packet_in.year = 5;
    packet_in.month = 72;
    packet_in.day = 139;
    packet_in.hour = 206;
    packet_in.min = 17;
    packet_in.sec = 84;
    packet_in.clockStat = 151;
    packet_in.visSat = 218;
    packet_in.useSat = 29;
    packet_in.GppGl = 96;
    packet_in.sigUsedMask = 163;
    packet_in.percentUsed = 230;

    mavlink::slugs::msg::GPS_DATE_TIME packet1{};
    mavlink::slugs::msg::GPS_DATE_TIME packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.year, packet2.year);
    EXPECT_EQ(packet1.month, packet2.month);
    EXPECT_EQ(packet1.day, packet2.day);
    EXPECT_EQ(packet1.hour, packet2.hour);
    EXPECT_EQ(packet1.min, packet2.min);
    EXPECT_EQ(packet1.sec, packet2.sec);
    EXPECT_EQ(packet1.clockStat, packet2.clockStat);
    EXPECT_EQ(packet1.visSat, packet2.visSat);
    EXPECT_EQ(packet1.useSat, packet2.useSat);
    EXPECT_EQ(packet1.GppGl, packet2.GppGl);
    EXPECT_EQ(packet1.sigUsedMask, packet2.sigUsedMask);
    EXPECT_EQ(packet1.percentUsed, packet2.percentUsed);
}

#ifdef TEST_INTEROP
TEST(slugs_interop, GPS_DATE_TIME)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_gps_date_time_t packet_c {
         5, 72, 139, 206, 17, 84, 151, 218, 29, 96, 163, 230
    };

    mavlink::slugs::msg::GPS_DATE_TIME packet_in{};
    packet_in.year = 5;
    packet_in.month = 72;
    packet_in.day = 139;
    packet_in.hour = 206;
    packet_in.min = 17;
    packet_in.sec = 84;
    packet_in.clockStat = 151;
    packet_in.visSat = 218;
    packet_in.useSat = 29;
    packet_in.GppGl = 96;
    packet_in.sigUsedMask = 163;
    packet_in.percentUsed = 230;

    mavlink::slugs::msg::GPS_DATE_TIME packet2{};

    mavlink_msg_gps_date_time_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.year, packet2.year);
    EXPECT_EQ(packet_in.month, packet2.month);
    EXPECT_EQ(packet_in.day, packet2.day);
    EXPECT_EQ(packet_in.hour, packet2.hour);
    EXPECT_EQ(packet_in.min, packet2.min);
    EXPECT_EQ(packet_in.sec, packet2.sec);
    EXPECT_EQ(packet_in.clockStat, packet2.clockStat);
    EXPECT_EQ(packet_in.visSat, packet2.visSat);
    EXPECT_EQ(packet_in.useSat, packet2.useSat);
    EXPECT_EQ(packet_in.GppGl, packet2.GppGl);
    EXPECT_EQ(packet_in.sigUsedMask, packet2.sigUsedMask);
    EXPECT_EQ(packet_in.percentUsed, packet2.percentUsed);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(slugs, MID_LVL_CMDS)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::slugs::msg::MID_LVL_CMDS packet_in{};
    packet_in.target = 41;
    packet_in.hCommand = 17.0;
    packet_in.uCommand = 45.0;
    packet_in.rCommand = 73.0;

    mavlink::slugs::msg::MID_LVL_CMDS packet1{};
    mavlink::slugs::msg::MID_LVL_CMDS packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.target, packet2.target);
    EXPECT_EQ(packet1.hCommand, packet2.hCommand);
    EXPECT_EQ(packet1.uCommand, packet2.uCommand);
    EXPECT_EQ(packet1.rCommand, packet2.rCommand);
}

#ifdef TEST_INTEROP
TEST(slugs_interop, MID_LVL_CMDS)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_mid_lvl_cmds_t packet_c {
         17.0, 45.0, 73.0, 41
    };

    mavlink::slugs::msg::MID_LVL_CMDS packet_in{};
    packet_in.target = 41;
    packet_in.hCommand = 17.0;
    packet_in.uCommand = 45.0;
    packet_in.rCommand = 73.0;

    mavlink::slugs::msg::MID_LVL_CMDS packet2{};

    mavlink_msg_mid_lvl_cmds_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.target, packet2.target);
    EXPECT_EQ(packet_in.hCommand, packet2.hCommand);
    EXPECT_EQ(packet_in.uCommand, packet2.uCommand);
    EXPECT_EQ(packet_in.rCommand, packet2.rCommand);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(slugs, CTRL_SRFC_PT)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::slugs::msg::CTRL_SRFC_PT packet_in{};
    packet_in.target = 139;
    packet_in.bitfieldPt = 17235;

    mavlink::slugs::msg::CTRL_SRFC_PT packet1{};
    mavlink::slugs::msg::CTRL_SRFC_PT packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.target, packet2.target);
    EXPECT_EQ(packet1.bitfieldPt, packet2.bitfieldPt);
}

#ifdef TEST_INTEROP
TEST(slugs_interop, CTRL_SRFC_PT)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_ctrl_srfc_pt_t packet_c {
         17235, 139
    };

    mavlink::slugs::msg::CTRL_SRFC_PT packet_in{};
    packet_in.target = 139;
    packet_in.bitfieldPt = 17235;

    mavlink::slugs::msg::CTRL_SRFC_PT packet2{};

    mavlink_msg_ctrl_srfc_pt_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.target, packet2.target);
    EXPECT_EQ(packet_in.bitfieldPt, packet2.bitfieldPt);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(slugs, SLUGS_CAMERA_ORDER)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::slugs::msg::SLUGS_CAMERA_ORDER packet_in{};
    packet_in.target = 5;
    packet_in.pan = 72;
    packet_in.tilt = -117;
    packet_in.zoom = -50;
    packet_in.moveHome = 17;

    mavlink::slugs::msg::SLUGS_CAMERA_ORDER packet1{};
    mavlink::slugs::msg::SLUGS_CAMERA_ORDER packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.target, packet2.target);
    EXPECT_EQ(packet1.pan, packet2.pan);
    EXPECT_EQ(packet1.tilt, packet2.tilt);
    EXPECT_EQ(packet1.zoom, packet2.zoom);
    EXPECT_EQ(packet1.moveHome, packet2.moveHome);
}

#ifdef TEST_INTEROP
TEST(slugs_interop, SLUGS_CAMERA_ORDER)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_slugs_camera_order_t packet_c {
         5, 72, -117, -50, 17
    };

    mavlink::slugs::msg::SLUGS_CAMERA_ORDER packet_in{};
    packet_in.target = 5;
    packet_in.pan = 72;
    packet_in.tilt = -117;
    packet_in.zoom = -50;
    packet_in.moveHome = 17;

    mavlink::slugs::msg::SLUGS_CAMERA_ORDER packet2{};

    mavlink_msg_slugs_camera_order_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.target, packet2.target);
    EXPECT_EQ(packet_in.pan, packet2.pan);
    EXPECT_EQ(packet_in.tilt, packet2.tilt);
    EXPECT_EQ(packet_in.zoom, packet2.zoom);
    EXPECT_EQ(packet_in.moveHome, packet2.moveHome);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(slugs, CONTROL_SURFACE)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::slugs::msg::CONTROL_SURFACE packet_in{};
    packet_in.target = 29;
    packet_in.idSurface = 96;
    packet_in.mControl = 17.0;
    packet_in.bControl = 45.0;

    mavlink::slugs::msg::CONTROL_SURFACE packet1{};
    mavlink::slugs::msg::CONTROL_SURFACE packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.target, packet2.target);
    EXPECT_EQ(packet1.idSurface, packet2.idSurface);
    EXPECT_EQ(packet1.mControl, packet2.mControl);
    EXPECT_EQ(packet1.bControl, packet2.bControl);
}

#ifdef TEST_INTEROP
TEST(slugs_interop, CONTROL_SURFACE)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_control_surface_t packet_c {
         17.0, 45.0, 29, 96
    };

    mavlink::slugs::msg::CONTROL_SURFACE packet_in{};
    packet_in.target = 29;
    packet_in.idSurface = 96;
    packet_in.mControl = 17.0;
    packet_in.bControl = 45.0;

    mavlink::slugs::msg::CONTROL_SURFACE packet2{};

    mavlink_msg_control_surface_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.target, packet2.target);
    EXPECT_EQ(packet_in.idSurface, packet2.idSurface);
    EXPECT_EQ(packet_in.mControl, packet2.mControl);
    EXPECT_EQ(packet_in.bControl, packet2.bControl);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(slugs, SLUGS_MOBILE_LOCATION)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::slugs::msg::SLUGS_MOBILE_LOCATION packet_in{};
    packet_in.target = 29;
    packet_in.latitude = 17.0;
    packet_in.longitude = 45.0;

    mavlink::slugs::msg::SLUGS_MOBILE_LOCATION packet1{};
    mavlink::slugs::msg::SLUGS_MOBILE_LOCATION packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.target, packet2.target);
    EXPECT_EQ(packet1.latitude, packet2.latitude);
    EXPECT_EQ(packet1.longitude, packet2.longitude);
}

#ifdef TEST_INTEROP
TEST(slugs_interop, SLUGS_MOBILE_LOCATION)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_slugs_mobile_location_t packet_c {
         17.0, 45.0, 29
    };

    mavlink::slugs::msg::SLUGS_MOBILE_LOCATION packet_in{};
    packet_in.target = 29;
    packet_in.latitude = 17.0;
    packet_in.longitude = 45.0;

    mavlink::slugs::msg::SLUGS_MOBILE_LOCATION packet2{};

    mavlink_msg_slugs_mobile_location_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.target, packet2.target);
    EXPECT_EQ(packet_in.latitude, packet2.latitude);
    EXPECT_EQ(packet_in.longitude, packet2.longitude);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(slugs, SLUGS_CONFIGURATION_CAMERA)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::slugs::msg::SLUGS_CONFIGURATION_CAMERA packet_in{};
    packet_in.target = 5;
    packet_in.idOrder = 72;
    packet_in.order = 139;

    mavlink::slugs::msg::SLUGS_CONFIGURATION_CAMERA packet1{};
    mavlink::slugs::msg::SLUGS_CONFIGURATION_CAMERA packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.target, packet2.target);
    EXPECT_EQ(packet1.idOrder, packet2.idOrder);
    EXPECT_EQ(packet1.order, packet2.order);
}

#ifdef TEST_INTEROP
TEST(slugs_interop, SLUGS_CONFIGURATION_CAMERA)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_slugs_configuration_camera_t packet_c {
         5, 72, 139
    };

    mavlink::slugs::msg::SLUGS_CONFIGURATION_CAMERA packet_in{};
    packet_in.target = 5;
    packet_in.idOrder = 72;
    packet_in.order = 139;

    mavlink::slugs::msg::SLUGS_CONFIGURATION_CAMERA packet2{};

    mavlink_msg_slugs_configuration_camera_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.target, packet2.target);
    EXPECT_EQ(packet_in.idOrder, packet2.idOrder);
    EXPECT_EQ(packet_in.order, packet2.order);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(slugs, ISR_LOCATION)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::slugs::msg::ISR_LOCATION packet_in{};
    packet_in.target = 41;
    packet_in.latitude = 17.0;
    packet_in.longitude = 45.0;
    packet_in.height = 73.0;
    packet_in.option1 = 108;
    packet_in.option2 = 175;
    packet_in.option3 = 242;

    mavlink::slugs::msg::ISR_LOCATION packet1{};
    mavlink::slugs::msg::ISR_LOCATION packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.target, packet2.target);
    EXPECT_EQ(packet1.latitude, packet2.latitude);
    EXPECT_EQ(packet1.longitude, packet2.longitude);
    EXPECT_EQ(packet1.height, packet2.height);
    EXPECT_EQ(packet1.option1, packet2.option1);
    EXPECT_EQ(packet1.option2, packet2.option2);
    EXPECT_EQ(packet1.option3, packet2.option3);
}

#ifdef TEST_INTEROP
TEST(slugs_interop, ISR_LOCATION)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_isr_location_t packet_c {
         17.0, 45.0, 73.0, 41, 108, 175, 242
    };

    mavlink::slugs::msg::ISR_LOCATION packet_in{};
    packet_in.target = 41;
    packet_in.latitude = 17.0;
    packet_in.longitude = 45.0;
    packet_in.height = 73.0;
    packet_in.option1 = 108;
    packet_in.option2 = 175;
    packet_in.option3 = 242;

    mavlink::slugs::msg::ISR_LOCATION packet2{};

    mavlink_msg_isr_location_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.target, packet2.target);
    EXPECT_EQ(packet_in.latitude, packet2.latitude);
    EXPECT_EQ(packet_in.longitude, packet2.longitude);
    EXPECT_EQ(packet_in.height, packet2.height);
    EXPECT_EQ(packet_in.option1, packet2.option1);
    EXPECT_EQ(packet_in.option2, packet2.option2);
    EXPECT_EQ(packet_in.option3, packet2.option3);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(slugs, VOLT_SENSOR)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::slugs::msg::VOLT_SENSOR packet_in{};
    packet_in.r2Type = 17;
    packet_in.voltage = 17235;
    packet_in.reading2 = 17339;

    mavlink::slugs::msg::VOLT_SENSOR packet1{};
    mavlink::slugs::msg::VOLT_SENSOR packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.r2Type, packet2.r2Type);
    EXPECT_EQ(packet1.voltage, packet2.voltage);
    EXPECT_EQ(packet1.reading2, packet2.reading2);
}

#ifdef TEST_INTEROP
TEST(slugs_interop, VOLT_SENSOR)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_volt_sensor_t packet_c {
         17235, 17339, 17
    };

    mavlink::slugs::msg::VOLT_SENSOR packet_in{};
    packet_in.r2Type = 17;
    packet_in.voltage = 17235;
    packet_in.reading2 = 17339;

    mavlink::slugs::msg::VOLT_SENSOR packet2{};

    mavlink_msg_volt_sensor_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.r2Type, packet2.r2Type);
    EXPECT_EQ(packet_in.voltage, packet2.voltage);
    EXPECT_EQ(packet_in.reading2, packet2.reading2);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(slugs, PTZ_STATUS)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::slugs::msg::PTZ_STATUS packet_in{};
    packet_in.zoom = 17;
    packet_in.pan = 17235;
    packet_in.tilt = 17339;

    mavlink::slugs::msg::PTZ_STATUS packet1{};
    mavlink::slugs::msg::PTZ_STATUS packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.zoom, packet2.zoom);
    EXPECT_EQ(packet1.pan, packet2.pan);
    EXPECT_EQ(packet1.tilt, packet2.tilt);
}

#ifdef TEST_INTEROP
TEST(slugs_interop, PTZ_STATUS)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_ptz_status_t packet_c {
         17235, 17339, 17
    };

    mavlink::slugs::msg::PTZ_STATUS packet_in{};
    packet_in.zoom = 17;
    packet_in.pan = 17235;
    packet_in.tilt = 17339;

    mavlink::slugs::msg::PTZ_STATUS packet2{};

    mavlink_msg_ptz_status_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.zoom, packet2.zoom);
    EXPECT_EQ(packet_in.pan, packet2.pan);
    EXPECT_EQ(packet_in.tilt, packet2.tilt);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(slugs, UAV_STATUS)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::slugs::msg::UAV_STATUS packet_in{};
    packet_in.target = 65;
    packet_in.latitude = 17.0;
    packet_in.longitude = 45.0;
    packet_in.altitude = 73.0;
    packet_in.speed = 101.0;
    packet_in.course = 129.0;

    mavlink::slugs::msg::UAV_STATUS packet1{};
    mavlink::slugs::msg::UAV_STATUS packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.target, packet2.target);
    EXPECT_EQ(packet1.latitude, packet2.latitude);
    EXPECT_EQ(packet1.longitude, packet2.longitude);
    EXPECT_EQ(packet1.altitude, packet2.altitude);
    EXPECT_EQ(packet1.speed, packet2.speed);
    EXPECT_EQ(packet1.course, packet2.course);
}

#ifdef TEST_INTEROP
TEST(slugs_interop, UAV_STATUS)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_uav_status_t packet_c {
         17.0, 45.0, 73.0, 101.0, 129.0, 65
    };

    mavlink::slugs::msg::UAV_STATUS packet_in{};
    packet_in.target = 65;
    packet_in.latitude = 17.0;
    packet_in.longitude = 45.0;
    packet_in.altitude = 73.0;
    packet_in.speed = 101.0;
    packet_in.course = 129.0;

    mavlink::slugs::msg::UAV_STATUS packet2{};

    mavlink_msg_uav_status_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.target, packet2.target);
    EXPECT_EQ(packet_in.latitude, packet2.latitude);
    EXPECT_EQ(packet_in.longitude, packet2.longitude);
    EXPECT_EQ(packet_in.altitude, packet2.altitude);
    EXPECT_EQ(packet_in.speed, packet2.speed);
    EXPECT_EQ(packet_in.course, packet2.course);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(slugs, STATUS_GPS)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::slugs::msg::STATUS_GPS packet_in{};
    packet_in.csFails = 17443;
    packet_in.gpsQuality = 151;
    packet_in.msgsType = 218;
    packet_in.posStatus = 29;
    packet_in.magVar = 17.0;
    packet_in.magDir = 96;
    packet_in.modeInd = 163;

    mavlink::slugs::msg::STATUS_GPS packet1{};
    mavlink::slugs::msg::STATUS_GPS packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.csFails, packet2.csFails);
    EXPECT_EQ(packet1.gpsQuality, packet2.gpsQuality);
    EXPECT_EQ(packet1.msgsType, packet2.msgsType);
    EXPECT_EQ(packet1.posStatus, packet2.posStatus);
    EXPECT_EQ(packet1.magVar, packet2.magVar);
    EXPECT_EQ(packet1.magDir, packet2.magDir);
    EXPECT_EQ(packet1.modeInd, packet2.modeInd);
}

#ifdef TEST_INTEROP
TEST(slugs_interop, STATUS_GPS)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_status_gps_t packet_c {
         17.0, 17443, 151, 218, 29, 96, 163
    };

    mavlink::slugs::msg::STATUS_GPS packet_in{};
    packet_in.csFails = 17443;
    packet_in.gpsQuality = 151;
    packet_in.msgsType = 218;
    packet_in.posStatus = 29;
    packet_in.magVar = 17.0;
    packet_in.magDir = 96;
    packet_in.modeInd = 163;

    mavlink::slugs::msg::STATUS_GPS packet2{};

    mavlink_msg_status_gps_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.csFails, packet2.csFails);
    EXPECT_EQ(packet_in.gpsQuality, packet2.gpsQuality);
    EXPECT_EQ(packet_in.msgsType, packet2.msgsType);
    EXPECT_EQ(packet_in.posStatus, packet2.posStatus);
    EXPECT_EQ(packet_in.magVar, packet2.magVar);
    EXPECT_EQ(packet_in.magDir, packet2.magDir);
    EXPECT_EQ(packet_in.modeInd, packet2.modeInd);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(slugs, NOVATEL_DIAG)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::slugs::msg::NOVATEL_DIAG packet_in{};
    packet_in.timeStatus = 163;
    packet_in.receiverStatus = 963497464;
    packet_in.solStatus = 230;
    packet_in.posType = 41;
    packet_in.velType = 108;
    packet_in.posSolAge = 45.0;
    packet_in.csFails = 17651;

    mavlink::slugs::msg::NOVATEL_DIAG packet1{};
    mavlink::slugs::msg::NOVATEL_DIAG packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.timeStatus, packet2.timeStatus);
    EXPECT_EQ(packet1.receiverStatus, packet2.receiverStatus);
    EXPECT_EQ(packet1.solStatus, packet2.solStatus);
    EXPECT_EQ(packet1.posType, packet2.posType);
    EXPECT_EQ(packet1.velType, packet2.velType);
    EXPECT_EQ(packet1.posSolAge, packet2.posSolAge);
    EXPECT_EQ(packet1.csFails, packet2.csFails);
}

#ifdef TEST_INTEROP
TEST(slugs_interop, NOVATEL_DIAG)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_novatel_diag_t packet_c {
         963497464, 45.0, 17651, 163, 230, 41, 108
    };

    mavlink::slugs::msg::NOVATEL_DIAG packet_in{};
    packet_in.timeStatus = 163;
    packet_in.receiverStatus = 963497464;
    packet_in.solStatus = 230;
    packet_in.posType = 41;
    packet_in.velType = 108;
    packet_in.posSolAge = 45.0;
    packet_in.csFails = 17651;

    mavlink::slugs::msg::NOVATEL_DIAG packet2{};

    mavlink_msg_novatel_diag_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.timeStatus, packet2.timeStatus);
    EXPECT_EQ(packet_in.receiverStatus, packet2.receiverStatus);
    EXPECT_EQ(packet_in.solStatus, packet2.solStatus);
    EXPECT_EQ(packet_in.posType, packet2.posType);
    EXPECT_EQ(packet_in.velType, packet2.velType);
    EXPECT_EQ(packet_in.posSolAge, packet2.posSolAge);
    EXPECT_EQ(packet_in.csFails, packet2.csFails);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(slugs, SENSOR_DIAG)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::slugs::msg::SENSOR_DIAG packet_in{};
    packet_in.float1 = 17.0;
    packet_in.float2 = 45.0;
    packet_in.int1 = 17651;
    packet_in.char1 = -93;

    mavlink::slugs::msg::SENSOR_DIAG packet1{};
    mavlink::slugs::msg::SENSOR_DIAG packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.float1, packet2.float1);
    EXPECT_EQ(packet1.float2, packet2.float2);
    EXPECT_EQ(packet1.int1, packet2.int1);
    EXPECT_EQ(packet1.char1, packet2.char1);
}

#ifdef TEST_INTEROP
TEST(slugs_interop, SENSOR_DIAG)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_sensor_diag_t packet_c {
         17.0, 45.0, 17651, -93
    };

    mavlink::slugs::msg::SENSOR_DIAG packet_in{};
    packet_in.float1 = 17.0;
    packet_in.float2 = 45.0;
    packet_in.int1 = 17651;
    packet_in.char1 = -93;

    mavlink::slugs::msg::SENSOR_DIAG packet2{};

    mavlink_msg_sensor_diag_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.float1, packet2.float1);
    EXPECT_EQ(packet_in.float2, packet2.float2);
    EXPECT_EQ(packet_in.int1, packet2.int1);
    EXPECT_EQ(packet_in.char1, packet2.char1);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(slugs, BOOT)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::slugs::msg::BOOT packet_in{};
    packet_in.version = 963497464;

    mavlink::slugs::msg::BOOT packet1{};
    mavlink::slugs::msg::BOOT packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.version, packet2.version);
}

#ifdef TEST_INTEROP
TEST(slugs_interop, BOOT)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_boot_t packet_c {
         963497464
    };

    mavlink::slugs::msg::BOOT packet_in{};
    packet_in.version = 963497464;

    mavlink::slugs::msg::BOOT packet2{};

    mavlink_msg_boot_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.version, packet2.version);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif
