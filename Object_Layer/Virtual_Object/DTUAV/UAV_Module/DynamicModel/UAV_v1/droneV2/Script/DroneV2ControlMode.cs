using System.Collections;
using System.Collections.Generic;
using UnityEngine;
namespace DTUAV.UAV_Module.droneV2
{
    public class DroneV2ControlMode : MonoBehaviour
    {
        [Header("控制量")]
        [Header("油门控制")]
        public float Throttle = 0.0f;//油门控制
        public bool InvertThrottle = true;
        private string ThrottleCommand = "Throttle";

        [Header("偏航角控制")]
        public float Yaw = 0.0f;//偏航角控制
        public bool InvertYaw = false;
        private string YawCommand = "Yaw";

        [Header("俯仰角控制")]
        public float Pitch = 0.0f;//偏航角控制
        public bool InvertPitch = true;
        private string PitchCommand = "Pitch";

        [Header("滚转角控制")]
        public float Roll = 0.0f;//滚转角控制
        public bool InvertRoll = true;
        private string RollCommand = "Roll";

        [Header("油门量")]
        public float ThrottleValue;

        [Header("油门增量")]
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
