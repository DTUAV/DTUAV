using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using RosSharp.RosBridgeClient;

namespace DTUAV.UAV_Module.droneV2
{
    public class DroneV2XYZControl : MonoBehaviour
    {
        [Header("The PD Controller of X channel")] 
        public DroneV2PdControl xPd;
        [Header("The output of PD Controller in X channel")] 
        public float xPd_result;
        [Header("The PID Controller of Y channel")] 
        public DroneV2PidControl yPid;
        [Header("The output of PID Controller in Y channel")] 
        public float yPid_result;
        [Header("The PD Controller of Z channel")] 
        public DroneV2PdControl zPd;
        [Header("The output of PD Controller in Z channel")] 
        public float zPd_result;

        [Header("The PID Controller of Pitch")] public DroneV2PidControl pitchPID;
        [Header("The output of PID Controller in Pitch")] public float pitchPID_result;

        [Header("The PID Controller of Roll")] public DroneV2PidControl rollPID;
        [Header("The output of PID Controller in Roll")] public float rollPID_result;

        [Header("The UAV state")] public DroneV2State uavState;

        [Header("The target global position")] 
        public float uavPosition_x = 51;
        public float uavPosition_y = 1;
        public float uavPosition_z = 110;

        private float refUavLocalPosition_x;
        private float refUavLocalPosition_y;
        private float refUavLocalPosition_z;

        private Vector3 uav_init_position;

        [Header("The running status of the UAV")] 
        public bool takeoff = false;//takeoff command
        public bool is_lane = false;//land command
        public bool lane = true;//if land
        public bool IsCollisionCheck = false;//if obstacle avoidance
        [Header("If iscollisionckeck is true, you need to select saferunning")]
        public safe_uav_running SafeRunning;
     
        [HideInInspector] public bool chage_ref_position = true;
        public DroneV2ControlMode inputControl;
        private float ref_position_x;
        private float ref_position_y;
        private float ref_position_z;
        private Vector3 refPositionLocal;
        private float uav_init_heigh;
        void Start()
        {
            uav_init_position = uavState.rb.position;
            uav_init_heigh = uavState.rb.position.y;
        }
        void UpdatePIDResult()
        {
            yPid_result = yPid.Update(refUavLocalPosition_y, uavState.uavPosition.y, UnityEngine.Time.fixedDeltaTime);
            pitchPID_result = pitchPID.Update(zPd_result, uavState.uavAngle.x, UnityEngine.Time.fixedDeltaTime);
            rollPID_result = rollPID.Update(xPd_result, -uavState.uavAngle.z, UnityEngine.Time.fixedDeltaTime);
        }
        Vector3 ToLocalPosition(Vector3 worldPosition,float currentYaw)
        {
            Vector3 localPositon = Vector3.zero;
            localPositon.x = worldPosition.x * Mathf.Cos((3.14f / 180) * currentYaw) -
                                    worldPosition.z * Mathf.Sin((3.14f / 180) * currentYaw);
            localPositon.z = worldPosition.x * Mathf.Sin((3.14f / 180) * currentYaw) +
                                    worldPosition.z * Mathf.Cos((3.14f / 180) * currentYaw);
            localPositon.y = worldPosition.y;
            return localPositon;

        }
        Vector3 ToWorldPosition(Vector3 localPosition, float currentYaw)
        {
            Vector3 worldPosition = Vector3.zero;
            worldPosition.x = localPosition.x * Mathf.Cos((3.14f / 180) * currentYaw) +
                              localPosition.z * Mathf.Sin((3.14f / 180) * currentYaw);
            worldPosition.z = -localPosition.x * Mathf.Sin((3.14f / 180) * currentYaw) +
                              localPosition.z * Mathf.Cos((3.14f / 180) * currentYaw);
            worldPosition.y = localPosition.y;
            return worldPosition;
        }
       
