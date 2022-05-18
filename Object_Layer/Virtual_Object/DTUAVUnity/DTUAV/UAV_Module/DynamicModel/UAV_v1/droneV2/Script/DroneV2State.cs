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
using UnityEngine;
namespace DTUAV.UAV_Module.droneV2
{
    public class DroneV2State : MonoBehaviour
    {
        [Header("UAV Object")]
        public GameObject Uav;

        [Header("Current status of UAV")]
        [Header("Current position of UAV")]
        public Vector3 uavPosition;
        [Header("Sensor estimated UAV position")] 
        public Vector3 sensorEstationPosition;
        [Header("Current attitude angle of UAV")]
        public Vector3 uavAngle;

        public Quaternion uavQuate;
        [Header("Current speed of UAV")]
        public float uavSpeed;
        [Header("Current velocity vector of each axis of UAV")]
        public Vector3 uavVelocity;
        [Header("Current angular velocity vector of each axis of UAV")]
        public Vector3 uavAngleVelocity;

        [Header("UAV rigid body")]
        public Rigidbody rb;

        [Header("UAV coordinate system")]
        public Vector3 uavLocalPosition;
        
        public Quaternion quaternion;
        public Vector3 posePosition;
        public Vector3 angular_velocity;
        public Vector3 linear_velocity;
        public DroneV2ControlMode inputControl;



        public bool getImuDataFlag = false;
        public bool getPoseDataFlag = false;
        public bool getOdometryDataFlag = false;
        public bool getUavStateDataFlag = false;


        private Vector3 last_linear_velocity;
        private Vector3 last_angle_velocity;
        private Vector3 last_position;
        private Vector3 last_angle;
        private Vector3 current_position;
        private float update_time;

        // Start is called before the first frame update
        void Start()
        {
            if (Uav == null)
            {
                Debug.LogError("No drone object specified");
            }
            else
            {
                rb = Uav.GetComponent<Rigidbody>();
                last_position = rb.position;
                last_angle = rb.rotation.eulerAngles;
                last_linear_velocity = rb.velocity;
                last_angle_velocity = rb.angularVelocity;
                uavPosition = rb.position;
                uavQuate = rb.rotation;
                sensorEstationPosition = new Vector3();
            }
        }

        void UpdateMsgState()
        {
            if (!getOdometryDataFlag)
            {
                posePosition = rb.position;
                linear_velocity = rb.velocity;
                quaternion = rb.rotation.normalized;
                angular_velocity = rb.angularVelocity;
                getImuDataFlag = true;
                getPoseDataFlag = true;
                getOdometryDataFlag = true;
                getUavStateDataFlag = true;
            }
        }
        void UpdateState()
        {
            if (inputControl.LocationModel == DroneV2Param.GPS_LOCATION)
            {
                uavPosition = rb.position; 
            }
            else
            {
                uavPosition = sensorEstationPosition;
            }

            uavAngle = rb.rotation.eulerAngles;          
           
            uavAngle.x = (uavAngle.x > 180) ? uavAngle.x - 360 : uavAngle.x;
           
            uavAngle.z = (uavAngle.z > 180) ? uavAngle.z - 360 : uavAngle.z;

            
            uavLocalPosition.x = uavPosition.x * Mathf.Cos((3.14f / 180) * uavAngle.y) - uavPosition.z * Mathf.Sin((3.14f / 180) * uavAngle.y);
            uavLocalPosition.y = uavPosition.y;
            uavLocalPosition.z = uavPosition.x * Mathf.Sin((3.14f / 180) * uavAngle.y) + uavPosition.z * Mathf.Cos((3.14f / 180) * uavAngle.y);

            uavSpeed = rb.velocity.magnitude;
            uavVelocity = rb.velocity;
            uavAngleVelocity = rb.angularVelocity;
            uavQuate = rb.rotation;

        }

        void FixedUpdate()
        {
            UpdateMsgState();
            if (inputControl.ControlModel == true)
            {
                UpdateState();
            }
        }
    }
}
