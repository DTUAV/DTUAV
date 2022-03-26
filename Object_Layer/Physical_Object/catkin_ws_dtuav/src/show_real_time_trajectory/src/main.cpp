#include "ros/ros.h"
#include "../include/show_real_time_trajectory/real_time_trajectory.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "show_trajectory");
  ros::NodeHandle nh;
  real_time_trajectory show_trajectory;
  ros::spin();

  return 0;
}
