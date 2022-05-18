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
    public class DroneV2ControlMode : MonoBehaviour
    {
        [Header("Control")]
        [Header("Throttle control")]
        public float Throttle = 0.0f;
        public bool InvertThrottle = true;
        private string ThrottleCommand = "Throttle";

        [Header("Yaw angle control")]
        public float Yaw = 0.0f;
        public bool InvertYaw = false;
        private string YawCommand = "Yaw";

        [Header("Pitch angle control")]
        public float Pitch = 0.0f;
        public bool InvertPitch = true;
        private string PitchCommand = "Pitch";

        [Header("Roll angle control")]
        public float Roll = 0.0f;
        public bool InvertRoll = true;
        private string RollCommand = "Roll";

        [Header("Throttle value")]
        public float ThrottleValue;

        [Header("Throttle increment")]
        public float ThrottleIncrease;

        [Header("Control mode: false: manual control, true: automatic control")]
        public bool ControlModel = false;

        [Header("Positioning mode: 0: GPS positioning system, 1: sensor positioning system")] 
        public uint LocationModel = 0;
        public DroneV2BaseControl BaseControl;

         public float ThrottleToUav;
         public float YawToUav;
         public float PitchToUav;
         public float RollToUav;
         public float IncreaseToUav;
         public float ThrottleValueTo;





        void UpdateInput()
        {
            Throttle = Input.GetAxisRaw(ThrottleCommand) * (InvertThrottle ? -1 : 1);
            Yaw = Input.GetAxisRaw(YawCommand) * (InvertYaw ? -1 : 1);
            Pitch = Input.GetAxisRaw(PitchCommand) * (InvertPitch ? -1 : 1);
            Roll = Input.GetAxisRaw(RollCommand) * (InvertRoll ? -1 : 1);

            ThrottleToUav = Throttle;
            YawToUav = Yaw;
            PitchToUav = Pitch;
            RollToUav = Roll;
            IncreaseToUav = ThrottleIncrease;
            ThrottleValue = BaseControl.HeightCorrectionTo;
            ThrottleValueTo = ThrottleValue;
        }

        // Start is called before the first frame update
       
        // Update is called once per frame
        void FixedUpdate()
        {
            UpdateInput();
        }
    }
}
