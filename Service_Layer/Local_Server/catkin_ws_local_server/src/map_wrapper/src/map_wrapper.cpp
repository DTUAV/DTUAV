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
#include "../include/map_wrapper/map_wrapper.h"
int _sock;
struct sockaddr_in gcAddr;
struct sockaddr_in locAddr;
map_wrapper::~map_wrapper()
{

}
void map_wrapper::mavlinkMsgCallback(const mavros_msgs::MavlinkConstPtr &msg)
{
    mavlink_message_t mavlinkMsg;
    uint16_t len;
    uint8_t buf[BUFFER_LENGTH];
    mavlinkMsg.checksum = msg.get()->checksum;
    mavlinkMsg.compid = msg.get()->compid;
    mavlinkMsg.len = msg.get()->len;
    mavlinkMsg.magic = msg.get()->magic;
    mavlinkMsg.msgid = msg.get()->msgid;
    if(msg.get()->payload64.size()<=33)
    {
        for(int i=0;i<msg.get()->payload64.size();++i)
        {
            mavlinkMsg.payload64[i] = msg.get()->payload64.at(i);
        }
    }
    mavlinkMsg.seq = msg.get()->seq;
    mavlinkMsg.sysid = msg.get()->sysid;
    len = mavlink_msg_to_send_buffer(buf, &mavlinkMsg);
    while(sendto(_sock, buf, len, 0, (struct sockaddr*)&gcAddr, sizeof(struct sockaddr_in))!=len);
}

void *map_wrapper::runRecv(void *args)
{
    map_wrapper* wrapper = (map_wrapper*)args;
    ros::Rate rate(wrapper->_dataRecvRateHz);
    uint8_t buf[BUFFER_LENGTH];
    ssize_t recsize;
    socklen_t fromlen = sizeof(gcAddr);
    unsigned int temp = 0;
    mavros_msgs::Mavlink mavlinkMsg;
    while(ros::ok())
    {
        memset(buf, 0, BUFFER_LENGTH);
        recsize = recvfrom(_sock, (void *)buf, BUFFER_LENGTH, 0, (struct sockaddr *)&gcAddr, &fromlen);
        if (recsize > 0)
        {
            // Something received - print out all bytes and parse packet
            mavlink_message_t msg;
            mavlink_status_t status;

            printf("Bytes Received: %d\nDatagram: ", (int)recsize);
            for (ssize_t i = 0; i < recsize; ++i)
            {
                temp = buf[i];
                printf("%02x ", (unsigned char)temp);
                if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status))
                {
                    // Packet received
                    printf("\nReceived packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d\n", msg.sysid, msg.compid, msg.len, msg.msgid);
                }
            }
            printf("\n");
            mavlinkMsg.checksum = msg.checksum;
            mavlinkMsg.compid = msg.compid;
            mavlinkMsg.msgid = msg.msgid;
            mavlinkMsg.len = msg.len;
            mavlinkMsg.magic = msg.magic;
            mavlinkMsg.payload64.resize(33);
            for(int i = 0;i<33;i++)
            {
                mavlinkMsg.payload64.at(i) = msg.payload64[i];
            }
            mavlinkMsg.sysid = msg.sysid;
            mavlinkMsg.seq = msg.seq;
            mavlinkMsg.header.stamp = ros::Time::now();
            wrapper->_mavlinkDataPub.publish(mavlinkMsg);
        }
        memset(buf, 0, BUFFER_LENGTH);
        rate.sleep();

    }
}

map_wrapper::map_wrapper(int argc, char **argv)
{
    ros::init(argc,argv,"map_wrapper");
    ros::NodeHandle nh("~");
    nh.param("qgc_port",_qgcPort,14550);
    nh.param("local_port",_localPort,14551);
    std::cout<<_qgcPort<<std::endl;
    std::string ros_pub_topic = "/map_wrapper/msg/from/map";
    nh.getParam("ros_pub_topic",ros_pub_topic);
    std::string ros_sub_topic = "/map_wrapper/msg/to/map";
    nh.getParam("ros_sub_topic",ros_sub_topic);
    float data_recv_rate_hz = 25;
    nh.getParam("data_recv_rate_hz",data_recv_rate_hz);
    _dataRecvRateHz = data_recv_rate_hz;
    nh.param<std::string>("server_ip",_serverIP,"127.0.0.1");
    std::cout<<_serverIP<<std::endl;
    _mavlinkDataSub = nh.subscribe(ros_sub_topic,1,&map_wrapper::mavlinkMsgCallback,this);
    _mavlinkDataPub = nh.advertise<mavros_msgs::Mavlink>(ros_pub_topic,1);

    _sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    memset(&locAddr, 0, sizeof(locAddr));
    locAddr.sin_family = AF_INET;
    locAddr.sin_addr.s_addr = INADDR_ANY;
    locAddr.sin_port = htons(_localPort);

    if (-1 == bind(_sock,(struct sockaddr *)&locAddr, sizeof(struct sockaddr)))
    {
        perror("error bind failed");
        close(_sock);
        exit(EXIT_FAILURE);
    }

    /* Attempt to make it non blocking */
#if (defined __QNX__) | (defined __QNXNTO__)
    if (fcntl(_sock, F_SETFL, O_NONBLOCK | FASYNC) < 0)
#else
    if (fcntl(_sock, F_SETFL, O_NONBLOCK | O_ASYNC) < 0)
#endif

    {
        fprintf(stderr, "error setting nonblocking: %s\n", strerror(errno));
        close(_sock);
        exit(EXIT_FAILURE);
    }
    memset(&gcAddr, 0, sizeof(gcAddr));
    gcAddr.sin_family = AF_INET;
    gcAddr.sin_addr.s_addr = inet_addr(_serverIP.c_str());
    gcAddr.sin_port = htons(_qgcPort);
    int flag_thread = pthread_create(&dataRecvThread,NULL,&map_wrapper::runRecv,this);
    if (flag_thread < 0) {
      ROS_ERROR("pthread_create ros_process_thread failed: %d\n", flag_thread);
    }
}

/* QNX timer version */
#if (defined __QNX__) | (defined __QNXNTO__)
uint64_t map_wrapper::microsSinceEpoch()
{

    struct timespec time;

    uint64_t micros = 0;

    clock_gettime(CLOCK_REALTIME, &time);
    micros = (uint64_t)time.tv_sec * 1000000 + time.tv_nsec/1000;

    return micros;
}
#else
uint64_t map_wrapper::microsSinceEpoch()
{
    struct timeval tv;
    uint64_t micros = 0;
    gettimeofday(&tv, NULL);
    micros =  ((uint64_t)tv.tv_sec) * 1000000 + tv.tv_usec;
    return micros;
}
#endif
