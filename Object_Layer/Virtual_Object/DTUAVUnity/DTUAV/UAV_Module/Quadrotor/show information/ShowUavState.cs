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
using DTUAV.Quadrotor.QuadrotorMath;
using LCM.LCM;
using quadrotor_msgs;
using UnityEngine;

namespace DTUAV.Quadrotor
{
    public class ShowUavState : MonoBehaviour, LCMSubscriber
    {
        public string StateTopicName;
        public TextMesh Text;
        private LCM.LCM.LCM _showUavStateLcm;
        private bool _isShow;
        private QuadrotorState _state;
        private double _curTime;

        private string PackVector3(double x, double y, double z)
        {
            return "(" + x + "," + y + "," + z + ")";
        }

        private string PackStateMsg(QuadrotorState state)
        {
            string ret = "Quadrotor State: " + "\n"
                                               + "  Position: " + PackVector3(state.PosX, state.PosY, state.PosZ) + "\n"
                                               + "  Linear Velocity: " + PackVector3(state.VelX, state.VelY, state.VelZ) + "\n"
                                               + "  Linear Acceleration: " + PackVector3(state.AccX, state.AccY, state.AccZ) + "\n"
                                               + "  Rotation: " + PackVector3(state.Roll, state.Pitch, state.Yaw) + "\n"
                                               + "  Rotation Velocity: " + PackVector3(state.VelRoll, state.VelPitch, state.VelYaw) + "\n"
                                               + "  Rotation Acceleration: " + PackVector3(state.AccRoll, state.AccPitch, state.AccYaw) + "\n"
                                               + "  Omega: " + PackVector3(state.OmegaX, state.OmegaY, state.OmegaZ) + "\n"
                                               + "  Omega Acceleration: " + PackVector3(state.OmegaAccX, state.OmegaAccY, state.OmegaAccZ) + "\n";
            return ret;
        }
        public void MessageReceived(LCM.LCM.LCM lcm, string channel, LCMDataInputStream ins)
        {
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

        // Start is called before the first frame update
        void Start()
        {
            _showUavStateLcm = new LCM.LCM.LCM();
            _showUavStateLcm.Subscribe(StateTopicName, this);
            _isShow = false;
            _state = new QuadrotorState();
        }

        // Update is called once per frame
        void Update()
        {
            Text.text = PackStateMsg(_state);
        }
    }
}
