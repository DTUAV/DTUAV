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
using RosSharp.RosBridgeClient;
using System.Collections;
using System.Collections.Generic;
using System.Threading;
using DTUAV.Math.DataNoise;
using UnityEngine;

namespace DTUAV.Sensor_Module.Imu
{
    public class ImuNodeRos : UnityPublisher<RosSharp.RosBridgeClient.MessageTypes.Sensor.Imu>
    {
        [Header("The Rigidbody of Imu Object")]
        public Rigidbody ImuRb;
        [Header("The Frame ID of Imu Message")]
        public string FrameId = "F450";
        private RosSharp.RosBridgeClient.MessageTypes.Sensor.Imu _message;
        [Header("Is Add Noise")]
        public bool IsAddNoise = false;
        [Header("The Running Frequency of Imu")]
        public float RunHz;
        private Thread _imuThread;
        private int _sleepTime;
        private bool _isRun;
        private Imu _imuNode;

        private Vector3 _curLinearAcc;

        private Vector3 _curAngularVel;

        private Quaternion _curQuaternion;
        // Start is called before the first frame update
        protected override void Start()
        {
            base.Start();
            _message = new RosSharp.RosBridgeClient.MessageTypes.Sensor.Imu()
            {
                header = new RosSharp.RosBridgeClient.MessageTypes.Std.Header { frame_id = FrameId },
                angular_velocity = new RosSharp.RosBridgeClient.MessageTypes.Geometry.Vector3(),
                linear_acceleration = new RosSharp.RosBridgeClient.MessageTypes.Geometry.Vector3(),
                orientation = new RosSharp.RosBridgeClient.MessageTypes.Geometry.Quaternion(),
                angular_velocity_covariance = new double[9],
                linear_acceleration_covariance = new double[9],
                orientation_covariance = new double[9],
            };
            _sleepTime = (int)((1.0 / RunHz) * 1000);
            _isRun = true;
            _imuNode = new Imu(ImuRb);
            _curAngularVel = new Vector3();
            _curLinearAcc = new Vector3();
            _curQuaternion = new Quaternion();
            Loom.RunAsync(
                () =>
                {
                    _imuThread = new Thread(UpdateSensor);
                    _imuThread.IsBackground = true;
                    _imuThread.Start();
                }
            );
        }
        void UpdateSensor()
        {
            while (_isRun)
            {
                Loom.QueueOnMainThread(() =>
                {
                    _imuNode.UpdateSensor(1.0f / RunHz);
                });
                _curAngularVel = TF.TF.Unity2Ros(_imuNode.GetAngularVelocity());
                _curLinearAcc = TF.TF.Unity2Ros(_imuNode.GetLinearAcceleration());
                _curQuaternion = TF.TF.Unity2Ros(_imuNode.GetRotation());

                if (IsAddNoise)
                {
                    _message.angular_velocity.x = _curAngularVel.x + (float) DataNoise.GaussNiose1() / 1000.0f;
                    _message.angular_velocity.y = _curAngularVel.y + (float)DataNoise.GaussNiose1() / 1000.0f;
                    _message.angular_velocity.z = _curAngularVel.z + (float)DataNoise.GaussNiose1() / 1000.0f;
                    _message.linear_acceleration.x = _curLinearAcc.x + (float)DataNoise.GaussNiose1() / 1000.0f;
                    _message.linear_acceleration.y = _curLinearAcc.y + (float)DataNoise.GaussNiose1() / 1000.0f;
                    _message.linear_acceleration.z = _curLinearAcc.z + (float)DataNoise.GaussNiose1() / 1000.0f;
                    _message.orientation.x = _curQuaternion.x + (float)DataNoise.GaussNiose1() / 1000.0f;
                    _message.orientation.y = _curQuaternion.y + (float)DataNoise.GaussNiose1() / 1000.0f;
                    _message.orientation.z = _curQuaternion.z + (float)DataNoise.GaussNiose1() / 1000.0f;
                    _message.orientation.w = _curQuaternion.w + (float)DataNoise.GaussNiose1() / 1000.0f;

                }
                else
                {
                    _message.angular_velocity.x = _curAngularVel.x;
                    _message.angular_velocity.y = _curAngularVel.y;
                    _message.angular_velocity.z = _curAngularVel.z;
                    _message.linear_acceleration.x = _curLinearAcc.x;
                    _message.linear_acceleration.y = _curLinearAcc.y;
                    _message.linear_acceleration.z = _curLinearAcc.z;
                    _message.orientation.x = _curQuaternion.x;
                    _message.orientation.y = _curQuaternion.y;
                    _message.orientation.z = _curQuaternion.z;
                    _message.orientation.w = _curQuaternion.w;
                }
                
                SendRangeMsg();
                System.Threading.Thread.Sleep(_sleepTime);
            }
        }
        private void SendRangeMsg()
        {
            _message.header.Update();
            Publish(_message);

        }
        void OnDestroy()
        {
            _isRun = false;
        }
    }
}
