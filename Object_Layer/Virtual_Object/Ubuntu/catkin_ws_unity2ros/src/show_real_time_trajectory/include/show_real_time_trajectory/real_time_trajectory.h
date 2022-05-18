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
#ifndef REAL_TIME_TRAJECTORY_H
#define REAL_TIME_TRAJECTORY_H
#include <ros/ros.h>
#include <ros/console.h>
#include <nav_msgs/Path.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_broadcaster.h>
#include <tf/tf.h>
#include <iostream>
class real_time_trajectory
{
public:
  real_time_trajectory();
  void local_pose_sub_callback(const geometry_msgs::PoseStamped::ConstPtr& msg);

private:
 std::string local_pose_sub_topic;
 std::string path_pub_topic;
 ros::Subscriber local_pose_sub;
 ros::Publisher  path_pub;
 nav_msgs::Path path;

};

#endif // REAL_TIME_TRAJECTORY_H
