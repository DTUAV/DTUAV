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
#ifndef R_UAV_MESSAGE_UNPACK_H
#define R_UAV_MESSAGE_UNPACK_H
#include <cloud_common/socket_data_packet_stamp_msg.h>
#include <cloud_common/define_common.h>
#include "std_msgs/Bool.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Twist.h"
#include "ros/ros.h"
using namespace dtcloud;

class uav_message_unpack
{
public:
  uav_message_unpack();
  void IotMessageSubCallback(const cloud_common::socket_data_packet_stamp_msgConstPtr& msg);

private:
  ros::Subscriber _iotMessageSub;
  ros::Publisher _refPosMsgPub;
  ros::Publisher _refVelMsgPub;


  string _iotMessageSubTopic;

  string _refPoseMessageTopic;
  string _refVelocityMessageTopic;
};

#endif // R_UAV_MESSAGE_UNPACK_H
