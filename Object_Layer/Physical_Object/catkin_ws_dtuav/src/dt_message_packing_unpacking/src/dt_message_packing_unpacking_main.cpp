#include "../include/dt_message_packing_unpacking/dt_message_packing_unpacking.h"
int main(int argc, char **argv)
{
  ros::init(argc, argv, "dt_message_packing_unpacking");
  ros::NodeHandle nh;
  dt_message_packing_unpacking packing_unpacking_node;
  ros::spin();
  return 0;
}
