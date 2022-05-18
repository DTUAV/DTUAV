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
#ifndef CONTROL_CMD_WRAPPER_H
#define CONTROL_CMD_WRAPPER_H
#include "ros/ros.h"
#include "iostream"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/TwistStamped.h"
#include "mavros_msgs/GlobalPositionTarget.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Int8.h"
#include "pthread.h"

#define local_server 0
#define vr_server 1
#define cloud_server 2
#define local_machine 3
#define dt_object 4
#define no_control_source -1

#define velocity_cmd 0
#define local_position_cmd 1
#define global_position_cmd 2

class control_cmd_wrapper
{
public:
  control_cmd_wrapper();
  void cloud_server_local_position_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg);
  void cloud_server_global_position_sub_cb(const mavros_msgs::GlobalPositionTargetConstPtr& msg);
  void cloud_server_velocity_sub_cb(const geometry_msgs::TwistStampedConstPtr& msg);
  void cloud_server_control_apply_sub_cb(const std_msgs::BoolConstPtr& msg);
  void cloud_server_target_cmd_type_sub_cb(const std_msgs::Int8ConstPtr& msg);

  void local_server_local_position_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg);
  void local_server_global_position_sub_cb(const mavros_msgs::GlobalPositionTargetConstPtr& msg);
  void local_server_velocity_sub_cb(const geometry_msgs::TwistStampedConstPtr& msg);
  void local_server_control_apply_sub_cb(const std_msgs::BoolConstPtr& msg);
  void local_server_target_cmd_type_sub_cb(const std_msgs::Int8ConstPtr& msg);

  void vr_server_local_position_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg);
  void vr_server_global_position_sub_cb(const mavros_msgs::GlobalPositionTargetConstPtr& msg);
  void vr_server_velocity_sub_cb(const geometry_msgs::TwistStampedConstPtr& msg);
  void vr_server_control_apply_sub_cb(const std_msgs::BoolConstPtr& msg);
  void vr_server_target_cmd_type_sub_cb(const std_msgs::Int8ConstPtr& msg);

  void dt_object_local_position_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg);
  void dt_object_global_position_sub_cb(const mavros_msgs::GlobalPositionTargetConstPtr& msg);
  void dt_object_velocity_sub_cb(const geometry_msgs::TwistStampedConstPtr& msg);
  void dt_object_control_apply_sub_cb(const std_msgs::BoolConstPtr& msg);
  void dt_object_target_cmd_type_sub_cb(const std_msgs::Int8ConstPtr& msg);

  void local_machine_local_position_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg);
  void local_machine_global_position_sub_cb(const mavros_msgs::GlobalPositionTargetConstPtr& msg);
  void local_machine_velocity_sub_cb(const geometry_msgs::TwistStampedConstPtr& msg);
  void local_machine_control_apply_sub_cb(const std_msgs::BoolConstPtr& msg);
  void local_machine_target_cmd_type_sub_cb(const std_msgs::Int8ConstPtr& msg);

  static void *run(void *args);
private:

  void update_control_type(int control_type, bool control_hold);

  int _cur_control_type;//0:local_server,1:vr_server,2:cloud_server 3:local machine 4:dt_object,-1: no config --->0-1-2, -1 can to every one
  bool _is_change_control_type;//Only the higher priority automatically relinquishes control, and the lower priority can access.

  bool _is_cloud_server_apply;
  bool _is_local_server_apply;
  bool _is_vr_server_apply;
  bool _is_dt_object_apply;
  bool _is_local_machine_apply;

  int _cloud_server_target_cmd_type;//0:velocity 1:local position 2:global position
  int _local_server_target_cmd_type;//0:velocity 1:local position 2:global position
  int _vr_server_target_cmd_type;//0:velocity 1:local position 2:global position
  int _dt_object_target_cmd_type;//0:velocity 1:local position 2:global position
  int _local_machine_target_cmd_type;//0:velocity 1:local position 2:global position

  ros::Publisher _velocity_cmd_pub;
  ros::Publisher _local_position_cmd_pub;
  ros::Publisher _global_position_cmd_pub;
  ros::Publisher _cur_control_type_pub;
  ros::Publisher _target_cmd_type_pub;

  ros::Subscriber _cloud_server_local_position_sub;
  ros::Subscriber _cloud_server_global_position_sub;
  ros::Subscriber _cloud_server_velocity_sub;
  ros::Subscriber _cloud_server_control_apply_sub;
  ros::Subscriber _cloud_server_target_cmd_type_sub;

  ros::Subscriber _vr_server_local_position_sub;
  ros::Subscriber _vr_server_global_position_sub;
  ros::Subscriber _vr_server_velocity_sub;
  ros::Subscriber _vr_server_control_apply_sub;
  ros::Subscriber _vr_server_target_cmd_type_sub;

  ros::Subscriber _local_server_local_position_sub;
  ros::Subscriber _local_server_global_position_sub;
  ros::Subscriber _local_server_velocity_sub;
  ros::Subscriber _local_server_control_apply_sub;
  ros::Subscriber _local_server_target_cmd_type_sub;

  ros::Subscriber _dt_object_local_position_sub;
  ros::Subscriber _dt_object_global_position_sub;
  ros::Subscriber _dt_object_velocity_sub;
  ros::Subscriber _dt_object_control_apply_sub;
  ros::Subscriber _dt_object_target_cmd_type_sub;

  ros::Subscriber _local_machine_local_position_sub;
  ros::Subscriber _local_machine_global_position_sub;
  ros::Subscriber _local_machine_velocity_sub;
  ros::Subscriber _local_machine_control_apply_sub;
  ros::Subscriber _local_machine_target_cmd_type_sub;

  std::string _velocity_cmd_pub_topic;
  std::string _local_position_cmd_pub_topic;
  std::string _global_position_cmd_pub_topic;
  std::string _cur_control_type_pub_topic;
  std::string _target_cmd_type_pub_topic;


  std::string _cloud_server_local_position_sub_topic;
  std::string _cloud_server_global_position_sub_topic;
  std::string _cloud_server_velocity_sub_topic;
  std::string _cloud_server_control_apply_sub_topic;
  std::string _cloud_server_target_cmd_type_sub_topic;

  std::string _vr_server_local_position_sub_topic;
  std::string _vr_server_global_position_sub_topic;
  std::string _vr_server_velocity_sub_topic;
  std::string _vr_server_control_apply_sub_topic;
  std::string _vr_server_target_cmd_type_sub_topic;

  std::string _local_server_local_position_sub_topic;
  std::string _local_server_global_position_sub_topic;
  std::string _local_server_velocity_sub_topic;
  std::string _local_server_control_apply_sub_topic;
  std::string _local_server_target_cmd_type_sub_topic;

  std::string _dt_object_local_position_sub_topic;
  std::string _dt_object_global_position_sub_topic;
  std::string _dt_object_velocity_sub_topic;
  std::string _dt_object_control_apply_sub_topic;
  std::string _dt_object_target_cmd_type_sub_topic;

  std::string _local_machine_local_position_sub_topic;
  std::string _local_machine_global_position_sub_topic;
  std::string _local_machine_velocity_sub_topic;
  std::string _local_machine_control_apply_sub_topic;
  std::string _local_machine_target_cmd_type_sub_topic;

  pthread_t _run_thread;
  float _control_type_pub_frequency;
};

#endif // CONTROL_CMD_WRAPPER_H
