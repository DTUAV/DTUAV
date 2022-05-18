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
#ifndef MISSION_POINT_H
#define MISSION_POINT_H
#include <iostream>
#include <vector>
#include <XmlRpc.h>
#include <ros/ros.h>
#include <math.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Bool.h>
#include <geometry_msgs/TwistStamped.h>
#include "mavros_msgs/GlobalPositionTarget.h"
#include "std_msgs/Int8.h"
struct ref_state_stu
{
  double x;
  double y;
  double z;
  double yaw;
};
class mission_point
{
public:
  mission_point();
  void mission_control_cb(const std_msgs::BoolConstPtr& msg);
  void next_mission_point_cb(const std_msgs::BoolConstPtr& msg);
  void feedback_sub_cb(const geometry_msgs::PoseStampedConstPtr& msg);
private:
  std::string _mission_control_sub_topic;//Start Or Stop This Mission

  std::string _feedback_sub_topic;//The Current Position Of Object
  std::string _mission_point_pub_topic;//The Target Mission Position
  std::string _next_mission_point_sub_topic;//Change The Mission Position By Topic

  std::string _file_name;

  int _mission_change_type;//0:Auto Change By the error of target and current position. 1:Change By Other By Topic
  int _is_circle_run;//The Flag For Circle Mission:0:Not,1:Yes

  bool _is_mission;//The Flag For the Mission Running
  bool _is_first_run;//

  bool _is_mission_change;//The Flag For Change Mission Point

  int _curr_mission_id;//The Current ID of Mission Point
  float _mission_point_err;//The Error of Auto Change
  int _mission_count;//The Number of all Mission Points

  float _init_x;//The Init Position X
  float _init_y;//The Init Position Y
  float _init_z;//The Init Position Z

  ros::Publisher _ref_point_pub;
  ros::Subscriber _feedback_point_sub;
  ros::Subscriber _mission_control_sub;
  ros::Subscriber _mission_change_sub;


  std::string _local_machine_local_position_pub_topic;
  std::string _local_machine_global_position_pub_topic;
  std::string _local_machine_velocity_pub_topic;
  std::string _local_machine_control_apply_pub_topic;
  std::string _local_machine_target_cmd_type_pub_topic;

  ros::Publisher _local_machine_local_position_pub;
  ros::Publisher _local_machine_global_position_pub;
  ros::Publisher _local_machine_velocity_pub;
  ros::Publisher _local_machine_control_apply_pub;
  ros::Publisher _local_machine_target_cmd_type_pub;


  std::vector<ref_state_stu> _ref_state_vector;
};

#endif // MISSION_POINT_H
