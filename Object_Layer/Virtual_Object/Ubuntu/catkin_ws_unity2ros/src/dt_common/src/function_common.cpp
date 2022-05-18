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
#include "../include/dt_common/function_common.h"
DTUAV::data_size getDataSizeStuct(long size)
{
  DTUAV::data_size data_size_stuct;
  data_size_stuct.size_9 = size/1000000000;
  long size_rest = size%1000000000;
  data_size_stuct.size_8 = size_rest/100000000;
  size_rest = size_rest%100000000;
  data_size_stuct.size_7 = size_rest/10000000;
  size_rest = size_rest%10000000;
  data_size_stuct.size_6 = size_rest/1000000;
  size_rest = size_rest%1000000;
  data_size_stuct.size_5 = size_rest/100000;
  size_rest = size_rest%100000;
  data_size_stuct.size_4 = size_rest/10000;
  size_rest = size_rest%10000;
  data_size_stuct.size_3 = size_rest/1000;
  size_rest = size_rest%1000;
  data_size_stuct.size_2 = size_rest/100;
  size_rest = size_rest%100;
  data_size_stuct.size_1 = size_rest/10;
  size_rest = size_rest%10;
  data_size_stuct.size_0 = size_rest;
  return data_size_stuct;
}

long getDataSize(DTUAV::data_size data_size_stuct)
{
  long data_size =  (long)data_size_stuct.size_9*1000000000
                   +(long)data_size_stuct.size_8*100000000
                   +(long)data_size_stuct.size_7*10000000
                   +(long)data_size_stuct.size_6*1000000
                   +(long)data_size_stuct.size_5*100000
                   +(long)data_size_stuct.size_4*10000
                   +(long)data_size_stuct.size_3*1000
                   +(long)data_size_stuct.size_2*100
                   +(long)data_size_stuct.size_1*10
                   +(long)data_size_stuct.size_0*1;
  return data_size;

}

