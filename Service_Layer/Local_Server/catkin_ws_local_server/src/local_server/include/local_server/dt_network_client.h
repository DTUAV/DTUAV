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
#ifndef DT_NETWORK_CLIENT_H
#define DT_NETWORK_CLIENT_H
#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<iostream>
#include <pthread.h>
#include <ros/ros.h>
#include <iostream>
#include <cloud_common/socket_data_packet_stamp_msg.h>
#include <cloud_common/define_common.h>
#include <cloud_common/function_common.h>
#include <cloud_common/ros_msg_common.h>
#include <cloud_common/socket_data_common.h>

class dt_network_client
{
public:
  dt_network_client(int argc, char **argv);
  ~dt_network_client();
  void rosSubMsgCallback(const cloud_common::socket_data_packet_stamp_msg::ConstPtr& msg);
  static void *data_recv(void *arg);
private:
  int _socketFd;
  int _argc;
  char **_argv;
  int _port;
  string _serverIP;
  pthread_t data_recv_thread;
  std::string ros_sub_topic;
  std::string ros_pub_topic;
  int _data_recv_rate_hz;
};

#endif // DT_NETWORK_CLIENT_H
