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
#include "../include/message_pack/uav_message_pack.h"
int send_time =0;
uav_message_pack::uav_message_pack()
{
  ros::NodeHandle n("~");
  n.getParam("IotMessagePubTopic",_iotMessagePubTopic);
  n.getParam("SourceID",_sourceID);
  n.getParam("TargetID",_targetID);
  n.getParam("GlobalPositionMessageSubTopic",_globalPosMsgSubTopic);
  n.getParam("LocalPositionMessageSubTopic",_localPosMsgSubTopic);
  n.getParam("LocalVelocityMessageSubTopic",_localVelMsgSubTopic);
  n.getParam("UavStateMessageSubTopic",_uavStateMsgSubTopic);
  n.getParam("MessagePubFrequency",_msgPubFrequency);
  _iotMessagePub = n.advertise<cloud_common::socket_data_packet_stamp_msg>(_iotMessagePubTopic,1);
  _gloPosMsgSub = n.subscribe(_globalPosMsgSubTopic,1,&uav_message_pack::globalPosMsgSubCallback,this);
  _localPosMsgSub = n.subscribe(_localPosMsgSubTopic,1,&uav_message_pack::localPosMsgSubCallback,this);
  _localVelMsgSub = n.subscribe(_localVelMsgSubTopic,1,&uav_message_pack::localVelocitySubCallback,this);
  _uavStateMsgSub = n.subscribe(_uavStateMsgSubTopic,1,&uav_message_pack::uavStateSubCallback,this);
  send_time = 0;
}

void uav_message_pack::uavStateSubCallback(const mavros_msgs::StateConstPtr &msg)
{
//if(send_time==0)
{
  cloud_common::socket_data_packet_stamp_msg cloudMsgPub;
  cloudMsgPub.MessageID = UavStateMsgID;
  cloudMsgPub.SourceID = _sourceID;
  cloudMsgPub.TargetID = _targetID;
  cloudMsgPub.TimeStamp = msg.get()->header.stamp.toNSec();//_nsec是纳秒
  UavStateMsg uavStateMsg;
  uavStateMsg.armed = msg.get()->armed;
  uavStateMsg.connected = msg.get()->connected;
  uavStateMsg.guided = msg.get()->guided;
  uavStateMsg.manual_input = msg.get()->manual_input;
  uavStateMsg.mode = msg.get()->mode;
  uavStateMsg.system_status = msg.get()->system_status;
  cloudMsgPub.MessageData = x2struct::X::tojson(uavStateMsg);
  _iotMessagePub.publish(cloudMsgPub);
send_time =1;
}
}

void uav_message_pack::globalPosMsgSubCallback(const sensor_msgs::NavSatFix::ConstPtr &msg)
{
  cloud_common::socket_data_packet_stamp_msg cloudMsgPub;
  cloudMsgPub.MessageID = UavGlobalPositionMessageID;
  cloudMsgPub.SourceID = _sourceID;
  cloudMsgPub.TargetID = _targetID;
  cloudMsgPub.TimeStamp = msg.get()->header.stamp.toNSec();//_nsec是纳秒
  UavGlobalPositionMessage gloPosMsg;
  gloPosMsg.altitude = msg.get()->altitude;
  gloPosMsg.latitude = msg.get()->latitude;
  gloPosMsg.longitude = msg.get()->longitude;
  gloPosMsg.position_covariance_type = msg.get()->position_covariance_type;
  gloPosMsg.position_covariance.resize(9);
  gloPosMsg.service = msg.get()->status.service;
  gloPosMsg.status = msg.get()->status.status;
  for(int i =0;i<9;i++)
  {
    gloPosMsg.position_covariance.at(i) = msg.get()->position_covariance.at(i);
  }
  cloudMsgPub.MessageData = x2struct::X::tojson(gloPosMsg);
  _iotMessagePub.publish(cloudMsgPub);
}

void uav_message_pack::localPosMsgSubCallback(const geometry_msgs::PoseStamped::ConstPtr &msg)
{
  cloud_common::socket_data_packet_stamp_msg cloudMsgPub;
  cloudMsgPub.MessageID = UavLocalPositionMessageID;
  cloudMsgPub.SourceID = _sourceID;
  cloudMsgPub.TargetID = _targetID;
  cloudMsgPub.TimeStamp = msg.get()->header.stamp.toNSec();//_nsec是纳秒
  UavLocalPositionMessage localPosMsg;
  localPosMsg.position_x = msg.get()->pose.position.x;
  localPosMsg.position_y = msg.get()->pose.position.y;
  localPosMsg.position_z = msg.get()->pose.position.z;
  localPosMsg.rotation_x = msg.get()->pose.orientation.x;
  localPosMsg.rotation_y = msg.get()->pose.orientation.y;
  localPosMsg.rotation_z = msg.get()->pose.orientation.z;
  localPosMsg.rotation_w = msg.get()->pose.orientation.w;
  cloudMsgPub.MessageData = x2struct::X::tojson(localPosMsg);
  _iotMessagePub.publish(cloudMsgPub);
}

void uav_message_pack::localVelocitySubCallback(const geometry_msgs::TwistStamped::ConstPtr &msg)
{
  cloud_common::socket_data_packet_stamp_msg cloudMsgPub;
  cloudMsgPub.MessageID = UavLocalVelocityMessageID;
  cloudMsgPub.SourceID = _sourceID;
  cloudMsgPub.TargetID = _targetID;
  cloudMsgPub.TimeStamp = msg.get()->header.stamp.toNSec();//_nsec是纳秒
  UavLocalVelocityMessage localVelMsg;
  localVelMsg.linear_velocity_x = msg.get()->twist.linear.x;
  localVelMsg.linear_velocity_y = msg.get()->twist.linear.y;
  localVelMsg.linear_velocity_z = msg.get()->twist.linear.z;
  localVelMsg.anger_velocity_x = msg.get()->twist.angular.x;
  localVelMsg.anger_velocity_y = msg.get()->twist.angular.y;
  localVelMsg.anger_velocity_z = msg.get()->twist.angular.z;
  cloudMsgPub.MessageData = x2struct::X::tojson(localVelMsg);
  _iotMessagePub.publish(cloudMsgPub);
}
