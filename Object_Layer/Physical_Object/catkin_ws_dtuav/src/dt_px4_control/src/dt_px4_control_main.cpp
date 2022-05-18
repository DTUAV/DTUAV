#include "../include/dt_px4_control/control_cmd_wrapper.h"
#include "../include/dt_px4_control/dt_px4_control.h"

int main(int argc, char *argv[])
{
  ros::init(argc,argv,"dt_px4_control");
  ros::NodeHandle nh;
  control_cmd_wrapper control_cmd_wrapper_node;
  dt_px4_control px4_control_node;
  ros::MultiThreadedSpinner spinner(2); // Use 4 threads
  spinner.spin(); // spin
  return 0;
}
