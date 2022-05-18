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
