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