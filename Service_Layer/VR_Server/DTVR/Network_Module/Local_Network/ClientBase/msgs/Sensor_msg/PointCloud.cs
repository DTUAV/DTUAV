﻿/*
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


using System;
using System.Runtime.InteropServices;
using DTUAV.Message.Format.Structure.geometry_msgs;

namespace DTUAV.Message.Format.Structure.sensor_msgs
{
    [Serializable]
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct PointCloudDouble
    {
        public Pointdouble[] points;
        public ChannelDouble[] channels;

    }
    [Serializable]
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct PointCloudFloat
    {
        public Pointfloat[] points;
        public ChannelFloat[] channels;
    }


}