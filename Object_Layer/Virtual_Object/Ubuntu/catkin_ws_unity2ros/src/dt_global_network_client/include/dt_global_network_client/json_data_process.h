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
