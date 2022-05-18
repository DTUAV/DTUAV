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
