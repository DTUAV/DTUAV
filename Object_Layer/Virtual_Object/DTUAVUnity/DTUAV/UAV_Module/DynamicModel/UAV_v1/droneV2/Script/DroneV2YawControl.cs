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

namespace DTUAV.UAV_Module.droneV2
{
    public class DroneV2YawControl : MonoBehaviour
    {
        [Header("The target yaw")]
        public float refer_yaw;
        [Header("PID Controller")]
        public DroneV2PidControl yaw_PID;
        [Header("The output of PID Controller")]
        public float yawCorrection;
        // Start is called before the first frame update
        [Header("The UAV State")]
        public DroneV2State uavState;

        [HideInInspector] public bool chage_yaw = false;
        void UpdateYaw()
        {
            yawCorrection = yaw_PID.Update(refer_yaw, uavState.uavAngle.y, UnityEngine.Time.fixedDeltaTime);
        }
      
        void FixedUpdate()
        {
            chage_yaw = false;
            UpdateYaw();
            chage_yaw = true;
        }
    }
}