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
#include "../include/dt_mission/mission_point.h"

mission_point::mission_point()
{
  ros::NodeHandle nh("~");
  XmlRpc::XmlRpcValue ref_state_params;
  nh.param<std::string>("yawl_file_name",_file_name,"ref_uav_state");
  nh.getParam(_file_name, ref_state_params);
  _ref_state_vector.resize(ref_state_params.size());
  _mission_count = _ref_state_vector.size();
  std::cout<<"The All Mission Points Number: "<<_ref_state_vector.size()<<std::endl;
  for(size_t i = 0; i<ref_state_params.size(); ++i)
  {
    _ref_state_vector.at(i).x     = ref_state_params[i]["x"];
    _ref_state_vector.at(i).y    = ref_state_params[i]["y"];
    _ref_state_vector.at(i).z     = ref_state_params[i]["z"];
    _ref_state_vector.at(i).yaw     = ref_state_params[i]["yaw"];
    // std::cout<<ref_state_vector.at(i).x<<std::endl;
  }

  XmlRpc::XmlRpcValue mission_1_ref_state_params;
  nh.param<std::string>("mission_1_yawl_file_name",_mission_1_file_name,"ref_uav_state");
  nh.getParam(_file_name, mission_1_ref_state_params);
  _mission_1_ref_state_vector.resize(mission_1_ref_state_params.size());
  _mission_1_count = _mission_1_ref_state_vector.size();
  std::cout<<"The All Mission Points Number: "<<_mission_1_ref_state_vector.size()<<std::endl;
  for(size_t i = 0; i<ref_state_params.size(); ++i)
  {
   _mission_1_ref_state_vector.at(i).x     = mission_1_ref_state_params[i]["x"];
   _mission_1_ref_state_vector.at(i).y    = mission_1_ref_state_params[i]["y"];
   _mission_1_ref_state_vector.at(i).z     = mission_1_ref_state_params[i]["z"];
   _mission_1_ref_state_vector.at(i).yaw     = mission_1_ref_state_params[i]["yaw"];
    // std::cout<<ref_state_vector.at(i).x<<std::endl;
  }

  XmlRpc::XmlRpcValue mission_2_ref_state_params;
  nh.param<std::string>("mission_2_yawl_file_name",_mission_2_file_name,"ref_uav_state");
  nh.getParam(_file_name, mission_2_ref_state_params);
  _mission_2_ref_state_vector.resize(mission_2_ref_state_params.size());
  _mission_2_count = _mission_2_ref_state_vector.size();
  std::cout<<"The All Mission Points Number: "<<_mission_2_ref_state_vector.size()<<std::endl;
  for(size_t i = 0; i<ref_state_params.size(); ++i)
  {
   _mission_2_ref_state_vector.at(i).x     = mission_2_ref_state_params[i]["x"];
   _mission_2_ref_state_vector.at(i).y    = mission_2_ref_state_params[i]["y"];
   _mission_2_ref_state_vector.at(i).z     = mission_2_ref_state_params[i]["z"];
   _mission_2_ref_state_vector.at(i).yaw     = mission_2_ref_state_params[i]["yaw"];
    // std::cout<<ref_state_vector.at(i).x<<std::endl;
  }

  XmlRpc::XmlRpcValue mission_3_ref_state_params;
  nh.param<std::string>("mission_3_yawl_file_name",_mission_3_file_name,"ref_uav_state");
  nh.getParam(_file_name, mission_3_ref_state_params);
  _mission_3_ref_state_vector.resize(mission_3_ref_state_params.size());
  _mission_3_count = _mission_3_ref_state_vector.size();
  std::cout<<"The All Mission Points Number: "<<_mission_3_ref_state_vector.size()<<std::endl;
  for(size_t i = 0; i<ref_state_params.size(); ++i)
  {
   _mission_3_ref_state_vector.at(i).x     = mission_3_ref_state_params[i]["x"];
   _mission_3_ref_state_vector.at(i).y    = mission_3_ref_state_params[i]["y"];
   _mission_3_ref_state_vector.at(i).z     = mission_3_ref_state_params[i]["z"];
   _mission_3_ref_state_vector.at(i).yaw     = mission_3_ref_state_params[i]["yaw"];
    // std::cout<<ref_state_vector.at(i).x<<std::endl;
  }

  nh.getParam("mission_point_err",_mission_point_err);
  nh.getParam("mission_control_sub_topic",_mission_control_sub_topic);
  nh.getParam("mission_change_type",_mission_change_type);
  nh.getParam("feeback_sub_topic",_feedback_sub_topic);
  nh.getParam("next_mission_point_sub_topic",_next_mission_point_sub_topic);
  nh.getParam("mission_point_pub_topic",_mission_point_pub_topic);
  nh.getParam("circle_run",_is_circle_run);

  nh.getParam("local_machine_local_position_pub_topic",_local_machine_local_position_pub_topic);
  nh.getParam("local_machine_global_position_pub_topic",_local_machine_global_position_pub_topic);
  nh.getParam("local_machine_velocity_pub_topic",_local_machine_velocity_pub_topic);
  nh.getParam("local_machine_control_apply_pub_topic",_local_machine_control_apply_pub_topic);
  nh.getParam("local_machine_target_cmd_type_pub_topic",_local_machine_target_cmd_type_pub_topic);

  _is_mission = false;
  _is_first_run = true;
  _is_mission_change = false;
  _curr_mission_id = 0;
  _init_x = _ref_state_vector.at(0).x;
  _init_y = _ref_state_vector.at(0).y;
  _init_z = _ref_state_vector.at(0).z;

  _ref_point_pub = nh.advertise<geometry_msgs::PoseStamped>(_mission_point_pub_topic,1);
  _feedback_point_sub = nh.subscribe(_feedback_sub_topic, 1, &mission_point::feedback_sub_cb,this);
  _mission_control_sub = nh.subscribe(_mission_control_sub_topic,1,&mission_point::mission_control_cb,this);
  _mission_change_sub = nh.subscribe(_next_mission_point_sub_topic,1,&mission_point::next_mission_point_cb,this);


  _local_machine_local_position_pub = nh.advertise<geometry_msgs::PoseStamped>(_local_machine_local_position_pub_topic,1);
  _local_machine_global_position_pub = nh.advertise<mavros_msgs::GlobalPositionTarget>(_local_machine_global_position_pub_topic,1);
  _local_machine_velocity_pub = nh.advertise<geometry_msgs::TwistStamped>(_local_machine_velocity_pub_topic,1);
  _local_machine_control_apply_pub = nh.advertise<std_msgs::Bool>(_local_machine_control_apply_pub_topic,1);
  _local_machine_target_cmd_type_pub = nh.advertise<std_msgs::Int8>(_local_machine_target_cmd_type_pub_topic,1);

}

