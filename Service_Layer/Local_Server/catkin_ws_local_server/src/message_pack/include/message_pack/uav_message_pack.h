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
#ifndef R_UAV_MESSAGE_PACK_H
#define R_UAV_MESSAGE_PACK_H
#include "ros/ros.h"
#include "iostream"
#include <cloud_common/socket_data_packet_stamp_msg.h>
#include <cloud_common/define_common.h>
#include "sensor_msgs/NavSatFix.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/TwistStamped.h"
#include "mavros_msgs/State.h"
#include "x2struct/x2struct.hpp"
using namespace dtcloud;
class uav_message_pack
{
public:
  uav_message_pack();
  void globalPosMsgSubCallback(const sensor_msgs::NavSatFix::ConstPtr& msg);
  void localPosMsgSubCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
  void localVelocitySubCallback(const geometry_msgs::TwistStamped::ConstPtr& msg);
  void uavStateSubCallback(const mavros_msgs::StateConstPtr& msg);
private:
  ros::Publisher             _iotMessagePub;
  string                     _iotMessagePubTopic;
  int                        _sourceID;
  int                        _targetID;
  float                      _msgPubFrequency;
  string                     _globalPosMsgSubTopic;
  string                     _localPosMsgSubTopic;
  string                     _localVelMsgSubTopic;
  string                     _uavStateMsgSubTopic;


  ros::Subscriber            _gloPosMsgSub;
  ros::Subscriber            _localPosMsgSub;
  ros::Subscriber            _localVelMsgSub;
  ros::Subscriber            _uavStateMsgSub;

};

#endif // R_UAV_MESSAGE_PACK_H
