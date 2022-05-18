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
#include "../include/map_wrapper/cloud_connection.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/time.h>
#include <time.h>
#include <arpa/inet.h>
#include <stdbool.h> /* required for the definition of bool in C99 */
using namespace DTUAVCARS;
#define BUFFER_LENGTH 2041

extern aiot_sysdep_portfile_t g_aiot_sysdep_portfile;

extern const char *ali_ca_cert;
vector<uint8_t> recv_data_uint8_t;
bool is_first_recv = true;

char target_ip[100];

float position[6] = {};
int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
struct sockaddr_in gcAddr;
struct sockaddr_in locAddr;
//struct sockaddr_in fromAddr;
uint8_t buf[BUFFER_LENGTH];
ssize_t recsize;
socklen_t fromlen = sizeof(gcAddr);
int bytes_sent;
//mavlink_message_t msg;
uint16_t len;

int32_t state_logcb(int32_t code, char *message)
{
  printf("%s", message);
  return 0;
}

void mqtt_event_handler(void *handle, const aiot_mqtt_event_t *event, void *userdata)
{
  switch (event->type) {
  case AIOT_MQTTEVT_CONNECT: {
    printf("AIOT_MQTTEVT_CONNECT\n");
  }
    break;


  case AIOT_MQTTEVT_RECONNECT: {
    printf("AIOT_MQTTEVT_RECONNECT\n");

  }
    break;


  case AIOT_MQTTEVT_DISCONNECT: {
    char *cause = const_cast<char *>((event->data.disconnect == AIOT_MQTTDISCONNEVT_NETWORK_DISCONNECT) ? ("network disconnect") :("heartbeat disconnect"));
    printf("AIOT_MQTTEVT_DISCONNECT: %s\n", cause);
  }
    break;

  default: {

  }
  }
}


void mqtt_default_recv_handler(void *handle, const aiot_mqtt_recv_t *packet, void *userdata)
{
  switch (packet->type) {
  case AIOT_MQTTRECV_HEARTBEAT_RESPONSE: {
    //  printf("heartbeat response\n");

  }
    break;

  case AIOT_MQTTRECV_SUB_ACK: {
    //   printf("suback, res: -0x%04X, packet id: %d, max qos: %d\n",
    //         -packet->data.sub_ack.res, packet->data.sub_ack.packet_id, packet->data.sub_ack.max_qos);

  }
    break;
  case AIOT_MQTTRECV_PUB: {
    printf("pub, qos: %d, topic: %.*s\n", packet->data.pub.qos, packet->data.pub.topic_len, packet->data.pub.topic);
    printf("pub, payload: %c\n", packet->data.pub.payload_len, packet->data.pub.payload);
    mavlink_message_t msg;
    mavlink_status_t status1;
    int deal_id =0;
    if(is_first_recv)
    {
      for(int i=0;i<packet->data.pub.payload_len;i++)
      {
        recv_data_uint8_t.push_back(packet->data.pub.payload[i]);
      }
      is_first_recv = false;
    }
    else
    {
      for(int i=0;i<packet->data.pub.payload_len;i++)
      {
        recv_data_uint8_t.push_back(packet->data.pub.payload[i]);
      }    
      for(int i=0;i<recv_data_uint8_t.size();i++)
      {
        if (mavlink_parse_char(MAVLINK_COMM_0, recv_data_uint8_t.at(i), &msg, &status1))
        {
          deal_id = i;
         // cout<<"true"<<endl;
         // printf("\nReceived packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d\n", msg1.sysid, msg1.compid, msg1.len, msg1.msgid);
          mavros_msgs::Mavlink recv_msg;
          recv_msg.checksum     = msg.checksum;
          recv_msg.compid       = msg.compid;
          recv_msg.msgid        = msg.msgid;
          recv_msg.len          = msg.len;
          recv_msg.sysid        = msg.sysid;
          recv_msg.magic        = msg.magic;
          recv_msg.header.stamp = ros::Time::now();
          recv_msg.payload64.resize(msg.len);
          for(int i= 0; i<msg.len; i++)
          {
            recv_msg.payload64.at(i) = msg.payload64[i];
          }
          recv_msg.seq          = msg.seq;
          iot_msg_pub.publish(recv_msg);
        }
      }
      for(int i =0; i<deal_id;i++)
      {
        recv_data_uint8_t.pop_back();
      }
    }
  }
    break;

  case AIOT_MQTTRECV_PUB_ACK: {
    //   printf("puback, packet id: %d\n", packet->data.pub_ack.packet_id)
  }
    break;

  default: {

  }
  }
}


