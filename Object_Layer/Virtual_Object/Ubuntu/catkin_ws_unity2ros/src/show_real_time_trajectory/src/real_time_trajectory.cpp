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
#include "../include/show_real_time_trajectory/real_time_trajectory.h"

real_time_trajectory::real_time_trajectory()
{
  ros::NodeHandle nh("~");
  nh.getParam("local_pose_sub_topic",local_pose_sub_topic);
  nh.getParam("path_pub_topic",path_pub_topic);
  path_pub = nh.advertise<nav_msgs::Path>(path_pub_topic,1);
  local_pose_sub = nh.subscribe(local_pose_sub_topic,1,&real_time_trajectory::local_pose_sub_callback,this);

}
void real_time_trajectory::local_pose_sub_callback(const geometry_msgs::PoseStamped::ConstPtr &msg)
{
  path.header.frame_id = msg.get()->header.frame_id;
  path.header.stamp    = ros::Time::now();
  geometry_msgs::PoseStamped cur_msg;
  cur_msg.header = msg.get()->header;
  cur_msg.pose   = msg.get()->pose;
  path.poses.push_back(cur_msg);
  path_pub.publish(path);
}
