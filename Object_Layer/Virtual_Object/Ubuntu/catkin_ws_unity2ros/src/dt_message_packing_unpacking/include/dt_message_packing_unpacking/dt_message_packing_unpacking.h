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
#ifndef DT_MESSAGE_PACKING_UNPACKING_H
#define DT_MESSAGE_PACKING_UNPACKING_H
#include "ros/ros.h"
#include "iostream"
#include <dt_common/socket_data_packet_stamp_msg.h>
#include <dt_common/define_common.h>
#include "sensor_msgs/NavSatFix.h"
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include "mavros_msgs/State.h"
#include "mavros_msgs/GlobalPositionTarget.h"
#include "x2struct/x2struct.hpp"
#include "std_msgs/Bool.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Int8.h"
#include <dt_message_package/CloudMessage.h>
using namespace DTUAV;
class dt_message_packing_unpacking
{
public:
  dt_message_packing_unpacking();
  void globalPosMsgSubCallback(const sensor_msgs::NavSatFix::ConstPtr& msg);
  void localPosMsgSubCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
  void localVelocitySubCallback(const geometry_msgs::TwistStamped::ConstPtr& msg);
  void uavStateSubCallback(const mavros_msgs::StateConstPtr& msg);
  void iotMessageSubCallback(const dt_message_package::CloudMessageConstPtr& msg);
private:
  ros::Publisher             _iotMessagePub;
  string                     _iotMessagePubTopic;
  int                        _sourceID;
  int                        _targetID;
  int                        _dtObjectID;
  float                      _msgPubFrequency;
  string                     _globalPosMsgSubTopic;
  string                     _localPosMsgSubTopic;
  string                     _localVelMsgSubTopic;
  string                     _uavStateMsgSubTopic;


  ros::Subscriber            _gloPosMsgSub;
  ros::Subscriber            _localPosMsgSub;
  ros::Subscriber            _localVelMsgSub;
  ros::Subscriber            _uavStateMsgSub;

  ros::Subscriber           _iotMessageSub;

  string                   _iotMessageSubTopic;

  ros::Publisher _cloud_server_local_position_pub;
  ros::Publisher _cloud_server_global_position_pub;
  ros::Publisher _cloud_server_velocity_pub;
  ros::Publisher _cloud_server_control_apply_pub;
  ros::Publisher _cloud_server_target_cmd_type_pub;

  ros::Publisher _vr_server_local_position_pub;
  ros::Publisher _vr_server_global_position_pub;
  ros::Publisher _vr_server_velocity_pub;
  ros::Publisher _vr_server_control_apply_pub;
  ros::Publisher _vr_server_target_cmd_type_pub;

  ros::Publisher _local_server_local_position_pub;
  ros::Publisher _local_server_global_position_pub;
  ros::Publisher _local_server_velocity_pub;
  ros::Publisher _local_server_control_apply_pub;
  ros::Publisher _local_server_target_cmd_type_pub;

  ros::Publisher _dt_object_local_position_pub;
  ros::Publisher _dt_object_global_position_pub;
  ros::Publisher _dt_object_velocity_pub;
  ros::Publisher _dt_object_control_apply_pub;
  ros::Publisher _dt_object_target_cmd_type_pub;

  std::string _velocity_cmd_pub_topic;
  std::string _local_position_cmd_pub_topic;
  std::string _global_position_cmd_pub_topic;
  std::string _cur_control_type_pub_topic;
  std::string _target_cmd_type_pub_topic;


  std::string _cloud_server_local_position_pub_topic;
  std::string _cloud_server_global_position_pub_topic;
  std::string _cloud_server_velocity_pub_topic;
  std::string _cloud_server_control_apply_pub_topic;
  std::string _cloud_server_target_cmd_type_pub_topic;

  std::string _vr_server_local_position_pub_topic;
  std::string _vr_server_global_position_pub_topic;
  std::string _vr_server_velocity_pub_topic;
  std::string _vr_server_control_apply_pub_topic;
  std::string _vr_server_target_cmd_type_pub_topic;

  std::string _local_server_local_position_pub_topic;
  std::string _local_server_global_position_pub_topic;
  std::string _local_server_velocity_pub_topic;
  std::string _local_server_control_apply_pub_topic;
  std::string _local_server_target_cmd_type_pub_topic;

  std::string _dt_object_local_position_pub_topic;
  std::string _dt_object_global_position_pub_topic;
  std::string _dt_object_velocity_pub_topic;
  std::string _dt_object_control_apply_pub_topic;
  std::string _dt_object_target_cmd_type_pub_topic;


};

#endif // DT_MESSAGE_PACKING_UNPACKING_H
