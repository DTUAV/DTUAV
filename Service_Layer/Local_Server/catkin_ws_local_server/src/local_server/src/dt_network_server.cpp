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
#include "../include/local_server/dt_network_server.h"
static int data_recv_rate;
std::mutex clientsMutex;
ros::Publisher ros_pub;
ros::Subscriber ros_sub;
vector<clientInfo> clients;
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
dt_network_server::dt_network_server(int argc, char **argv)
{
    ros::init(argc,argv,"socket_network");
    ros::NodeHandle nh("~");
    nh.param("port",port,8000);
    nh.getParam("ros_pub_topic",ros_pub_topic);
    nh.getParam("ros_sub_topic",ros_sub_topic);
    nh.param("data_recv_rate_hz",data_recv_rate_hz,25);
    data_recv_rate = data_recv_rate_hz;
    ros_sub = nh.subscribe(ros_sub_topic,1,&dt_network_server::ros_sub_cb,this);
    ros_pub = nh.advertise<cloud_common::socket_data_packet_stamp_msg>(ros_pub_topic,1);
    pthread_create(&server_connect_thread,NULL,&dt_network_server::server_connect,this);
    pthread_detach(server_connect_thread);
}

void *dt_network_server::server_connect_msg(void *arg)
{
    clientPoint client_point_temp = *(clientPoint *)arg;
    int clientfd_temp = *(int *)(client_point_temp.client_fd);
    dt_network_server *server_point = (dt_network_server*)(client_point_temp.server);
    int clientPort = *(int *)(client_point_temp.client_port);
    string clientIp = (client_point_temp.client_ip);
    ros::Rate rate(10.0);
    dtcloud::socket_data_packet_stamp data_packet;
    while(ros::ok())
    {
        char buf[2];
        if(recv(clientfd_temp,buf,2,0) == 2)
        {
            if(buf[0] == '\n'&&buf[1]=='\n')
            {
                char data_size_buf[32];
                if(recv(clientfd_temp,&data_size_buf,32,0) == 32)
                {
                    long packet_data_size=0;
                    string data_size_str(data_size_buf);
                    for(int i = 0; i< 32; i++){
                        if(data_size_str.at(i)=='1')
                        {
                            packet_data_size += pow(2.0,32-i-1);
                        }
                    }
                    char buff[packet_data_size];
                    if(recv(clientfd_temp,buff,packet_data_size,0) == packet_data_size)
                    {
                        string check_str(buff);
                        string str = CheckRecvData(check_str);
                        if(str != "")
                        {
                            bool is_load = x2struct::X::loadjson(str,data_packet,false);
                            if(is_load)
                            { //std::cout<<"ffffffffffffffffff"<<std::endl;
                                clientInfo client_info;
                                client_info.client_fd = clientfd_temp;
                                client_info.source_id = data_packet.SourceID;
                                client_info.target_id = data_packet.TargetID;
                                {
                                    std::lock_guard<std::mutex> lock(clientsMutex);
                                    clients.push_back(client_info);
                                }
                                bool is_config = false;
                                for(int i=0;i<clients.size();i++)
                                {
                                    if(clients.at(i).client_fd == clientfd_temp)
                                    {

                                        is_config = true;
                                        pthread_create(&(server_point->data_recv_thread),NULL,&dt_network_server::data_recv,&clientfd_temp);
                                        pthread_detach(server_point->data_recv_thread);
                                        std::cout<<"Receive Message From Clinet: IP = "<<clientIp<<" , "<<"Port: "<<clientPort<<" . "<<" && "<<"SourceID = "<<data_packet.SourceID<<" , "<<"TargetID = "<<data_packet.TargetID<<std::endl;
                                        break;
                                    }
                                    else
                                    {
                                        is_config = false;
                                    }
                                }
                                if(is_config)
                                {
                                    break;
                                }
                                else
                                {
                                    std::cout<<"Wait Message From Clinet: IP = "<<clientIp<<" , "<<"Port: "<<clientPort<<std::endl;
                                }
                            }
                        }
                    }
                }
            }
        }
        rate.sleep();
    }
}


