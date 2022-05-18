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
}
