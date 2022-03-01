#include "../include/dt_network_client/dt_network_client.h"

int main(int argc, char **argv)
{
  dt_network_client network(argc,argv);
  ros::spin();
  return 0;
}