void *mqtt_process_thread(void *args)
{
  int32_t res = STATE_SUCCESS;

  while (ros::ok()) {
    res = aiot_mqtt_process(args);
    if (res == STATE_USER_INPUT_EXEC_DISABLED) {
      break;
    }
    sleep(1);
  }
  return NULL;
}

void *mqtt_recv_thread(void *args)
{
  int32_t res = STATE_SUCCESS;

  while (ros::ok()) {
    res = aiot_mqtt_recv(args);
    if (res < STATE_SUCCESS) {
      if (res == STATE_USER_INPUT_EXEC_DISABLED) {
        break;
      }
      sleep(1);
    }
  }
  return NULL;
}
void iot_msg_cb(const mavros_msgs::MavlinkConstPtr& msg)
{
  mavlink_message_t send_msg;
  send_msg.checksum = msg.get()->checksum;
  send_msg.compid   = msg.get()->compid;
  send_msg.len      = msg.get()->len;
  send_msg.magic    = msg.get()->magic;
  send_msg.msgid    = msg.get()->msgid;
  send_msg.payload64[msg.get()->len];
  for(int i = 0; i<msg.get()->len;i++)
  {
    send_msg.payload64[i] = msg.get()->payload64.at(i);
  }
  send_msg.seq      = msg.get()->seq;
  send_msg.sysid    = msg.get()->sysid;
  uint8_t buf[BUFFER_LENGTH];
  uint16_t len = mavlink_msg_to_send_buffer(buf, &send_msg);
  uint8_t send_buf[len];
  mavlink_msg_to_send_buffer(send_buf,&send_msg);
  int res = 0;
    res = aiot_mqtt_pub(mqtt_handle, iot_pub_topic, send_buf,len, 0);
    if (res < 0) {
      printf("aiot_mqtt_pub iot_msg failed, res: -0x%04X\n", -res);
    }
}

