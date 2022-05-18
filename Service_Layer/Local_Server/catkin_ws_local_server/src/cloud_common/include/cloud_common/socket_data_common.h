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
#ifndef SOCKET_DATA_COMMON_H
#define SOCKET_DATA_COMMON_H
#include <iostream>
#include <x2struct/x2struct.hpp>
namespace dtcloud {
#pragma pack(1)
struct data_size
{
  double size_0;
  double size_1;
  double size_2;
  double size_3;
  double size_4;
  double size_5;
  double size_6;
  double size_7;
  double size_8;
  double size_9;
};

struct socket_data_packet
{
  int data_packet_from;
  int data_packet_to;
  int data_packet_type;
  std::string data;
  XTOSTRUCT(O(data_packet_from,data_packet_to,data_packet_type,data));
};

struct socket_data_packet_stamp
{
  int TargetID;
  int SourceID;
  int MessageID;
  double TimeStamp;
  std::string MessageData;
  XTOSTRUCT(O(TargetID,SourceID,MessageData,MessageID,TimeStamp));
};



}





#endif // SOCKET_DATA_COMMON_H
