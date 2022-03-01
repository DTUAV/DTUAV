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
