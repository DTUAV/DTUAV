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
    public struct Inertiadouble
    {
       public double m;//Mass(kg)
       public Vector3double com;//Center of mass(m)
       public double ixx;
       public double ixy;
       public double ixz;
       public double iyy;
       public double iyz;
       public double izz;
    }
    [Serializable] 
    [StructLayout(LayoutKind.Sequential, Pack = 1)] 
    public struct Inertiafloat
    {
       public float m;//Mass(kg)
       public Vector3float com;//Center of mass(m)
       public float ixx;
       public float ixy;
       public float ixz;
       public float iyy;
       public float iyz;
       public float izz;
    }

}