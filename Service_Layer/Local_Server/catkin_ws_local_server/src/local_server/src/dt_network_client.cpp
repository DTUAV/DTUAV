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
#include "../include/local_server/dt_network_client.h"
static int data_recv_rate;
ros::Publisher ros_pub;
ros::Subscriber ros_sub;
string CheckRecvData(string msg)
{
  string ret;
  if(msg[0] != '{')
  {
    ret = "";
  }
  else
  {
    int num = 0;
    for(int i=0;i<msg.length();i++)
    {
      if(msg[i] =='}')
      {
        num++;
      }
      if(num == 2)
      {
        ret = msg.substr(0,i+1);
        break;
      }
    }
  }
  return ret;
}
dt_network_client::dt_network_client(int argc, char **argv)
{
  ros::init(argc,argv,"socket_network");
  ros::NodeHandle nh("~");
  nh.param("port",_port,8000);
  nh.getParam("ros_pub_topic",ros_pub_topic);
  nh.getParam("ros_sub_topic",ros_sub_topic);
  nh.param("data_recv_rate_hz",_data_recv_rate_hz,25);
  nh.param<string>("server_ip",_serverIP,"192.168.0.1");
  data_recv_rate = _data_recv_rate_hz;
  ros_sub = nh.subscribe(ros_sub_topic,1,&dt_network_client::rosSubMsgCallback,this);
  ros_pub = nh.advertise<cloud_common::socket_data_packet_stamp_msg>(ros_pub_topic,1);
  _socketFd = socket(AF_INET,SOCK_STREAM,0);
  if(_socketFd == -1)
  {
    cout<<"socket create failure--restart this node"<<endl;
    exit(-1);
  }
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(_port);
  addr.sin_addr.s_addr = inet_addr(_serverIP.c_str());
  int res = connect(_socketFd,(struct sockaddr*)&addr,sizeof(addr));
  if(res == -1)
  {
    cout<<"bind failure--restart this node"<<endl;
    close(_socketFd);
    exit(-1);
  }
  else
  {
    cout<<"connect to server with"+_serverIP<<endl;
    pthread_create(&data_recv_thread,NULL,&dt_network_client::data_recv,&_socketFd);
    pthread_detach(data_recv_thread);

  }
}
dt_network_client::~dt_network_client()
{
  close(_socketFd);
  pthread_exit(0);
}


void *dt_network_client::data_recv(void *arg)
{
  int connfd = *(int *)arg;
  ros::Rate rate(data_recv_rate);
  dtcloud::socket_data_packet_stamp data_packet;
  while(ros::ok())
  {
    char buf[2];
    if(recv(connfd,buf,2,0) == 2)
    {
      if(buf[0] == '\n'&&buf[1]=='\n')
      {
        char data_size_buf[32];
        //memset(&data_size_stu,0,sizeof(data_size_stu));
        if(recv(connfd,&data_size_buf,32,0) == 32)
        {
          long packet_data_size=0;
          string data_size_str(data_size_buf);
          for(int i = 0; i< 32; i++){
            if(data_size_str.at(i)=='1')
            {
              packet_data_size += pow(2.0,32-i-1);
            }
          }
          // long packet_data_size = getDataSize(data_size_stu);
        //  std::cout<<"packet_data_size:"<<packet_data_size<<std::endl;
          char buff[packet_data_size];
          if(recv(connfd,buff,packet_data_size,0) == packet_data_size)
          {
            string check_str(buff);
            string str = CheckRecvData(check_str);
            if(str != "")
            {
            bool is_load = x2struct::X::loadjson(str,data_packet,false);
            if(is_load)
            {
              cloud_common::socket_data_packet_stamp_msg data_packet_msg;
              data_packet_msg.MessageData = data_packet.MessageData;
              data_packet_msg.MessageID   = data_packet.MessageID;
              data_packet_msg.SourceID    = data_packet.SourceID;
              data_packet_msg.TargetID    = data_packet.TargetID;
              data_packet_msg.TimeStamp   = data_packet.TimeStamp;
              ros_pub.publish(data_packet_msg);
              rate.sleep();
            }
          }
          }
        }
      }
    }
  }
}
void dt_network_client::rosSubMsgCallback(const cloud_common::socket_data_packet_stamp_msgConstPtr &msg)
{
  dtcloud::socket_data_packet_stamp data_packet;
  data_packet.MessageData = msg.get()->MessageData;
  data_packet.MessageID   = msg.get()->MessageID;
  data_packet.SourceID    = msg.get()->SourceID;
  data_packet.TargetID    = msg.get()->TargetID;
  data_packet.TimeStamp   = msg.get()->TimeStamp;
  string send_msg = x2struct::X::tojson(data_packet);
  char buf[2];
  char str[] = "00000000000000000000000000000000";
  int n = send_msg.length();
  for (int i = 0; i < 32; i++) if (((1 << i) & n) == (1 << i)) str[31 - i] = '1';
  buf[0] = '\n';
  buf[1] = '\n';
  send(_socketFd,buf,2,0);
  send(_socketFd,str,32,0);
  int ret;
  if(ret = send(_socketFd,(const void *)send_msg.c_str(),send_msg.length(),0)<0)
  {
     printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
  }
}

