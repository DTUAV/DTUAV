#ifndef JSON_DATA_PROCESS_H
#define JSON_DATA_PROCESS_H
#include <iostream>
using namespace std;
//The function for msg_check
bool IsJsonData(string data)
{

  if(data[0] != '{')
    return false;
  int num = 1;
  for(int i=1;i<data.length();++i)
  {
    if(data[i] == '{')
    {
      ++num;
     // cout<<"true json "<<i<<data[i]<<endl;
    }
    else if(data[i] =='}')
    {
      --num;
      //cout<<"true json "<<i<<data[i]<<endl;
    }
    if(num == 0&&data[data.length()-1] =='}')
    {
     // cout<<"true json"<<"  sucess"<<endl;
      return true;

    }
  }
  return false;
  //cout<<"true json"<<"  fali"<<endl;

}
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

string CheckData(string msg)
{
  int g_position = msg.find_last_of("g");
  int I_position = msg.find_last_of("I");
  int D_position = msg.find_last_of("D");
  if(g_position+1 == I_position&&I_position+1==D_position)
  {
    string data = msg.substr(0,D_position+5);
    return data;
  }
  else
  {   string data;
    while (g_position+1 != I_position&&I_position+1!=D_position)
    {
      data  = msg.substr(0,D_position);
      g_position = data.find_last_of("g");
      I_position = data.find_last_of("I");
      D_position = data.find_last_of("D");
    }
    return data.substr(0,D_position+5);

  }
}
#endif // JSON_DATA_PROCESS_H
