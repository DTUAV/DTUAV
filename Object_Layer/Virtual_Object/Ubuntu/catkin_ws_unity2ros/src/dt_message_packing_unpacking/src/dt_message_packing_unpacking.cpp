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
#include "../include/dt_message_packing_unpacking/dt_message_packing_unpacking.h"
using namespace DTUAV;
int send_time =0;
dt_message_packing_unpacking::dt_message_packing_unpacking()
{
  ros::NodeHandle n("~");
  n.getParam("IotMessagePubTopic",_iotMessagePubTopic);
  n.getParam("SourceID",_sourceID);
  n.getParam("TargetID",_targetID);
  n.getParam("DtObjectID",_dtObjectID);
  n.getParam("GlobalPositionMessageSubTopic",_globalPosMsgSubTopic);
  n.getParam("LocalPositionMessageSubTopic",_localPosMsgSubTopic);
  n.getParam("LocalVelocityMessageSubTopic",_localVelMsgSubTopic);
  n.getParam("UavStateMessageSubTopic",_uavStateMsgSubTopic);
  n.getParam("MessagePubFrequency",_msgPubFrequency);
  n.getParam("IotMessageSubTopic",_iotMessageSubTopic);

  n.getParam("cloud_server_local_position_pub_topic",_cloud_server_local_position_pub_topic);
  n.getParam("cloud_server_global_position_pub_topic",_cloud_server_global_position_pub_topic);
  n.getParam("cloud_server_velocity_pub_topic",_cloud_server_velocity_pub_topic);
  n.getParam("cloud_server_control_apply_pub_topic",_cloud_server_control_apply_pub_topic);
  n.getParam("cloud_server_target_cmd_type_pub_topic",_cloud_server_target_cmd_type_pub_topic);

  n.getParam("local_server_local_position_pub_topic",_local_server_local_position_pub_topic);
  n.getParam("local_server_global_position_pub_topic",_local_server_global_position_pub_topic);
  n.getParam("local_server_velocity_pub_topic",_local_server_velocity_pub_topic);
  n.getParam("local_server_control_apply_pub_topic",_local_server_control_apply_pub_topic);
  n.getParam("local_server_target_cmd_type_pub_topic",_local_server_target_cmd_type_pub_topic);

  n.getParam("vr_server_local_position_pub_topic",_vr_server_local_position_pub_topic);
  n.getParam("vr_server_global_position_pub_topic",_vr_server_global_position_pub_topic);
  n.getParam("vr_server_velocity_pub_topic",_vr_server_velocity_pub_topic);
  n.getParam("vr_server_control_apply_pub_topic",_vr_server_control_apply_pub_topic);
  n.getParam("vr_server_target_cmd_type_pub_topic",_vr_server_target_cmd_type_pub_topic);

  n.getParam("dt_object_local_position_pub_topic",_dt_object_local_position_pub_topic);
  n.getParam("dt_object_global_position_pub_topic",_dt_object_global_position_pub_topic);
  n.getParam("dt_object_velocity_pub_topic",_dt_object_velocity_pub_topic);
  n.getParam("dt_object_control_apply_pub_topic",_dt_object_control_apply_pub_topic);
  n.getParam("dt_object_target_cmd_type_pub_topic",_dt_object_target_cmd_type_pub_topic);

  _cloud_server_local_position_pub = n.advertise<geometry_msgs::PoseStamped>(_cloud_server_local_position_pub_topic,1);
  _cloud_server_global_position_pub = n.advertise<mavros_msgs::GlobalPositionTarget>(_cloud_server_global_position_pub_topic,1);
  _cloud_server_velocity_pub = n.advertise<geometry_msgs::TwistStamped>(_cloud_server_velocity_pub_topic,1);
  _cloud_server_control_apply_pub = n.advertise<std_msgs::Bool>(_cloud_server_control_apply_pub_topic,1);
  _cloud_server_target_cmd_type_pub = n.advertise<std_msgs::Int8>(_cloud_server_target_cmd_type_pub_topic,1);

  _local_server_local_position_pub = n.advertise<geometry_msgs::PoseStamped>(_local_server_local_position_pub_topic,1);
  _local_server_global_position_pub = n.advertise<mavros_msgs::GlobalPositionTarget>(_local_server_global_position_pub_topic,1);
  _local_server_velocity_pub = n.advertise<geometry_msgs::TwistStamped>(_local_server_velocity_pub_topic,1);
  _local_server_control_apply_pub = n.advertise<std_msgs::Bool>(_local_server_control_apply_pub_topic,1);
  _local_server_target_cmd_type_pub = n.advertise<std_msgs::Int8>(_local_server_target_cmd_type_pub_topic,1);

  _vr_server_local_position_pub = n.advertise<geometry_msgs::PoseStamped>(_vr_server_local_position_pub_topic,1);
  _vr_server_global_position_pub = n.advertise<mavros_msgs::GlobalPositionTarget>(_vr_server_global_position_pub_topic,1);
  _vr_server_velocity_pub = n.advertise<geometry_msgs::TwistStamped>(_vr_server_velocity_pub_topic,1);
  _vr_server_control_apply_pub = n.advertise<std_msgs::Bool>(_vr_server_control_apply_pub_topic,1);
  _vr_server_target_cmd_type_pub = n.advertise<std_msgs::Int8>(_vr_server_target_cmd_type_pub_topic,1);

  _dt_object_local_position_pub = n.advertise<geometry_msgs::PoseStamped>(_dt_object_local_position_pub_topic,1);
  _dt_object_global_position_pub = n.advertise<mavros_msgs::GlobalPositionTarget>(_dt_object_global_position_pub_topic,1);
  _dt_object_velocity_pub = n.advertise<geometry_msgs::TwistStamped>(_dt_object_velocity_pub_topic,1);
  _dt_object_control_apply_pub = n.advertise<std_msgs::Bool>(_dt_object_control_apply_pub_topic,1);
  _dt_object_target_cmd_type_pub = n.advertise<std_msgs::Int8>(_dt_object_target_cmd_type_pub_topic,1);

  _iotMessagePub = n.advertise<dt_message_package::CloudMessage>(_iotMessagePubTopic,1);
  _iotMessageSub = n.subscribe(_iotMessageSubTopic,1,&dt_message_packing_unpacking::iotMessageSubCallback,this);
  _gloPosMsgSub = n.subscribe(_globalPosMsgSubTopic,1,&dt_message_packing_unpacking::globalPosMsgSubCallback,this);
  _localPosMsgSub = n.subscribe(_localPosMsgSubTopic,1,&dt_message_packing_unpacking::localPosMsgSubCallback,this);
  _localVelMsgSub = n.subscribe(_localVelMsgSubTopic,1,&dt_message_packing_unpacking::localVelocitySubCallback,this);
  _uavStateMsgSub = n.subscribe(_uavStateMsgSubTopic,1,&dt_message_packing_unpacking::uavStateSubCallback,this);
  send_time = 0;
}

