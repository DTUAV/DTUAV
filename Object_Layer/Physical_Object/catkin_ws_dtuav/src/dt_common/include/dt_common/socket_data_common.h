#ifndef SOCKET_DATA_COMMON_H
#define SOCKET_DATA_COMMON_H
#include <iostream>
#include <x2struct/x2struct.hpp>
namespace DTUAV {
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