void *dt_network_server::server_connect(void *arg)
{
    dt_network_server* server_point = (dt_network_server*)(arg);
    dtcloud::socket_data_packet_stamp data_packet;
    ros::Rate rate(20.0);
    struct sockaddr_in my_addr;
    server_point->serverfd = socket(AF_INET,SOCK_STREAM,0);
    if(server_point->serverfd < 0)
    {
        perror("socket error");
        exit(-1);
    }
    bzero(&my_addr,sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(server_point->port);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    printf("Binding server to port %d\n", server_point->port);
    int err_log = bind(server_point->serverfd,(struct sockaddr*)&my_addr,sizeof(my_addr));
    if(err_log !=0)
    {
        perror("bind error");
        close(server_point->serverfd);
        exit(-1);
    }
    err_log = listen(server_point->serverfd,10);
    if(err_log !=0)
    {
        perror("listen error");
        close(server_point->serverfd);
        exit(-1);
    }
    printf("Waiting client...\n");
    int test_recv = 0;
    while(ros::ok())
    {
        printf("Waiting new client...\n");
        char cli_ip[INET_ADDRSTRLEN] = "";
        struct sockaddr_in client_addr;
        socklen_t cliaddr_len = sizeof(client_addr);
        int clientfd_temp = accept(server_point->serverfd,(struct sockaddr*)&client_addr,&cliaddr_len);
        if(clientfd_temp < 0)
        {
            printf("accept error");
            close(clientfd_temp);
        }
        else
        {
            inet_ntop(AF_INET, &client_addr.sin_addr, cli_ip, INET_ADDRSTRLEN);
            printf("----------------------------------------------\n");
            printf("client ip=%s,port=%d\n", cli_ip,ntohs(client_addr.sin_port));

            clientPoint client_point_temp;
            client_point_temp.client_fd = &clientfd_temp;
            client_point_temp.server = server_point;
            string clientIp(cli_ip);
            client_point_temp.client_ip = clientIp;
            int clientPort = ntohs(client_addr.sin_port);
            client_point_temp.client_port = &clientPort;
            pthread_create(&(server_point->connect_msg_thread),NULL,&dt_network_server::server_connect_msg,&client_point_temp);
            pthread_detach(server_point->connect_msg_thread);
        }
        rate.sleep();
    }
}

dt_network_server::~dt_network_server()
{
    close(clientfd);
    close(serverfd);
    pthread_exit(0);
}

void *dt_network_server::data_recv(void *arg)
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

                                for(int i =0;i<clients.size();i++)
                                {
                                    if(clients.at(i).source_id == data_packet.TargetID)
                                    {
                                        //std::cout<<"source_id: "<< clients.at(i).source_id<<std::endl;
                                        string send_msg = x2struct::X::tojson(data_packet);
                                        char str[] = "00000000000000000000000000000000";
                                        int n = send_msg.length();
                                        for (int k = 0; k < 32; k++) if (((1 << k) & n) == (1 << k)) str[31 - k] = '1';
                                        int ret;
                                        {
                                            char buf[2];
                                            buf[0] = '\n';
                                            buf[1] = '\n';
                                            if(ret = send(clients.at(i).client_fd,buf,2,0)<0)
                                            {
                                                printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
                                                // close(clients.at(i).client_fd);
                                                {
                                                    std::lock_guard<std::mutex> lock(clientsMutex);
                                                    for(int j = i;j<clients.size()-1;j++)
                                                    {
                                                        clients.at(j) = clients.at(j+1);
                                                    }
                                                    if(!clients.empty())
                                                    {
                                                        clients.pop_back();
                                                    }
                                                }

                                            }
                                            else
                                            {
                                                if(ret = send(clients.at(i).client_fd,str,32,0)<0)
                                                {
                                                    printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
                                                    // close(clients.at(i).client_fd);
                                                    {
                                                        std::lock_guard<std::mutex> lock(clientsMutex);
                                                        for(int j = i;j<clients.size()-1;j++)
                                                        {
                                                            clients.at(j) = clients.at(j+1);
                                                        }
                                                        if(!clients.empty())
                                                        {
                                                            clients.pop_back();
                                                        }
                                                    }
                                                }
                                                else
                                                {
                                                    if(ret = send(clients.at(i).client_fd,(const void *)send_msg.c_str(),send_msg.length(),0)<0)
                                                    {
                                                        printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
                                                        // close(clients.at(i).client_fd);
                                                        {
                                                            std::lock_guard<std::mutex> lock(clientsMutex);
                                                            for(int j = i;j<clients.size()-1;j++)
                                                            {
                                                                clients.at(j) = clients.at(j+1);
                                                            }
                                                            if(!clients.empty())
                                                            {
                                                                clients.pop_back();
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        rate.sleep();
    }
}

void dt_network_server::ros_sub_cb(const cloud_common::socket_data_packet_stamp_msgConstPtr &msg)
{
    for(int i =0;i<clients.size();i++)
    {
        if(clients.at(i).source_id == msg.get()->TargetID)
        {

            dtcloud::socket_data_packet_stamp data_packet;
            data_packet.MessageData = msg.get()->MessageData;
            data_packet.MessageID   = msg.get()->MessageID;
            data_packet.SourceID    = msg.get()->SourceID;
            data_packet.TargetID    = msg.get()->TargetID;
            data_packet.TimeStamp   = msg.get()->TimeStamp;
            string send_msg = x2struct::X::tojson(data_packet);
            char str[] = "00000000000000000000000000000000";
            int n = send_msg.length();
            for (int k = 0; k < 32; k++) if (((1 << k) & n) == (1 << k)) str[31 - k] = '1';
            int ret;
            {
                std::lock_guard<std::mutex> lock(clientsMutex);
                char buf[2];
                buf[0] = '\n';
                buf[1] = '\n';
                if(ret = send(clients.at(i).client_fd,buf,2,0)<0)
                {
                    printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
                    // close(clients.at(i).client_fd);
                    std::lock_guard<std::mutex> lock(clientsMutex);
                    {
                        for(int j = i;j<clients.size()-1;j++)
                        {
                            clients.at(j) = clients.at(j+1);
                        }
                        if(!clients.empty())
                        {
                            clients.pop_back();
                        }
                    }
                }
                else
                {
                    if(ret = send(clients.at(i).client_fd,str,32,0)<0)
                    {
                        printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
                        // close(clients.at(i).client_fd);
                        {
                            std::lock_guard<std::mutex> lock(clientsMutex);
                            for(int j = i;j<clients.size()-1;j++)
                            {
                                clients.at(j) = clients.at(j+1);
                            }
                            if(!clients.empty())
                            {
                                clients.pop_back();
                            }
                        }
                    }
                    else
                    {
                        if(ret = send(clients.at(i).client_fd,(const void *)send_msg.c_str(),send_msg.length(),0)<0)
                        {
                            printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
                            // close(clients.at(i).client_fd);
                            {
                                std::lock_guard<std::mutex> lock(clientsMutex);

                                for(int j = i;j<clients.size()-1;j++)
                                {
                                    clients.at(j) = clients.at(j+1);
                                }
                                if(!clients.empty())
                                {
                                    clients.pop_back();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

