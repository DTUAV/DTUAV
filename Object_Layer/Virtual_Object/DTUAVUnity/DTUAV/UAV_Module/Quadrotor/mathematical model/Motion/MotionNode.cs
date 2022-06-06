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
using System.Text;
using System.Threading;
using DTUAV.Quadrotor.QuadrotorMath;
using DTUAV.Quadrotor.QuadrotorMath.TF;
using UnityEngine;
using LCM.LCM;
using quadrotor_msgs;

namespace DTUAV.Quadrotor.Motion
{
    public class MotionNode : MonoBehaviour
    {
        [Header("The Running Frequency of Motion Node")]
        public float Hz;

        [Header("The Mass of Quadrotor")] public float Mass;

        [Header("The Moment of Inertia for Quadrotor")]
        public double Jxx;

        public double Jyy;
        public double Jzz;

        [Header("The Moment of Inertia for Motor and Propeller")]
        public double Jm; //The Moment of Inertia for Motor and Propeller

        [Header("The Drag Coefficient of Propeller")]
        public double Ct; //The Drag Coefficient of Propeller

        [Header("The Torque Coefficient of Propeller")]
        public double Cm; //The Torque Coefficient of Propeller

        [Header("The Length of Arm")] 
        public double D; //The Length of Arm

        [Header("The Init State of Quadrotor")]
        public Vector3 InitPosition;

        public Vector3 InitAngle;

        [Header("LCM Network")] [Header("The State Message Name of Quadrotor")]
        public string StatePubMsgName;

        [Header("The Frequency of State Message")]
        public float StateMsgHz = 30;

        [Header("Is Select Linear Model")] 
        public bool IsLinearModel = true;

        [Header("The Transform of Propellers")]
        public Transform Propeller1;
        public Transform Propeller2;
        public Transform Propeller3;
        public Transform Propeller4;

        [Header("The Transform of F450")] 
        public Transform F450;

        private LCM.LCM.LCM _statePubLcm;
        private quadrotor_msgs.quadrotor_state _quadrotorStateLcmMsg;
        private Motion _motionNode;
        private QuadrotorState _state;

        private int _statePubThreadSleepTime;
        private Thread _statePubThread;


        private int _sleepTime;
        private bool _isStop;
        private Thread _runThread;
        private QuadrotorVector4 _propellerRate;
        private Vector3 _f450Position;
        private Vector3 _f450Angle;
        void Start()
        {
            _f450Angle = F450.rotation.eulerAngles;
            _f450Position = F450.position;
            _state = new QuadrotorState();
            _propellerRate = new QuadrotorVector4();
            _state.PosX = InitPosition.x;
            _state.PosY = InitPosition.y;
            _state.PosZ = InitPosition.z;
            _state.Roll = InitAngle.x;
            _state.Pitch = InitAngle.y;
            _state.Yaw = InitAngle.z;
            QuadrotorMatrix33 mat = new QuadrotorMatrix33();
            mat.Set(0, 0, Jxx);
            mat.Set(0, 1, 0);
            mat.Set(0, 2, 0);
            mat.Set(1, 0, 0);
            mat.Set(1, 1, Jyy);
            mat.Set(1, 2, 0);
            mat.Set(2, 0, 0);
            mat.Set(2, 1, 0);
            mat.Set(2, 2, Jzz);
            _motionNode = new Motion(Mass, _state, mat, Jm, Ct, Cm, D,IsLinearModel);

            _sleepTime = (int) ((1 / Hz) * 1000);
            _statePubThreadSleepTime = (int) ((1 / StateMsgHz) * 1000);
            _isStop = false;

            _statePubLcm = LCM.LCM.LCM.Singleton;
            _quadrotorStateLcmMsg = new quadrotor_state();

            _statePubThread = new Thread(PublishState);
            _statePubThread.IsBackground = true;
            _statePubThread.Start();

            Loom.RunAsync(
                () =>
                {
                    _runThread = new Thread(UpdateModel);
                    _runThread.IsBackground = true;
                    _runThread.Start();
                }
            );

        }

