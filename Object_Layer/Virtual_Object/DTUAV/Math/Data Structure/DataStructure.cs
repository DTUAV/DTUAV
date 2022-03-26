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
using UnityEngine;

namespace DTUAV.Math.DataStructure
{
    [Serializable]
    public class DT_Vector2
    {
        public float x;
        public float y;
    }

    public class DT_Vector3
    {
        public float x;
        public float y;
        public float z;

        public static DT_Vector3 operator +(DT_Vector3 t1, DT_Vector3 t2)
        {
            DT_Vector3 ret = new DT_Vector3();
            ret.x = t1.x + t2.x;
            ret.y = t1.y + t2.y;
            ret.z = t1.z + t2.z;
            return ret;
        }
        public static DT_Vector3 operator -(DT_Vector3 t1, DT_Vector3 t2)
        {
            DT_Vector3 ret = new DT_Vector3();
            ret.x = t1.x - t2.x;
            ret.y = t1.y - t2.y;
            ret.z = t1.z - t2.z;
            return ret;
        }
       
    }

    public class DT_Vector4
    {
        public float x;
        public float y;
        public float z;
        public float w;
    }


    public class DataStructure
    {

    }
}
