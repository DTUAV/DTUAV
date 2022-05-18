/*
© Guangdong University of Technology,
© The Laboratory of Intelligent Decision and Cooperative Control,
© 2021-2022,
© Author: Yuanlin Yang (yongwang0808@163.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
<http://www.apache.org/licenses/LICENSE-2.0>.
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#ifndef Cloud_CONNECTION_H
#define Cloud_CONNECTION_H
#include <iostream>
#include "../src/LinkSDK/core/aiot_state_api.h"
#include "../src/LinkSDK/core/aiot_sysdep_api.h"
#include "../src/LinkSDK/core/aiot_mqtt_api.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ros/ros.h>
#include <x2struct/x2struct.hpp>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <../include/mavlink/v1.0/common/mavlink.h>
#include <iomanip>
#include <string>
#include "ros/ros.h"
#include "../include/mavros_msgs/Mavlink.h"
#include "geometry_msgs/TransformStamped.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "geometry_msgs/TwistStamped.h"
#include "geometry_msgs/TwistWithCovarianceStamped.h"
#include "geometry_msgs/Vector3Stamped.h"
#include "geometry_msgs/AccelWithCovarianceStamped.h"
#include "geometry_msgs/Quaternion.h"
#include "std_msgs/Float64.h"
#include "std_msgs/UInt32.h"
#include "sensor_msgs/NavSatFix.h"
#include "sensor_msgs/Imu.h"
#include "sensor_msgs/FluidPressure.h"
#include "sensor_msgs/MagneticField.h"
#include "sensor_msgs/Temperature.h"
#include "sensor_msgs/LaserScan.h"
#include "sensor_msgs/Range.h"
#include "sensor_msgs/TimeReference.h"
#include "trajectory_msgs/MultiDOFJointTrajectory.h"
#include "geographic_msgs/GeoPointStamped.h"
#include "nav_msgs/Odometry.h"
#include "nav_msgs/Path.h"
#include "iostream"
#include "../include/mavros_msgs/Mavlink.h"
#include "../include/mavros_msgs/ActuatorControl.h"
#include "../include/mavros_msgs/ADSBVehicle.h"
#include "../include/mavros_msgs/Altitude.h"
#include "../include/mavros_msgs/CamIMUStamp.h"
#include "../include/mavros_msgs/CompanionProcessStatus.h"
#include "../include/mavros_msgs/DebugValue.h"
#include "../include/mavros_msgs/EstimatorStatus.h"
#include "../include/mavros_msgs/ExtendedState.h"
#include "../include/mavros_msgs/HomePosition.h"
#include "../include/mavros_msgs/RTCM.h"
#include "../include/mavros_msgs/HilActuatorControls.h"
#include "../include/mavros_msgs/HilControls.h"
#include "../include/mavros_msgs/HilGPS.h"
#include "../include/mavros_msgs/HilSensor.h"
#include "../include/mavros_msgs/OpticalFlowRad.h"
#include "../include/mavros_msgs/RCIn.h"
#include "../include/mavros_msgs/HilStateQuaternion.h"
#include "../include/mavros_msgs/HomePosition.h"
#include "../include/mavros_msgs/LogData.h"
#include "../include/mavros_msgs/LogEntry.h"
#include "../include/mavros_msgs/ManualControl.h"
#include "../include/mavros_msgs/WaypointReached.h"
#include "../include/mavros_msgs/WaypointList.h"
#include "../include/mavros_msgs/MountControl.h"
#include "../include/mavros_msgs/OnboardComputerStatus.h"
#include "../include/mavros_msgs/Param.h"
#include "../include/mavros_msgs/RadioStatus.h"
#include "../include/mavros_msgs/RCOut.h"
#include "../include/mavros_msgs/OverrideRCIn.h"
#include "../include/mavros_msgs/Thrust.h"
#include "../include/mavros_msgs/AttitudeTarget.h"
#include "../include/mavros_msgs/GlobalPositionTarget.h"
#include "../include/mavros_msgs/PositionTarget.h"
#include "../include/mavros_msgs/State.h"
#include "../include/mavros_msgs/StatusText.h"
#include "../include/mavros_msgs/TimesyncStatus.h"
#include "../include/mavros_msgs/Trajectory.h"
#include "../include/mavros_msgs/VFR_HUD.h"
using namespace std;
namespace DTUAVCARS {
static pthread_t g_mqtt_process_thread;
static pthread_t g_mqtt_recv_thread;
static pthread_t iot_state_thread;
int32_t     res = STATE_SUCCESS;
void       *mqtt_handle = NULL;
int8_t      public_instance = 1;
char       *url = "iot-as-mqtt.cn-shanghai.aliyuncs.com";
char        host[100] = {0};
uint16_t    port = 443;
aiot_sysdep_network_cred_t cred;

char *product_key       = "a1mcqCrCCBy";
char *device_name       = "MainServer";
char *device_secret     = "5776ba4032168e72798de531819278a7";
char *iot_pub_topic     = "pub";
char *iot_sub_topic     = "sub";

string ros_sub_topic = "/sub";
string ros_pub_topic = "/pub";
string ros_iot_state_pub_topic = "/state_pub";
string object_name = "uav";

string iot_connection_state = "off";
string iot_work_state = "error";


ros::Publisher iot_msg_pub;
ros::Publisher iot_state_pub;
ros::Subscriber iot_msg_sub;
}
#endif // Cloud_CONNECTION_H