void dt_message_packing_unpacking::uavStateSubCallback(const mavros_msgs::StateConstPtr &msg)
{
  //if(send_time==0)
  {
    dt_message_package::CloudMessage cloudMsgPub;
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
    cloudMsgPub.TargetID = _dtObjectID;
    _iotMessagePub.publish(cloudMsgPub);
    cloudMsgPub.TargetID = Local_Server;
    _iotMessagePub.publish(cloudMsgPub);
    cloudMsgPub.TargetID = Cloud_Server;
    _iotMessagePub.publish(cloudMsgPub);
    cloudMsgPub.TargetID = Vr_Server;
    _iotMessagePub.publish(cloudMsgPub);
  }
}

void dt_message_packing_unpacking::globalPosMsgSubCallback(const sensor_msgs::NavSatFix::ConstPtr &msg)
{
  dt_message_package::CloudMessage cloudMsgPub;
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

  cloudMsgPub.TargetID = _dtObjectID;
  _iotMessagePub.publish(cloudMsgPub);
  cloudMsgPub.TargetID = Local_Server;
  _iotMessagePub.publish(cloudMsgPub);
  cloudMsgPub.TargetID = Cloud_Server;
  _iotMessagePub.publish(cloudMsgPub);
  cloudMsgPub.TargetID = Vr_Server;
  _iotMessagePub.publish(cloudMsgPub);
}

