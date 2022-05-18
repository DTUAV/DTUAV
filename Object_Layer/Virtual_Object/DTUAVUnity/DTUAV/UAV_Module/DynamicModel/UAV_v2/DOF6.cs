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
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DTUAV.Math.DataStructure;
namespace DTUAV.UAV_Module.Quadrotor
{
    public class DOF6 : MonoBehaviour
    {
        public DT_Vector3 GlobalInitPosition = new DT_Vector3();
        public DT_Vector3 GlobalPosition = new DT_Vector3();
        public DT_Vector3 LocalPosition = new DT_Vector3();
        public DT_Vector3 AttitudeAngle = new DT_Vector3();
        public DT_Vector4 Rotation = new DT_Vector4();

        public DT_Vector3 GlobalPositionRos = new DT_Vector3();
        public DT_Vector3 LocalPositionRos = new DT_Vector3();
        public DT_Vector4 RotationRos = new DT_Vector4();


        public DT_Vector3 LineVelocity = new DT_Vector3();
        public DT_Vector3 AngleVelocity = new DT_Vector3();

        public DT_Vector3 LineAAcceleration = new DT_Vector3();
        public DT_Vector3 AngleAAcceleration = new DT_Vector3();

        public DT_Vector3 LineAcceleration = new DT_Vector3();
        public DT_Vector3 AngleAcceleration = new DT_Vector3();

        public float Weight;
        public float CurrentPitch;
        public float CurrentRoll;
        public float CurrentYaw;
        public DT_Vector3 Size = new DT_Vector3();


    }
}
