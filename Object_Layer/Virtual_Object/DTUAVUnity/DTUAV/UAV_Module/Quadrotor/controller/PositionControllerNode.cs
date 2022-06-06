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
using System.Threading;
using DTUAV.Quadrotor.Controller;
using DTUAV.Quadrotor.Motion;
using DTUAV.Quadrotor.QuadrotorMath;
using LCM.LCM;
using quadrotor_msgs;
using UnityEngine;

namespace DTUAV.Quadrotor.Controller
{
    public class PositionControllerNode : MonoBehaviour, LCMSubscriber
    {
        // Start is called before the first frame update
        [Header("The Parameter of Position P Controller")]
        public double KpX;

        public double KpY;
        public double KpZ;

        [Header("The Parameter of Velocity PID Controller")]
        public double KpVx;

        public double KiVx;
        public double KdVx;

        public double KpVy;
        public double KiVy;
        public double KdVy;

        public double KpVz;
        public double KiVz;
        public double KdVz;

        [Header("The Parameter of Angle P Controller")]
        public double KpRoll;

        public double KpPitch;
        public double KpYaw;

        [Header("The Parameter of Rotation Rate PID Controller")]
        public double KpRx;

        public double KiRx;
        public double KdRx;

        public double KpRy;
        public double KiRy;
        public double KdRy;

        public double KpRz;
        public double KiRz;
        public double KdRz;

        public string StateTopicName;
        public float RunHz;
        public MotionNode MotionNodeInstance;
        [Header("The Target Position and Yaw in Uav Coordinate System")]
        public double TargetPositionX;
        public double TargetPositionY;
        public double TargetPositionZ;
        public double TargetYaw;
        [Header("Some Limitation of Position Controller")]
        public double MaxDevVelocity;
        public double MaxAngle;
        public double MaxF;
        public double MaxRotation;
        public double MaxTorque;
        public double Mass;

        private Thread _runThread;
        private int _sleepTime;
        private bool _isStop;
        private LCM.LCM.LCM _uavStateLcm;
        private QuadrotorState _state;
        private PositionController _positionController;
        private double _curTime;
        private QuadrotorTargetPosition _quadrotorTargetPosition;
        public void MessageReceived(LCM.LCM.LCM lcm, string channel, LCMDataInputStream ins)
        {
          //  Debug.Log("ddddd");
            quadrotor_msgs.quadrotor_state temQuadrotorState = new quadrotor_state(ins);
            _state.PosX = temQuadrotorState.pos_x;
            _state.PosY = temQuadrotorState.pos_y;
            _state.PosZ = temQuadrotorState.pos_z;
            _state.VelX = temQuadrotorState.vel_x;
            _state.VelY = temQuadrotorState.vel_y;
            _state.VelZ = temQuadrotorState.vel_z;
            _state.AccX = temQuadrotorState.acc_x;
            _state.AccY = temQuadrotorState.acc_y;
            _state.AccZ = temQuadrotorState.acc_z;
            _state.Roll = temQuadrotorState.roll;
            _state.Pitch = temQuadrotorState.pitch;
            _state.Yaw = temQuadrotorState.yaw;
            _state.VelRoll = temQuadrotorState.vel_roll;
            _state.VelPitch = temQuadrotorState.vel_pitch;
            _state.VelYaw = temQuadrotorState.vel_yaw;
            _state.AccRoll = temQuadrotorState.acc_roll;
            _state.AccPitch = temQuadrotorState.acc_pitch;
            _state.AccYaw = temQuadrotorState.acc_yaw;
            _state.OmegaX = temQuadrotorState.omega_x;
            _state.OmegaY = temQuadrotorState.omega_y;
            _state.OmegaZ = temQuadrotorState.omega_z;
            _state.OmegaAccX = temQuadrotorState.omega_acc_x;
            _state.OmegaAccY = temQuadrotorState.omega_acc_y;
            _state.OmegaAccZ = temQuadrotorState.omega_acc_z;
            _curTime = temQuadrotorState.timestamp;
        }

