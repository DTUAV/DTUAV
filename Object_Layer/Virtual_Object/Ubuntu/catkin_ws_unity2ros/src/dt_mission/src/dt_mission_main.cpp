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
