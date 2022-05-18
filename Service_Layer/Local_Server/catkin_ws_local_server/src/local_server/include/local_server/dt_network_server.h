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
#ifndef DT_NETWORK_SERVER_H
#define DT_NETWORK_SERVER_H
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdlib.h>
#include <pthread.h>
#include <ros/ros.h>
#include <iostream>
#include <cloud_common/socket_data_packet_stamp_msg.h>
#include <cloud_common/define_common.h>
#include <cloud_common/function_common.h>
#include <cloud_common/ros_msg_common.h>
#include <cloud_common/socket_data_common.h>
#include <sys/signal.h>
#include <mutex>
struct clientInfo
{
  int client_fd;
  int target_id;
  int source_id;
};

struct clientPoint
{
    void *client_fd;
    void *server;
    string client_ip;
    void *client_port;
};

class dt_network_server
{
public:
  dt_network_server(int argc, char **argv);
  ~dt_network_server();
  static void *data_recv(void *arg);
  static void *server_connect(void *arg);
  static void *server_connect_msg(void *arg);
  void ros_sub_cb(const cloud_common::socket_data_packet_stamp_msgConstPtr &msg);
private:
  int port;
  int serverfd;
  int clientfd;
  int data_recv_rate_hz;
  pthread_t data_recv_thread;
  pthread_t server_connect_thread;
  pthread_t connect_msg_thread;
  std::string ros_sub_topic;
  std::string ros_pub_topic;

  bool is_recv;
};

#endif // DT_NETWORK_SERVER_H
