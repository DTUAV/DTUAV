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
using UnityEngine;
using DTUAV.Math.DataStructure;
namespace DTUAV.TF
{
    public class TF
    {
        public static DT_Vector3 Local2Global(DT_Vector3 local, float yaw)
        {
            DT_Vector3 tf_global = new DT_Vector3();
            tf_global.y = local.y;
            tf_global.x = Mathf.Cos(yaw) * local.x + Mathf.Sin(yaw) * local.z;
            tf_global.z = -Mathf.Sin(yaw) * local.x + Mathf.Cos(yaw) * local.z;
            return tf_global;
        }

        public static DT_Vector3 Global2Local(DT_Vector3 global, float yaw)
        {
            DT_Vector3 tf_local = new DT_Vector3();
            tf_local.y = global.y;
            tf_local.z = Mathf.Cos(yaw) * global.z + Mathf.Sin(yaw) * global.x;
            tf_local.x = -Mathf.Sin(yaw) * global.z + Mathf.Cos(yaw) * global.x;
            return tf_local;
        }
        public static DT_Vector3 Ros2Unity(DT_Vector3 tf_ros)
        {
            DT_Vector3 tf_unity = new DT_Vector3();
            tf_unity.x = -tf_ros.y;
            tf_unity.y = tf_ros.z;
            tf_unity.z = tf_ros.x;
            return tf_unity;
        }

        public static DT_Vector3 Unity2Ros(DT_Vector3 tf_unity)
        {
            DT_Vector3 tf_ros = new DT_Vector3();
            tf_ros.x = tf_unity.z;
            tf_ros.y = -tf_unity.x;
            tf_ros.z = tf_unity.y;
            return tf_ros;
        }
        public static DT_Vector4 Ros2Unity(DT_Vector4 quaternion)
        {
            DT_Vector4 ret = new DT_Vector4();
            ret.x = quaternion.y;
            ret.y = -quaternion.z;
            ret.z = -quaternion.x;
            ret.w = quaternion.w;
            return ret;

        }

        public static DT_Vector4 Unity2Ros(DT_Vector4 quaternion)
        {
            DT_Vector4 ret = new DT_Vector4();
            ret.x = -quaternion.z;
            ret.y = quaternion.x;
            ret.z = -quaternion.y;
            ret.w = quaternion.w;
            return ret;
        }
        public static Vector3 Local2Global(Vector3 local, float yaw)
        {
            Vector3 tf_global = new Vector3();
            tf_global.y = local.y;
            tf_global.x = Mathf.Cos(yaw) * local.x + Mathf.Sin(yaw) * local.z;
            tf_global.z = -Mathf.Sin(yaw) * local.x + Mathf.Cos(yaw) * local.z;
            return tf_global;
        }

        public static Vector3 Global2Local(Vector3 global, float yaw)
        {
            Vector3 tf_local = new Vector3();
            tf_local.y = global.y;
            tf_local.z = Mathf.Cos(yaw) * global.z + Mathf.Sin(yaw) * global.x;
            tf_local.x = -Mathf.Sin(yaw) * global.z + Mathf.Cos(yaw) * global.x;
            return tf_local;
        }
        public static Vector3 Ros2Unity(Vector3 tf_ros)
        {
            Vector3 tf_unity = new Vector3();
            tf_unity.x = -tf_ros.y;
            tf_unity.y = tf_ros.z;
            tf_unity.z = tf_ros.x;
            return tf_unity;
        }

        public static Vector3 Unity2Ros(Vector3 tf_unity)
        {
            Vector3 tf_ros = new Vector3();
            tf_ros.x = tf_unity.z;
            tf_ros.y = -tf_unity.x;
            tf_ros.z = tf_unity.y;
            return tf_ros;
        }
        public static Quaternion Ros2Unity(Quaternion quaternion)
        {
            return new Quaternion(quaternion.y, -quaternion.z, -quaternion.x, quaternion.w);
        }

        public static Quaternion Unity2Ros(Quaternion quaternion)
        {
            return new Quaternion(-quaternion.z, quaternion.x, -quaternion.y, quaternion.w);
        }
    }
}
