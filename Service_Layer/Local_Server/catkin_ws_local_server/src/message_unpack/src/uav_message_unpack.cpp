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
#include "../include/message_unpack/uav_message_unpack.h"

uav_message_unpack::uav_message_unpack()
{
  ros::NodeHandle n("~");
  n.getParam("IotMessageSubTopic",_iotMessageSubTopic);

  n.getParam("RefPoseMessageTopic",_refPoseMessageTopic);
  n.getParam("RefVelocityMessageTopic",_refVelocityMessageTopic);

  _iotMessageSub = n.subscribe(_iotMessageSubTopic,1,&uav_message_unpack::IotMessageSubCallback,this);


  _refPosMsgPub = n.advertise<geometry_msgs::PoseStamped>(_refPoseMessageTopic,1);

  _refVelMsgPub   = n.advertise<geometry_msgs::Twist>(_refVelocityMessageTopic,1);

}
void uav_message_unpack::IotMessageSubCallback(const cloud_common::socket_data_packet_stamp_msgConstPtr& msg)
{switch (msg.get()->MessageID) {
  case UavRefPoseMessageID:
  {
    UavRefPoseMessage iotRefPoseMsg;
    bool is_load = x2struct::X::loadjson(msg.get()->MessageData,iotRefPoseMsg,false);
    if(is_load)
    {
      geometry_msgs::PoseStamped refPoseMsg;
      refPoseMsg.header.frame_id = "Server0";
      refPoseMsg.header.stamp = ros::Time::now();
      refPoseMsg.pose.orientation.x = iotRefPoseMsg.rotation_x;
      refPoseMsg.pose.orientation.y = iotRefPoseMsg.rotation_y;
      refPoseMsg.pose.orientation.z = iotRefPoseMsg.rotation_z;
      refPoseMsg.pose.orientation.w = iotRefPoseMsg.rotation_w;
      refPoseMsg.pose.position.x    = iotRefPoseMsg.position_x;
      refPoseMsg.pose.position.y    = iotRefPoseMsg.position_y;
      refPoseMsg.pose.position.z    = iotRefPoseMsg.position_z;
      _refPosMsgPub.publish(refPoseMsg);
    }
  }
    break;
  case UavRefVelocityMessageID:
  {
    UavRefVelocityMessage iotRefVelocityMsg;
    bool is_load = x2struct::X::loadjson(msg.get()->MessageData,iotRefVelocityMsg,false);
    if(is_load)
    {
      geometry_msgs::Twist refVelocityMsg;
      refVelocityMsg.linear.x = iotRefVelocityMsg.linear_velocity_x;
      refVelocityMsg.linear.y = iotRefVelocityMsg.linear_velocity_y;
      refVelocityMsg.linear.z = iotRefVelocityMsg.linear_velocity_z;
      refVelocityMsg.angular.x = iotRefVelocityMsg.anger_velocity_x;
      refVelocityMsg.angular.y = iotRefVelocityMsg.anger_velocity_y;
      refVelocityMsg.angular.z = iotRefVelocityMsg.anger_velocity_z;
      _refVelMsgPub.publish(refVelocityMsg);
    }
  }
    break;
  case 1:
  {
    MrCommandMessage mrCommandMsg;
    bool is_load = x2struct::X::loadjson(msg.get()->MessageData,mrCommandMsg,false);
    if(is_load)
    {
      geometry_msgs::Twist refVelocityMsg;
      refVelocityMsg.linear.x = mrCommandMsg.LinearVelocityX;
      refVelocityMsg.linear.y = mrCommandMsg.LinearVelocityY;
      refVelocityMsg.linear.z = mrCommandMsg.LinearVelocityZ;
      refVelocityMsg.angular.x = 0;
      refVelocityMsg.angular.y = 0;
      refVelocityMsg.angular.z = 0;
      _refVelMsgPub.publish(refVelocityMsg);
      geometry_msgs::PoseStamped refPoseMsg;
      refPoseMsg.header.frame_id = "mr";
      refPoseMsg.header.stamp = ros::Time::now();
      refPoseMsg.pose.orientation.x = mrCommandMsg.SpatialPositionX;
      refPoseMsg.pose.orientation.y = mrCommandMsg.SpatialPositionY;
      refPoseMsg.pose.orientation.z = mrCommandMsg.LinearVelocityZ;
      refPoseMsg.pose.orientation.w = 1;
      refPoseMsg.pose.position.x    = 0;
      refPoseMsg.pose.position.y    = 0;
      refPoseMsg.pose.position.z    = 0;
      _refPosMsgPub.publish(refPoseMsg);
    }
  }
    break;
  default:
    break;
  }

}


