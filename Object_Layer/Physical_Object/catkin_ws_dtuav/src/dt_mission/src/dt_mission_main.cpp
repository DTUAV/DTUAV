#include "../include/dt_mission/mission_point.h"
#include "../include/dt_mission/generate_path.h"

int main(int argc, char *argv[])
{
  ros::init(argc,argv,"dt_mission");
  ros::NodeHandle nh;
  mission_point mission_point_node;
  generate_path path;
  ros::MultiThreadedSpinner spinner(2); // Use 4 threads
  spinner.spin(); // spin
  return 0;
}