void mission_point::feedback_sub_cb(const geometry_msgs::PoseStampedConstPtr &msg)
{
  if(_is_mission&&_curr_mission_id<_mission_count-1)
  {
    if(_is_first_run)
    {
      _is_first_run = false;
      geometry_msgs::PoseStamped pose_msg;
      pose_msg.pose.position.x = _init_x;
      pose_msg.pose.position.y = _init_y;
      pose_msg.pose.position.z = _init_z;
      _curr_mission_id = 0;
      _ref_point_pub.publish(pose_msg);
      std_msgs::Int8 cmd_type_msg;
      cmd_type_msg.data = 1;
      _local_machine_target_cmd_type_pub.publish(cmd_type_msg);
      _local_machine_local_position_pub.publish(pose_msg);
    }
    else
    {
      if(_mission_change_type == 0)
      {
        if(abs(_ref_state_vector.at(_curr_mission_id).x - msg.get()->pose.position.x)<=_mission_point_err&&
           abs(_ref_state_vector.at(_curr_mission_id).y - msg.get()->pose.position.y)<=_mission_point_err&&
           abs(_ref_state_vector.at(_curr_mission_id).z - msg.get()->pose.position.z)<=_mission_point_err)
        {
          _curr_mission_id ++;
          geometry_msgs::PoseStamped pose_msg;
          pose_msg.pose.position.x = _ref_state_vector.at(_curr_mission_id).x;
          pose_msg.pose.position.y = _ref_state_vector.at(_curr_mission_id).y;
          pose_msg.pose.position.z = _ref_state_vector.at(_curr_mission_id).z;

          if(_mission_id == 1)
          {
              pose_msg.pose.position.x = _mission_1_ref_state_vector.at(_curr_mission_id).x;
              pose_msg.pose.position.y = _mission_1_ref_state_vector.at(_curr_mission_id).y;
              pose_msg.pose.position.z = _mission_1_ref_state_vector.at(_curr_mission_id).z;
          }
          else if(_mission_id == 2)
          {
              pose_msg.pose.position.x = _mission_2_ref_state_vector.at(_curr_mission_id).x;
              pose_msg.pose.position.y = _mission_2_ref_state_vector.at(_curr_mission_id).y;
              pose_msg.pose.position.z = _mission_2_ref_state_vector.at(_curr_mission_id).z;
          }
          else if(_mission_id == 3)
          {
              pose_msg.pose.position.x = _mission_3_ref_state_vector.at(_curr_mission_id).x;
              pose_msg.pose.position.y = _mission_3_ref_state_vector.at(_curr_mission_id).y;
              pose_msg.pose.position.z = _mission_3_ref_state_vector.at(_curr_mission_id).z;
          }

          _ref_point_pub.publish(pose_msg);
          std_msgs::Int8 cmd_type_msg;
          cmd_type_msg.data = 1;
          _local_machine_target_cmd_type_pub.publish(cmd_type_msg);
          _local_machine_local_position_pub.publish(pose_msg);

        }
      }
      else
      {
        if(_is_mission_change)
        { _curr_mission_id ++;
          geometry_msgs::PoseStamped pose_msg;
          pose_msg.pose.position.x = _ref_state_vector.at(_curr_mission_id).x;
          pose_msg.pose.position.y = _ref_state_vector.at(_curr_mission_id).y;
          pose_msg.pose.position.z = _ref_state_vector.at(_curr_mission_id).z;

          if(_mission_id == 1)
          {
              pose_msg.pose.position.x = _mission_1_ref_state_vector.at(_curr_mission_id).x;
              pose_msg.pose.position.y = _mission_1_ref_state_vector.at(_curr_mission_id).y;
              pose_msg.pose.position.z = _mission_1_ref_state_vector.at(_curr_mission_id).z;
          }
          else if(_mission_id == 2)
          {
              pose_msg.pose.position.x = _mission_2_ref_state_vector.at(_curr_mission_id).x;
              pose_msg.pose.position.y = _mission_2_ref_state_vector.at(_curr_mission_id).y;
              pose_msg.pose.position.z = _mission_2_ref_state_vector.at(_curr_mission_id).z;
          }
          else if(_mission_id == 3)
          {
              pose_msg.pose.position.x = _mission_3_ref_state_vector.at(_curr_mission_id).x;
              pose_msg.pose.position.y = _mission_3_ref_state_vector.at(_curr_mission_id).y;
              pose_msg.pose.position.z = _mission_3_ref_state_vector.at(_curr_mission_id).z;
          }


          _ref_point_pub.publish(pose_msg);
          std_msgs::Int8 cmd_type_msg;
          cmd_type_msg.data = 1;
          _local_machine_target_cmd_type_pub.publish(cmd_type_msg);
          _local_machine_local_position_pub.publish(pose_msg);
          _is_mission_change = false;
        }
      }
    }
  }
  else
  {
    if(_curr_mission_id == _mission_count-1)
    {
     if(_is_circle_run == 1)
     {
       _curr_mission_id = 0;
     }
    }
  }
}

void mission_point::next_mission_point_cb(const std_msgs::BoolConstPtr &msg)
{
  _is_mission_change = msg.get()->data;
}

void mission_point::mission_control_cb(const dt_message_package::mission_msgConstPtr& msg)
{
  _is_mission = msg.get()->mission_state;
  _mission_id = msg.get()->mission_id;
  std_msgs::Bool start_msg;
  start_msg.data = _is_mission;
  _local_machine_control_apply_pub.publish(start_msg);
  if(_mission_id == 1)
  {
      _init_x = _mission_1_ref_state_vector.at(0).x;
      _init_y = _mission_1_ref_state_vector.at(0).y;
      _init_z = _mission_1_ref_state_vector.at(0).z;
  }
  else if(_mission_id == 2)
  {
      _init_x = _mission_2_ref_state_vector.at(0).x;
      _init_y = _mission_2_ref_state_vector.at(0).y;
      _init_z = _mission_2_ref_state_vector.at(0).z;
  }
  else if(_mission_id == 3)
  {
      _init_x = _mission_3_ref_state_vector.at(0).x;
      _init_y = _mission_3_ref_state_vector.at(0).y;
      _init_z = _mission_3_ref_state_vector.at(0).z;
  }
}
