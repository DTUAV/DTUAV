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
using DTUAV.TF;

namespace DTUAV.UAV_Module.Quadrotor
{
    public class UAV4Implement_v2 : DOF6
    {
        public List<Motor_v2> UavMotors;
        public ControlWay_v2 ControlWayInstace;
        public Rigidbody UavRigidbody; //The Rigidbody of UAV

        public Transform Motor1Transform; //The Position of Motor1

        public Transform Motor2Transform; //The Position of Motor2

        public Transform Motor3Transform; //The Position of Motor3

        public Transform Motor4Transform; //The Position of Motor4

        public GameObject Propeller1GameObject; //The GameObject of Propeller1
        public GameObject Propeller2GameObject; //The GameObject of Propeller2
        public GameObject Propeller3GameObject; //The GameObject of Propeller3
        public GameObject Propeller4GameObject; //The GameObject of Propeller4

        public float PitchParam; //The Param of Pitch Effect
        public float RollParam; //The Param of Roll Effect
        public float YawParam; //The Param of Yaw Effect
        public float ThrottleParam1; //The Param of Throttle
        public float ThrottleParam2;
        public float ThrottleParam3;
        public float ThrottleParam4;
        public float PropellerParam; //The Param of Propeller
        public float SimulationTime; //The Interval Time of Simulation

        public bool IsRun; //The Flag of Start Simulation

        public bool IsStart; //The Flag of Start UAV

        public bool IsUnlock; //The Flag of Unlock UAV

        public float CurrentThrottle; //The Value of Throttle

        public float RefPitch; //The Target Pitch In Running Process(Inc)

        public float RefRoll; //The Target Roll In Running Process(Inc)

        public float RefYaw; //The Target Yaw In Running Process(Inc) 

        public float RefHeight;

        public float _power1; //The Power is added to Motor1

        public float _power2; //The Power is added to Motor2

        public float _power3; //The Power is added to Motor3

        public float _power4; //The Power is added to Motor4

        public float _powerSlide; //The Power of Body Slide

        public float _propeller1Speed; //The Speed of Propeller1

        public float _propeller2Speed; //The Speed of Propeller2

        public float _propeller3Speed; //The Speed of Propeller3

        public float _propeller4Speed; //The Speed of Propeller4

        private float _pitch;
        private float _roll;
        private float _yaw;

        private Coroutine UavRun;

        private Coroutine Motor1Run;

        private Coroutine Motor2Run;

        private Coroutine Motor3Run;

        private Coroutine Motor4Run;

        public Vector3 localpositionros = new Vector3();
        public float currentroll;

        // Start is called before the first frame update
        void Start()
        {
            GlobalPosition.x = UavRigidbody.position.x;
            GlobalPosition.y = UavRigidbody.position.y;
            GlobalPosition.z = UavRigidbody.position.z;

            GlobalInitPosition.x = UavRigidbody.position.x;
            GlobalInitPosition.y = UavRigidbody.position.y;
            GlobalInitPosition.z = UavRigidbody.position.z;

            LocalPosition.x = 0;
            LocalPosition.y = 0;
            LocalPosition.z = 0;

            /// CurrentThrottle = 1100;
            // UavRun = StartCoroutine(UpdateRun());
        }

        private void UpdateState()
        {
            GlobalPosition.x = UavRigidbody.position.x;
            GlobalPosition.y = UavRigidbody.position.y;
            GlobalPosition.z = UavRigidbody.position.z;

            GlobalPositionRos = TF.TF.Unity2Ros(GlobalPosition);

            LocalPosition = TF.TF.Global2Local(GlobalPosition - GlobalInitPosition, UavRigidbody.rotation.eulerAngles.y * Mathf.Deg2Rad);

            LocalPositionRos = TF.TF.Unity2Ros(GlobalPosition - GlobalInitPosition);


            localpositionros.x = LocalPositionRos.x;
            localpositionros.y = LocalPositionRos.y;
            localpositionros.z = LocalPositionRos.z;

            AngleVelocity.x = UavRigidbody.angularVelocity.x;
            AngleVelocity.y = UavRigidbody.angularVelocity.y;
            AngleVelocity.z = UavRigidbody.angularVelocity.z;

            LineVelocity.x = UavRigidbody.velocity.x;
            LineVelocity.y = UavRigidbody.velocity.y;
            LineVelocity.z = UavRigidbody.velocity.z;

            AttitudeAngle.x = UavRigidbody.rotation.eulerAngles.x;
            AttitudeAngle.y = UavRigidbody.rotation.eulerAngles.y;
            AttitudeAngle.z = UavRigidbody.rotation.eulerAngles.z;

            CurrentPitch = UavRigidbody.rotation.eulerAngles.x;
            CurrentRoll = UavRigidbody.rotation.eulerAngles.z;
            CurrentYaw = UavRigidbody.rotation.eulerAngles.y;
            CurrentPitch = (CurrentPitch > 180) ? CurrentPitch - 360 : CurrentPitch;
            CurrentRoll = (CurrentRoll > 180) ? CurrentRoll - 360 : CurrentRoll;
            currentroll = CurrentRoll;
        }