/*
void *iot_state_thread_fun(void *args)
{
   ros::Rate rate(10.0);
   while (ros::ok())
   {
     message_package::CloudStateMessage state_msg;
     state_msg.connection_state = iot_connection_state;
     state_msg.work_state = iot_work_state;
     iot_state_pub.publish(state_msg);
    rate.sleep();
   }



}
*/

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "iot_conneection");
  ros::NodeHandle nh("~");
  string str_key  = "a1xrDbYuLKC";
  nh.getParam("product_key",str_key);
  product_key = (char *)str_key.c_str();
  string str_name = "UAV-5G-Server-1";
  nh.getParam("device_name",str_name);
  device_name = (char *)str_name.c_str();
  string str_sec = "f2fe6fce2283c89ec49c84ad4d0ad148";
  nh.getParam("device_secret",str_sec);
  device_secret = (char *)str_sec.c_str();
  string str_pub = "/a1xrDbYuLKC/UAV-5G-Server-1/user/UAV_Server_1_Pub";
  nh.getParam("iot_pub_topic",str_pub);
  iot_pub_topic = (char *)str_pub.c_str();
  string str_sub = "/a1xrDbYuLKC/UAV-5G-Server-1/user/UAV_Server_1_Sub";
  nh.getParam("iot_sub_topic",str_sub);
  iot_sub_topic = (char *)str_sub.c_str();

  nh.getParam("ros_sub_topic",ros_sub_topic);
  nh.getParam("ros_pub_topic",ros_pub_topic);
  nh.getParam("object_name",object_name);
  nh.getParam("ros_iot_state_pub_topic",ros_iot_state_pub_topic);
  iot_msg_pub = nh.advertise<mavros_msgs::Mavlink>(ros_pub_topic, 100);
  //iot_state_pub = nh.advertise<message_package::CloudStateMessage>(ros_iot_state_pub_topic,1);
  iot_msg_sub = nh.subscribe(ros_sub_topic, 100, iot_msg_cb);
  iot_connection_state = "off";
  iot_work_state = "error";
  /* 配置SDK的底层依赖 */
  aiot_sysdep_set_portfile(&g_aiot_sysdep_portfile);
  /* 配置SDK的日志输出 */
  aiot_state_set_logcb(state_logcb);

  /* 创建SDK的安全凭据, 用于建立TLS连接 */
  memset(&cred, 0, sizeof(aiot_sysdep_network_cred_t));
  cred.option = AIOT_SYSDEP_NETWORK_CRED_SVRCERT_CA;  /* 使用RSA证书校验MQTT服务端 */
  cred.max_tls_fragment = 16384; /* 最大的分片长度为16K, 其它可选值还有4K, 2K, 1K, 0.5K */
  cred.sni_enabled = 1;                               /* TLS建连时, 支持Server Name Indicator */
  cred.x509_server_cert = ali_ca_cert;                 /* 用来验证MQTT服务端的RSA根证书 */
  cred.x509_server_cert_len = strlen(ali_ca_cert);     /* 用来验证MQTT服务端的RSA根证书长度 */

  /* 创建1个MQTT客户端实例并内部初始化默认参数 */
  mqtt_handle = aiot_mqtt_init();
  if (mqtt_handle == NULL) {
    printf("aiot_mqtt_init failed\n");
    return -1;
  }

  /* TODO: 如果以下代码不被注释, 则例程会用TCP而不是TLS连接云平台 */
  /*
    {
        memset(&cred, 0, sizeof(aiot_sysdep_network_cred_t));
        cred.option = AIOT_SYSDEP_NETWORK_CRED_NONE;
    }
    */
  if (1 == public_instance) {
    snprintf(host, 100, "%s.%s", product_key, url);
  } else {
    snprintf(host, 100, "%s", url);
  }

  /* 配置MQTT服务器地址 */
  aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_HOST, (void *)host);
  /* 配置MQTT服务器端口 */
  aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_PORT, (void *)&port);
  /* 配置设备productKey */
  aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_PRODUCT_KEY, (void *)product_key);
  /* 配置设备deviceName */
  aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_DEVICE_NAME, (void *)device_name);
  /* 配置设备deviceSecret */
  aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_DEVICE_SECRET, (void *)device_secret);
  /* 配置网络连接的安全凭据, 上面已经创建好了 */
  aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_NETWORK_CRED, (void *)&cred);
  /* 配置MQTT默认消息接收回调函数 */
  aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_RECV_HANDLER, (void *)mqtt_default_recv_handler);
  /* 配置MQTT事件回调函数 */
  aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_EVENT_HANDLER, (void *)mqtt_event_handler);

  /* 与服务器建立MQTT连接 */
  res = aiot_mqtt_connect(mqtt_handle);
  iot_connection_state = "on";
  if (res < STATE_SUCCESS) {
    /* 尝试建立连接失败, 销毁MQTT实例, 回收资源 */
    aiot_mqtt_deinit(&mqtt_handle);
    iot_connection_state = "off";
    printf("aiot_mqtt_connect failed: -0x%04X\n", -res);
    return -1;
  }

  /* MQTT 订阅topic功能示例, 请根据自己的业务需求进行使用 */
  res = aiot_mqtt_sub(mqtt_handle, iot_sub_topic, NULL, 1, NULL);
  iot_work_state = "nomal";
  if (res < 0) {
    printf("aiot_mqtt_sub failed, res: -0x%04X\n", -res);
    iot_work_state = "error";
    return -1;
  }

  char *pub_payload = "{\"MsgID\":0,\"MsgData\":\"{\"UavModel\":0,\"ref_position_x\":1.0,\"ref_position_y\":0.5,\"ref_position_z\":3.0,\"ref_yaw\":0.0}\"}";
  res = aiot_mqtt_pub(mqtt_handle, iot_pub_topic, (uint8_t *)pub_payload, (uint32_t)strlen(pub_payload), 0);

  if (res < 0) {
    printf("aiot_mqtt_sub failed, res: -0x%04X\n", -res);
     iot_work_state = "error";
    return -1;
  }

  res = pthread_create(&g_mqtt_process_thread, NULL, mqtt_process_thread, mqtt_handle);
  if (res < 0) {
    printf("pthread_create demo_mqtt_process_thread failed: %d\n", res);
    iot_work_state = "error";
    return -1;
  }

  res = pthread_create(&g_mqtt_recv_thread, NULL, mqtt_recv_thread, mqtt_handle);
  if (res < 0) {
    printf("pthread_create mqtt_recv_thread failed: %d\n", res);
    iot_work_state = "error";
    return -1;
  }
  // res = pthread_create(&iot_state_thread, NULL, iot_state_thread_fun, mqtt_handle);
  // if (res < 0) {
  //    printf("pthread_create mqtt_recv_thread failed: %d\n", res);
  //    iot_work_state = "error";
  //   return -1;
  //  }
  ros::spin();

  res = aiot_mqtt_disconnect(mqtt_handle);
  if (res < STATE_SUCCESS) {
    aiot_mqtt_deinit(&mqtt_handle);
    printf("aiot_mqtt_disconnect failed: -0x%04X\n", -res);
    return -1;
  }
  res = aiot_mqtt_deinit(&mqtt_handle);
  if (res < STATE_SUCCESS) {
    printf("aiot_mqtt_deinit failed: -0x%04X\n", -res);
    return -1;
  }
  pthread_join(g_mqtt_process_thread, NULL);
  pthread_join(g_mqtt_recv_thread, NULL);
  // pthread_join(iot_state_thread,NULL);
  iot_connection_state = "off";
  iot_work_state = "error";
  return 0;
}
