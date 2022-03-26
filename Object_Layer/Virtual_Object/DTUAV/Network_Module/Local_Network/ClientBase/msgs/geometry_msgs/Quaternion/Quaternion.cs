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
namespace DTUAV.Message.Format.Structure.geometry_msgs
{
    [Serializable]
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct Quaterniondouble
    {
      public  double x;
      public  double y;
      public  double z;
      public  double w;
    }
    [Serializable]
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct Quaternionfloat
    {
       public float x;
       public float y;
       public float z;
       public float w;
    }


}