        private QuadrotorVector4 ToPropellerRate(QuadrotorInput inputValue)
        {
            QuadrotorVector4 ret = new QuadrotorVector4();
            double ct = 1.105e-05;
            double cm = 1.779e-07;
            double d = 0.225;
            double k = 0.707107;
            Debug.Log("QuadrotorInput: "+"( "+inputValue.F+","+inputValue.Tx+","+inputValue.Ty+","+inputValue.Tz+")");
            ret.x = System.Math.Sqrt((1 / (4 * ct))*inputValue.F + (1 / (4 * ct * d * k))*inputValue.Tx+(1 / (4 * ct * d * k))*inputValue.Ty+(1 / (4 * cm))*inputValue.Tz);
            ret.y = System.Math.Sqrt((1 / (4 * ct)) * inputValue.F+( -1 / (4 * ct * d * k)) * inputValue.Tx + (1 / (4 * ct * d * k)) * inputValue.Ty+( -1 / (4 * cm)) * inputValue.Tz);

            ret.z = System.Math.Sqrt(( 1 / (4 * ct)) * inputValue.F + (-1 / (4 * ct * d * k)) * inputValue.Tx + (- 1 / (4 * ct * d * k)) * inputValue.Ty + (1 / (4 * cm)) * inputValue.Tz);
            ret.w = System.Math.Sqrt((1 / (4 * ct)) * inputValue.F + (1 / (4 * ct * d * k)) * inputValue.Tx + (-1 / (4 * ct * d * k)) * inputValue.Ty + (-1 / (4 * cm)) * inputValue.Tz);
            Debug.Log("rate.x: "+ret.x+" rate.y"+ret.y+" rate.z"+ret.z+" rate.w"+ret.w);
            return ret;
        }

        void UpdateController()
        {
            QuadrotorInput targetInput = new QuadrotorInput();
            while (!_isStop)
            {
                _quadrotorTargetPosition.x = TargetPositionX;
                _quadrotorTargetPosition.y = TargetPositionY;
                _quadrotorTargetPosition.z = TargetPositionZ;
                _quadrotorTargetPosition.yaw = TargetYaw*3.14/180;
                targetInput = _positionController.UpdateController(_state, _quadrotorTargetPosition);
                MotionNodeInstance.UpdatePropellerRate(ToPropellerRate(targetInput));
                System.Threading.Thread.Sleep(_sleepTime);
            }
            
        }

        void Start()
        {
            _uavStateLcm = new LCM.LCM.LCM();
            _uavStateLcm.Subscribe(StateTopicName, this);
            _isStop = false;
            _state = new QuadrotorState();
            _sleepTime = (int) ((1 / RunHz) * 1000);

            _positionController = new PositionController(MaxDevVelocity,MaxAngle,MaxF,MaxRotation,MaxTorque,Mass);
            _positionController.InitXController(KpX);
            _positionController.InitYController(KpY);
            _positionController.InitZController(KpZ);
            _positionController.InitVxController(KpVx, KiVx, KiVx);
            _positionController.InitVyController(KpVy, KiVy, KpVy);
            _positionController.InitVzController(KpVz, KiVz, KdVz);
            _positionController.InitRollController(KpRoll);
            _positionController.InitPitchController(KpPitch);
            _positionController.InitYawController(KpYaw);
            _positionController.InitRxController(KpRx, KiRx, KdRx);
            _positionController.InitRyController(KpRy, KiRy, KdRy);
            _positionController.InitRzController(KpRz, KiRz, KdRz);

            _quadrotorTargetPosition.x = TargetPositionX;
            _quadrotorTargetPosition.y = TargetPositionY;
            _quadrotorTargetPosition.z = TargetPositionZ;
            _quadrotorTargetPosition.yaw = TargetYaw;

            _runThread = new Thread(UpdateController);
            _runThread.IsBackground = true;
            _runThread.Start();

        }

        void OnDestroy()
        {
            _isStop = true;
        }
    }
}