void dt_message_packing_unpacking::localPosMsgSubCallback(const geometry_msgs::PoseStamped::ConstPtr &msg)
{
  dt_message_package::CloudMessage cloudMsgPub;
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

  cloudMsgPub.TargetID = _dtObjectID;
  _iotMessagePub.publish(cloudMsgPub);
  cloudMsgPub.TargetID = Local_Server;
  _iotMessagePub.publish(cloudMsgPub);
  cloudMsgPub.TargetID = Cloud_Server;
  _iotMessagePub.publish(cloudMsgPub);
  cloudMsgPub.TargetID = Vr_Server;
  _iotMessagePub.publish(cloudMsgPub);
}

void dt_message_packing_unpacking::localVelocitySubCallback(const geometry_msgs::TwistStamped::ConstPtr &msg)
{
  dt_message_package::CloudMessage cloudMsgPub;
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

  cloudMsgPub.TargetID = _dtObjectID;
  _iotMessagePub.publish(cloudMsgPub);
  cloudMsgPub.TargetID = Local_Server;
  _iotMessagePub.publish(cloudMsgPub);
  cloudMsgPub.TargetID = Cloud_Server;
  _iotMessagePub.publish(cloudMsgPub);
  cloudMsgPub.TargetID = Vr_Server;
  _iotMessagePub.publish(cloudMsgPub);
}

