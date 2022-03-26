/*
 *
 *  GNU General Public License (GPL)
 *
 * Update Information:
 *                    First: 2021-8-6 In Guangdong University of Technology By Yuanlin Yang  Email: yongwang0808@163.com
 *
 *
 *
 *
 *
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
