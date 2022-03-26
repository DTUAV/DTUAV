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

using System.Runtime.InteropServices;
using DTUAV.Math;
using UnityEngine;

namespace DTUAV.TF
{
    public class SimTf
    {
        //The Transfer from Unity to NED
        /*
         *      / \                                          / \
         *   z   |                                         x  |
         *       |                                            | 
         *       |——————>x                              |——————> y
         *
         *    Unity  y up                                    NED z down
         */                                              
        public static Vector2 UnityToNED(Vector2 tf_unity)
        {
            Vector2 ret;
            ret.x = tf_unity.y;
            ret.y = tf_unity.x;
            return ret;
        }

        public static Vector2Double UnityToNED(Vector2Double tf_unity)
        {
            Vector2Double ret;
            ret.x = tf_unity.y;
            ret.y = tf_unity.x;
            return ret;
        }
        public static Vector2Float UnityToNED(Vector2Float tf_unity)
        {
            Vector2Float ret;
            ret.x = tf_unity.y;
            ret.y = tf_unity.x;
            return ret;
        }
        public static Vector3 UnityToNED(Vector3 tf_unity)
        {
            Vector3 ret;
            ret.x = tf_unity.z;
            ret.y = tf_unity.x;
            ret.z = -tf_unity.y;
            return ret;
        }
        public static Vector3Double UnityToNED(Vector3Double tf_unity)
        {
            Vector3Double ret;
            ret.x = tf_unity.z;
            ret.y = tf_unity.x;
            ret.z = -tf_unity.y;
            return ret;
        }
        public static Vector3Float UnityToNED(Vector3Float tf_unity)
        {
            Vector3Float ret;
            ret.x = tf_unity.z;
            ret.y = tf_unity.x;
            ret.z = -tf_unity.y;
            return ret;
        }
        public static Quaternion UnityToNED(Quaternion tf_unity)
        {
            Quaternion ret;
            ret.x = tf_unity.z;
            ret.y = tf_unity.x;
            ret.z = -tf_unity.y;
            ret.w = tf_unity.w;
            return ret;
        }
        public static Vector4Double UnityToNED(Vector4Double tf_unity)
        {
            Vector4Double ret;
            ret.x = tf_unity.z;
            ret.y = tf_unity.x;
            ret.z = -tf_unity.y;
            ret.w = tf_unity.w;
            return ret;
        }
        public static Vector4Float UnityToNED(Vector4Float tf_unity)
        {
            Vector4Float ret;
            ret.x = tf_unity.z;
            ret.y = tf_unity.x;
            ret.z = -tf_unity.y;
            ret.w = tf_unity.w;
            return ret;
        }

        public static Vector2 NEDToUnity(Vector2 tf_ned)
        {
            Vector2 ret;
            ret.x = tf_ned.y;
            ret.y = tf_ned.x;
            return ret;
        }

        public static Vector2Double NEDToUnity(Vector2Double tf_ned)
        {
            Vector2Double ret;
            ret.x = tf_ned.y;
            ret.y = tf_ned.x;
            return ret;
        }
        public static Vector2Float NEDToUnity(Vector2Float tf_ned)
        {
            Vector2Float ret;
            ret.x = tf_ned.y;
            ret.y = tf_ned.x;
            return ret;
        }

        public static Vector3 NEDToUnity(Vector3 tf_ned)
        {
            Vector3 ret;
            ret.x = tf_ned.y;
            ret.y = -tf_ned.z;
            ret.z = tf_ned.x;
            return ret;
        }

        public static Vector3Double NEDToUnity(Vector3Double tf_ned)
        {
            Vector3Double ret;
            ret.x = tf_ned.y;
            ret.y = -tf_ned.z;
            ret.z = tf_ned.x;
            return ret;
        }
        public static Vector3Float NEDToUnity(Vector3Float tf_ned)
        {
            Vector3Float ret;
            ret.x = tf_ned.y;
            ret.y = -tf_ned.z;
            ret.z = tf_ned.x;
            return ret;
        }

        public static Quaternion NEDToUnity(Quaternion tf_ned)
        {
            Quaternion ret;
            ret.x = tf_ned.y;
            ret.y = -tf_ned.z;
            ret.z = tf_ned.x;
            ret.w = tf_ned.w;
            return ret;
        }
        public static Vector4Double NEDToUnity(Vector4Double tf_ned)
        {
            Vector4Double ret;
            ret.x = tf_ned.y;
            ret.y = -tf_ned.z;
            ret.z = tf_ned.x;
            ret.w = tf_ned.w;
            return ret;
        }
        public static Vector4Float NEDToUnity(Vector4Float tf_ned)
        {
            Vector4Float ret;
            ret.x = tf_ned.y;
            ret.y = -tf_ned.z;
            ret.z = tf_ned.x;
            ret.w = tf_ned.w;
            return ret;
        }




    }
}