void dt_message_packing_unpacking::iotMessageSubCallback(const dt_message_package::CloudMessageConstPtr &msg)
{

  switch (msg.get()->MessageID) {
  case TargetLocalPositionMsgID:
  {
    TargetLocalPositionMsg local_position_msg;
    bool is_load = x2struct::X::loadjson(msg.get()->MessageData,local_position_msg,false);
    if(is_load)
    {
      geometry_msgs::PoseStamped refPoseMsg;
      refPoseMsg.header.stamp = ros::Time::now();
      refPoseMsg.pose.orientation.x = local_position_msg.rotation_x;
      refPoseMsg.pose.orientation.y = local_position_msg.rotation_y;
      refPoseMsg.pose.orientation.z = local_position_msg.rotation_z;
      refPoseMsg.pose.orientation.w = local_position_msg.rotation_w;
      refPoseMsg.pose.position.x    = local_position_msg.position_x;
      refPoseMsg.pose.position.y    = local_position_msg.position_y;
      refPoseMsg.pose.position.z    = local_position_msg.position_z;
      if(msg.get()->MessageID ==_dtObjectID)
      {
        refPoseMsg.header.frame_id = "dt_object";
        _dt_object_local_position_pub.publish(refPoseMsg);
      }
      else
      {
        switch (msg.get()->SourceID)
        {
        case Local_Server:
        {
          refPoseMsg.header.frame_id = "local_server";
          _local_server_local_position_pub.publish(refPoseMsg);
        }
          break;
        case Vr_Server:
        {
          refPoseMsg.header.frame_id = "vr_server";
          _vr_server_local_position_pub.publish(refPoseMsg);
        }
          break;
        case Cloud_Server:
        {
          refPoseMsg.header.frame_id = "cloud_server";
          _cloud_server_local_position_pub.publish(refPoseMsg);
        }
          break;
        default:
          break;
        }
      }
    }
  }
    break;
  case TargetGlobalPositionMsgID:
  {
    TargetGlobalPositionMsg global_position_msg;
    bool is_load = x2struct::X::loadjson(msg.get()->MessageData,global_position_msg,false);
    if(is_load)
    {
      mavros_msgs::GlobalPositionTarget ros_global_position_msg;

      ros_global_position_msg.header.stamp = ros::Time::now();
      ros_global_position_msg.altitude = global_position_msg.altitude;
      ros_global_position_msg.latitude = global_position_msg.latitude;
      ros_global_position_msg.longitude = global_position_msg.longitude;
      if(msg.get()->MessageID ==_dtObjectID)
      {
        ros_global_position_msg.header.frame_id = "dt_object";
        _dt_object_global_position_pub.publish(ros_global_position_msg);
      }
      else
      {
        switch (msg.get()->SourceID)
        {
        case Local_Server:
        {
          ros_global_position_msg.header.frame_id = "global_server";
          _local_server_global_position_pub.publish(ros_global_position_msg);
        }
          break;
        case Vr_Server:
        {
          ros_global_position_msg.header.frame_id = "vr_server";
          _vr_server_global_position_pub.publish(ros_global_position_msg);
        }
          break;
        case Cloud_Server:
        {
          ros_global_position_msg.header.frame_id = "cloud_server";
          _cloud_server_global_position_pub.publish(ros_global_position_msg);
        }
          break;
        default:
          break;
        }
      }
    }
  }
    break;

  case TargetVelocityMsgID:
  {
    TargetVelocityMsg velocity_msg;
    bool is_load = x2struct::X::loadjson(msg.get()->MessageData,velocity_msg,false);
    if(is_load)
    {
      geometry_msgs::TwistStamped ros_velocity_msg;

      ros_velocity_msg.header.stamp = ros::Time::now();
      ros_velocity_msg.twist.linear.x = velocity_msg.linear_velocity_x;
      ros_velocity_msg.twist.linear.y = velocity_msg.linear_velocity_y;
      ros_velocity_msg.twist.linear.z = velocity_msg.linear_velocity_z;
      ros_velocity_msg.twist.angular.x = velocity_msg.anger_velocity_x;
      ros_velocity_msg.twist.angular.y = velocity_msg.anger_velocity_y;
      ros_velocity_msg.twist.angular.z = velocity_msg.anger_velocity_z;
      if(msg.get()->MessageID ==_dtObjectID)
      {

        ros_velocity_msg.header.frame_id = "dt_object";
        _dt_object_velocity_pub.publish(ros_velocity_msg);
      }
      else
      {
        switch (msg.get()->SourceID)
        {
        case Local_Server:
        {
          ros_velocity_msg.header.frame_id = "global_server";
          _local_server_velocity_pub.publish(ros_velocity_msg);
        }
          break;
        case Vr_Server:
        {
          ros_velocity_msg.header.frame_id = "vr_server";
          _vr_server_velocity_pub.publish(ros_velocity_msg);
        }
          break;
        case Cloud_Server:
        {
          ros_velocity_msg.header.frame_id = "cloud_server";
          _cloud_server_velocity_pub.publish(ros_velocity_msg);
        }
          break;
        default:
          break;
        }
      }
    }
  }
    break;

  case TargetCmdTypeMsgID:
  {
    TargetCmdTypeMsg cmd_type_msg;
    bool is_load = x2struct::X::loadjson(msg.get()->MessageData,cmd_type_msg,false);
    if(is_load)
    {
      std_msgs::Int8 ros_cmd_type_msg;
      ros_cmd_type_msg.data = cmd_type_msg.type;
      if(msg.get()->MessageID ==_dtObjectID)
      {
        _dt_object_target_cmd_type_pub.publish(ros_cmd_type_msg);
      }
      else
      {
        switch (msg.get()->SourceID)
        {
        case Local_Server:
        {
          _local_server_target_cmd_type_pub.publish(ros_cmd_type_msg);
        }
          break;
        case Vr_Server:
        {
          _vr_server_target_cmd_type_pub.publish(ros_cmd_type_msg);
        }
          break;
        case Cloud_Server:
        {
          _cloud_server_target_cmd_type_pub.publish(ros_cmd_type_msg);
        }
          break;
        default:
          break;
        }
      }
    }
  }
    break;

  case ControlApplyMsgID:
  {
    ControlApplyMsg control_apply_msg;
    bool is_load = x2struct::X::loadjson(msg.get()->MessageData,control_apply_msg,false);
    if(is_load)
    {
      std_msgs::Bool ros_control_apply_msg;
      ros_control_apply_msg.data = control_apply_msg.apply_info;
      if(msg.get()->MessageID ==_dtObjectID)
      {
        _dt_object_control_apply_pub.publish(ros_control_apply_msg);
      }
      else
      {
        switch (msg.get()->SourceID)
        {
        case Local_Server:
        {
          _local_server_control_apply_pub.publish(ros_control_apply_msg);
        }
          break;
        case Vr_Server:
        {
          _vr_server_control_apply_pub.publish(ros_control_apply_msg);
        }
          break;
        case Cloud_Server:
        {
          _cloud_server_control_apply_pub.publish(ros_control_apply_msg);
        }
          break;
        default:
          break;
        }
      }
    }
  }
    break;
  default:
    break;
  }
}



