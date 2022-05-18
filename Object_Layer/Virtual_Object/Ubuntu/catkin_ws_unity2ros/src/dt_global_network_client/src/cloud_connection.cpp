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
#include "../include/dt_global_network_client/cloud_connection.h"
extern aiot_sysdep_portfile_t g_aiot_sysdep_portfile;
extern const char *ali_ca_cert;
void iot_recv_process(string msg)
{
  msg = CheckRecvData(msg);
  if(msg != "")
  {
    bool isjson;
    if(isjson = IsJsonData(msg) == true)
    {
      DTUAV::IotMessage iot_msg;
      bool is_load = x2struct::X::loadjson(msg,iot_msg,false);
      if(is_load)
      {
        dt_message_package::CloudMessage ros_iot_msg;

        ros_iot_msg.TargetID = iot_msg.TargetID;
        ros_iot_msg.SourceID = iot_msg.SourceID;
        ros_iot_msg.MessageData = iot_msg.MessageData;
        ros_iot_msg.MessageID = iot_msg.MessageID;
        ros_iot_msg.TimeStamp = iot_msg.TimeStamp;
        iot_msg_pub.publish(ros_iot_msg);
      }
    }
  }
}
void iot_msg_cb(const dt_message_package::CloudMessage::ConstPtr& msg)
{
  DTUAV::IotMessage iot_msg;
  iot_msg.MessageData = msg.get()->MessageData;
  iot_msg.MessageID = msg.get()->MessageID;
  iot_msg.SourceID = msg.get()->SourceID;
  iot_msg.TargetID = msg.get()->TargetID;
  iot_msg.TimeStamp = msg.get()->TimeStamp;
  string iot_msg_json = x2struct::X::tojson(iot_msg);
  char *pub_payload =(char *)iot_msg_json.c_str();
  int res = 0;
  res = aiot_mqtt_pub(mqtt_handle, iot_pub_topic, (uint8_t *)pub_payload, (uint32_t)strlen(pub_payload), 0);
  if (res < 0)
  {
    printf("aiot_mqtt_pub iot_msg failed, res: -0x%04X\n", -res);
    iot_work_state = "error";
  }
  else
  {
    iot_work_state = "nomal";
  }
}
int32_t state_logcb(int32_t code, char *message)
{
  printf("%s", message);
  return 0;
}
void mqtt_event_handler(void *handle, const aiot_mqtt_event_t *event, void *userdata)
{
  switch (event->type) {
  case AIOT_MQTTEVT_CONNECT:
  {
    printf("AIOT_MQTTEVT_CONNECT\n");
  }
    break;

  case AIOT_MQTTEVT_RECONNECT:
  {
    printf("AIOT_MQTTEVT_RECONNECT\n");
  }
    break;
  case AIOT_MQTTEVT_DISCONNECT:
  {
    char *cause = const_cast<char *>((event->data.disconnect == AIOT_MQTTDISCONNEVT_NETWORK_DISCONNECT) ? ("network disconnect") :
                                                                                                          ("heartbeat disconnect"));
    printf("AIOT_MQTTEVT_DISCONNECT: %s\n", cause);
  }
    break;

  default:
  {

  }
  }
}
void mqtt_default_recv_handler(void *handle, const aiot_mqtt_recv_t *packet, void *userdata)
{
  switch (packet->type)
  {
  case AIOT_MQTTRECV_HEARTBEAT_RESPONSE:
  {
    //  printf("heartbeat response\n");
  }
    break;

  case AIOT_MQTTRECV_SUB_ACK:
  {
    //   printf("suback, res: -0x%04X, packet id: %d, max qos: %d\n",
    //         -packet->data.sub_ack.res, packet->data.sub_ack.packet_id, packet->data.sub_ack.max_qos);
  }
    break;

  case AIOT_MQTTRECV_PUB:
  {
    // printf("pub, qos: %d, topic: %.*s\n", packet->data.pub.qos, packet->data.pub.topic_len, packet->data.pub.topic);
    //  printf("pub, payload: %.*s\n", packet->data.pub.payload_len, packet->data.pub.payload);
    string msg((char *)packet->data.pub.payload);
    iot_recv_process(msg);
  }
    break;

  case AIOT_MQTTRECV_PUB_ACK:
  {
    //   printf("puback, packet id: %d\n", packet->data.pub_ack.packet_id);
  }
    break;

  default:
  {

  }
  }
}
void *mqtt_process_thread(void *args)
{
  int32_t res = STATE_SUCCESS;

  while (ros::ok())
  {
    res = aiot_mqtt_process(args);
    if (res == STATE_USER_INPUT_EXEC_DISABLED)
    {
      break;
    }
    sleep(1);
  }
  return NULL;
}
void *mqtt_recv_thread(void *args)
{
  int32_t res = STATE_SUCCESS;

  while (ros::ok())
  {
    res = aiot_mqtt_recv(args);
    if (res < STATE_SUCCESS)
    {
      if (res == STATE_USER_INPUT_EXEC_DISABLED)
      {
        break;
      }
      sleep(1);
    }
  }
  return NULL;
}
void *iot_state_thread_fun(void *args)
{
  ros::Rate rate(10.0);
  while (ros::ok())
  {
    dt_message_package::CloudStateMessage state_msg;
    state_msg.connection_state = iot_connection_state;
    state_msg.work_state = iot_work_state;
    iot_state_pub.publish(state_msg);
    rate.sleep();
  }
}

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "iot_conneection");
  ros::NodeHandle nh("~");
  string str_key  = "product_key";
  nh.getParam("product_key",str_key);
  product_key = (char *)str_key.c_str();
  string str_name = "device_name";
  nh.getParam("device_name",str_name);
  device_name = (char *)str_name.c_str();
  string str_sec = "device_secret";
  nh.getParam("device_secret",str_sec);
  device_secret = (char *)str_sec.c_str();
  string str_pub = "iot_pub_topic";
  nh.getParam("iot_pub_topic",str_pub);
  iot_pub_topic = (char *)str_pub.c_str();
  string str_sub = "iot_sub_topic";
  nh.getParam("iot_sub_topic",str_sub);
  iot_sub_topic = (char *)str_sub.c_str();
  nh.getParam("ros_sub_topic",ros_sub_topic);
  nh.getParam("ros_pub_topic",ros_pub_topic);
  nh.getParam("object_name",object_name);
  nh.getParam("ros_iot_state_pub_topic",ros_iot_state_pub_topic);
  iot_msg_pub = nh.advertise<dt_message_package::CloudMessage>(ros_pub_topic, 10);
  iot_state_pub = nh.advertise<dt_message_package::CloudStateMessage>(ros_iot_state_pub_topic,1);
  iot_msg_sub = nh.subscribe(ros_sub_topic, 1, iot_msg_cb);
  iot_connection_state = "off";
  iot_work_state = "error";
  aiot_sysdep_set_portfile(&g_aiot_sysdep_portfile);
  aiot_state_set_logcb(state_logcb);
  memset(&cred, 0, sizeof(aiot_sysdep_network_cred_t));
  cred.option = AIOT_SYSDEP_NETWORK_CRED_SVRCERT_CA;
  cred.max_tls_fragment = 16384;
  cred.sni_enabled = 1;
  cred.x509_server_cert = ali_ca_cert;
  cred.x509_server_cert_len = strlen(ali_ca_cert);
  mqtt_handle = aiot_mqtt_init();
  if (mqtt_handle == NULL) {
    printf("aiot_mqtt_init failed\n");
    return -1;
  }
  if (1 == public_instance) {
    snprintf(host, 100, "%s.%s", product_key, url);
  } else {
    snprintf(host, 100, "%s", url);
  }
  aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_HOST, (void *)host);
  aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_PORT, (void *)&port);
  aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_PRODUCT_KEY, (void *)product_key);
  aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_DEVICE_NAME, (void *)device_name);
  aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_DEVICE_SECRET, (void *)device_secret);
  aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_NETWORK_CRED, (void *)&cred);
  aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_RECV_HANDLER, (void *)mqtt_default_recv_handler);
  aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_EVENT_HANDLER, (void *)mqtt_event_handler);
  res = aiot_mqtt_connect(mqtt_handle);
  iot_connection_state = "on";
  if (res < STATE_SUCCESS) {

    aiot_mqtt_deinit(&mqtt_handle);
    iot_connection_state = "off";
    printf("aiot_mqtt_connect failed: -0x%04X\n", -res);
    return -1;
  }
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
  res = pthread_create(&iot_state_thread, NULL, iot_state_thread_fun, mqtt_handle);
  if (res < 0) {
    printf("pthread_create mqtt_recv_thread failed: %d\n", res);
    iot_work_state = "error";
    return -1;
  }
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
  pthread_join(iot_state_thread,NULL);
  iot_connection_state = "off";
  iot_work_state = "error";
  return 0;
}