        void UpdatePDResult(float ref_position_x,float ref_position_z,float ref_position_y)
        {
 
         refUavLocalPosition_x = ref_position_x;
         refUavLocalPosition_z = ref_position_z;
            if (is_lane)
            {
                refUavLocalPosition_y = 0;
            }
            else
            {
                refUavLocalPosition_y = ref_position_y;
            }



            zPd_result = zPd.UpdatePD(refUavLocalPosition_z, uavState.uavLocalPosition.z, UnityEngine.Time.fixedDeltaTime);
            xPd_result = xPd.UpdatePD(refUavLocalPosition_x, uavState.uavLocalPosition.x, UnityEngine.Time.fixedDeltaTime);

            zPd_result = Mathf.Clamp(zPd_result, -5, 5);
            xPd_result = Mathf.Clamp(xPd_result, -3, 3);

        }

        void FixedUpdate()
        {
            if (IsCollisionCheck)
            {
                if (SafeRunning.IsWillCollision)
                {
                    refPositionLocal = ToLocalPosition(new Vector3(ref_position_x, ref_position_y, ref_position_z),
                        uavState.uavAngle.y);
                    ref_position_x = SafeRunning.UavCurrentPosition.x;
                    ref_position_z = SafeRunning.UavCurrentPosition.z;
                    ref_position_y = SafeRunning.UavCurrentPosition.y;
                    float currentUavPositionX = uavPosition_x;
                    float currentUavPositionY = uavPosition_y;
                    float currentUavPositionZ = uavPosition_z;
                    
                    Vector3 currentUavPositionLocal =
                        ToLocalPosition(new Vector3(currentUavPositionX, currentUavPositionY, currentUavPositionZ),
                            uavState.uavAngle.y);
                    if (!SafeRunning.isBackCollision && refPositionLocal.z - currentUavPositionLocal.z >= 0)
                    {
                        refPositionLocal.z = currentUavPositionLocal.z;
                    }

                    if (!SafeRunning.isForwardCollision && refPositionLocal.z - currentUavPositionLocal.z <= 0)
                    {
                        refPositionLocal.z = currentUavPositionLocal.z;
                    }

                    if (!SafeRunning.isRightCollision && refPositionLocal.x - currentUavPositionLocal.x <= 0)
                    {
                        refPositionLocal.x = currentUavPositionLocal.x;
                    }

                    if (!SafeRunning.isLeftCollision && refPositionLocal.x - currentUavPositionLocal.x >= 0)
                    {
                        refPositionLocal.x = currentUavPositionLocal.x;
                    }

                    if (!SafeRunning.isUpCollision && refPositionLocal.y - currentUavPositionLocal.y >= 0)
                    {
                        refPositionLocal.y = currentUavPositionLocal.y;
                    }

                    if (!SafeRunning.isDownCollision && refPositionLocal.y - currentUavPositionLocal.y <= 0)
                    {
                        refPositionLocal.y = currentUavPositionLocal.y;
                    }

                    Vector3 refWorldPosition = ToWorldPosition(refPositionLocal, uavState.uavAngle.y);

                    uavPosition_z = refWorldPosition.z;
                    uavPosition_x = refWorldPosition.x;
                    uavPosition_y = refWorldPosition.y;
                }
                else
                {
                    ref_position_x = uavPosition_x;
                    ref_position_z = uavPosition_z;
                    ref_position_y = uavPosition_y;
                    refPositionLocal = ToLocalPosition(new Vector3(ref_position_x, ref_position_y, ref_position_z),
                        uavState.uavAngle.y);
                }
            }

            else
            {
                ref_position_x = uavPosition_x;
                ref_position_z = uavPosition_z;
                ref_position_y = uavPosition_y;
                refPositionLocal = ToLocalPosition(new Vector3(ref_position_x, ref_position_y, ref_position_z),
                    uavState.uavAngle.y);
            }

            if (uavState.uavPosition.y <= uav_init_heigh+0.2)
                {
                    lane = true;
                 }
                else
                {
                    lane = false;
                }

                if (!takeoff && lane)
                {

                }
                else
                {
                    if (inputControl.ControlModel == true)
                    {
                        chage_ref_position = false;
                        UpdatePDResult(refPositionLocal.x, refPositionLocal.z, refPositionLocal.y);
                        UpdatePIDResult();
                        chage_ref_position = true;

                    }
                }
            
        }
    }
}