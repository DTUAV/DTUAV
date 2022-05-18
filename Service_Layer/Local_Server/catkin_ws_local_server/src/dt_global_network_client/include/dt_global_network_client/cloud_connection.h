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
#ifndef CLOUD_CONNECTION_H
#define CLOUD_CONNECTION_H
#include <iostream>
#include "../src/LinkSDK/core/aiot_state_api.h"
#include "../src/LinkSDK/core/aiot_sysdep_api.h"
#include "../src/LinkSDK/core/aiot_mqtt_api.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ros/ros.h>
#include <x2struct/x2struct.hpp>
#include <cloud_common/define_common.h>
#include "json_data_process.h"
#include <dt_message_package/CloudMessage.h>
#include <dt_message_package/CloudStateMessage.h>
using namespace dtcloud;
using namespace std;
static pthread_t g_mqtt_process_thread;
static pthread_t g_mqtt_recv_thread;
static pthread_t iot_state_thread;
int32_t     res = STATE_SUCCESS;
void       *mqtt_handle = NULL;
int8_t      public_instance = 1;
char       *url = "iot-as-mqtt.cn-shanghai.aliyuncs.com";
char        host[100] = {0};
uint16_t    port = 443;
aiot_sysdep_network_cred_t cred;

char *product_key       = "a1mcqCrCCBy";
char *device_name       = "MainServer";
char *device_secret     = "5776ba4032168e72798de531819278a7";
char *iot_pub_topic     = "pub";
char *iot_sub_topic     = "sub";

string ros_sub_topic = "/sub";
string ros_pub_topic = "/pub";
string ros_iot_state_pub_topic = "/state_pub";
string object_name = "uav";

string iot_connection_state = "off";
string iot_work_state = "error";

ros::Publisher iot_msg_pub;
ros::Publisher iot_state_pub;
ros::Subscriber iot_msg_sub;

#endif // CLOUD_CONNECTION_H