        void PublishState()
        {
            while (!_isStop)
            {
                _quadrotorStateLcmMsg.timestamp = _motionNode.GetCurrentTime();
                _quadrotorStateLcmMsg.pos_x = _state.PosX;
                _quadrotorStateLcmMsg.pos_y = _state.PosY;
                _quadrotorStateLcmMsg.pos_z = _state.PosZ;
                _quadrotorStateLcmMsg.vel_x = _state.VelX;
                _quadrotorStateLcmMsg.vel_y = _state.VelY;
                _quadrotorStateLcmMsg.vel_z = _state.VelZ;
                _quadrotorStateLcmMsg.acc_x = _state.AccX;
                _quadrotorStateLcmMsg.acc_y = _state.AccY;
                _quadrotorStateLcmMsg.acc_z = _state.AccZ;
                _quadrotorStateLcmMsg.roll = _state.Roll;
                _quadrotorStateLcmMsg.pitch = _state.Pitch;
                _quadrotorStateLcmMsg.yaw = _state.Yaw;
                _quadrotorStateLcmMsg.vel_roll = _state.VelRoll;
                _quadrotorStateLcmMsg.vel_pitch = _state.VelPitch;
                _quadrotorStateLcmMsg.vel_yaw = _state.VelYaw;
                _quadrotorStateLcmMsg.acc_roll = _state.AccRoll;
                _quadrotorStateLcmMsg.acc_pitch = _state.AccPitch;
                _quadrotorStateLcmMsg.acc_yaw = _state.AccYaw;
                _quadrotorStateLcmMsg.omega_x = _state.OmegaX;
                _quadrotorStateLcmMsg.omega_y = _state.OmegaY;
                _quadrotorStateLcmMsg.omega_z = _state.OmegaZ;
                _quadrotorStateLcmMsg.omega_acc_x = _state.OmegaAccX;
                _quadrotorStateLcmMsg.omega_acc_y = _state.OmegaAccY;
                _quadrotorStateLcmMsg.omega_acc_z = _state.OmegaAccZ;
                _statePubLcm.Publish(StatePubMsgName, _quadrotorStateLcmMsg);
                // Debug.Log("sssssssss");
                System.Threading.Thread.Sleep(_statePubThreadSleepTime);
            }
        }

        public bool UpdatePropellerRate(QuadrotorVector4 rate)
        {
            _propellerRate.x = rate.x;
            _propellerRate.y = rate.y;
            _propellerRate.z = rate.z;
            _propellerRate.w = rate.w;
            return true;
        }

        void UpdateModel()
        {
            while (!_isStop)
            {
                Loom.QueueOnMainThread(() =>
                {
                    Propeller1.Rotate(0,-(float)_propellerRate.x,0);
                    Propeller2.Rotate(0, (float) _propellerRate.y, 0);
                    Propeller3.Rotate(0,-(float)_propellerRate.z,0);
                    Propeller4.Rotate(0,(float)_propellerRate.w,0);

                    _f450Position.x = (float) _state.PosX;
                    _f450Position.y = (float) _state.PosY;
                    _f450Position.z = (float) _state.PosZ;
                    _f450Position.z = _f450Position.z > -0.1 ? -0.1f : _f450Position.z;

                    _f450Angle.x = (float) _state.Roll * 180 / 3.14f;
                    _f450Angle.y = (float) _state.Pitch * 180 / 3.14f;
                    _f450Angle.z = (float) _state.Yaw * 180 / 3.14f;

                    F450.position = QuadrotorTF.Uav2Unity(_f450Position);
                    F450.rotation = Quaternion.Euler(QuadrotorTF.Uav2Unity(_f450Angle));
                });

                _state = _motionNode.UpdateModel(_propellerRate, 1/Hz);
                System.Threading.Thread.Sleep(_sleepTime);
            }
        }

        void OnDestroy()
        {
            _isStop = true;
        }
    }
}