        private void UpdatePower()
        {
            CurrentThrottle += RefHeight;
            _power1 += CurrentThrottle * ThrottleParam1;
            _power2 += CurrentThrottle * ThrottleParam2;
            _power3 += CurrentThrottle * ThrottleParam3;
            _power4 += CurrentThrottle * ThrottleParam4;

            //   _power1 -= RefPitch * PitchParam;
            //    _power3 -= RefPitch * PitchParam;
            //  _power2 += RefPitch * PitchParam;
            //   _power4 += RefPitch * PitchParam;

            //   _power1 += RefRoll * RollParam;
            //   _power3 -= RefRoll * RollParam;
            //    _power2 -= RefRoll * RollParam;
            //    _power4 += RefRoll * RollParam;

            //    _powerSlide = RefYaw * YawParam;

            _propeller1Speed = _power1 * PropellerParam;
            _propeller2Speed = _power2 * PropellerParam;
            _propeller3Speed = _power3 * PropellerParam;
            _propeller4Speed = _power4 * PropellerParam;

        }

        private void AddPower()
        {
            UavRigidbody.AddForceAtPosition(transform.up * _power1, Motor1Transform.position, ForceMode.Force);
            UavRigidbody.AddForceAtPosition(transform.up * _power2, Motor2Transform.position, ForceMode.Force);
            UavRigidbody.AddForceAtPosition(transform.up * _power3, Motor3Transform.position, ForceMode.Force);
            UavRigidbody.AddForceAtPosition(transform.up * _power4, Motor4Transform.position, ForceMode.Force);
            UavRigidbody.AddTorque(Vector3.up * _powerSlide, ForceMode.Force);
            Propeller1GameObject.transform.Rotate(0, -_propeller1Speed, 0);
            Propeller2GameObject.transform.Rotate(0, -_propeller2Speed, 0);
            Propeller3GameObject.transform.Rotate(0, _propeller3Speed, 0);
            Propeller4GameObject.transform.Rotate(0, _propeller4Speed, 0);
        }

        private void RunMotors()
        {
            float yaw = 0.0f;
            foreach (Motor_v2 uavMotor in UavMotors)
            {
                Transform motorTransform = uavMotor.MotorObject.transform;

                if (ControlWayInstace == ControlWay_v2.AutomaticFlight)
                {
                    uavMotor.Auto_PitchValue = RefPitch;
                    uavMotor.Auto_RollValue = RefRoll;
                    uavMotor.Auto_YawValue = RefYaw;
                    uavMotor.Auto_ThrottleValue = RefHeight;
                    uavMotor.UpdateForce();
                    yaw += uavMotor.SideForce;
                    UavRigidbody.AddForceAtPosition(transform.up * uavMotor.UpForce, motorTransform.position, ForceMode.Force);
                }
                else
                {
                    uavMotor.Man_PitchValue = RefPitch;
                    uavMotor.Man_RollValue = RefRoll;
                    uavMotor.Man_YawValue = RefYaw;
                    uavMotor.Man_ThrottleValue = RefHeight;
                    uavMotor.UpdateForce();
                    yaw += uavMotor.SideForce;
                    UavRigidbody.AddForceAtPosition(transform.up * uavMotor.UpForce, motorTransform.position, ForceMode.Impulse);
                }
            }
            UavRigidbody.AddTorque(transform.up * yaw, ForceMode.Force);
        }


        void FixedUpdate()
        {
            UpdateState();
            // UpdatePower();
            //AddPower();
            RunMotors();
        }


        private IEnumerator UpdateRun()
        {
            float t = 0;
            while (IsRun)
            {
                t += UnityEngine.Time.deltaTime;
                if (t >= SimulationTime)
                {
                    if (IsStart)
                    {
                        if (IsUnlock)
                        {
                            UpdateState();
                            // UpdatePower();
                            //AddPower();
                            RunMotors();
                        }
                    }

                    t = 0;
                }

                yield return null;
            }

        }

    }
}
