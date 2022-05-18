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
using System;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using UnityEngine;
using UnityEngine.UI;
using System.Runtime.InteropServices;

namespace DTUAV.Network_Module.Matlab
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct CurrentUavStateMsg
    {
        public double position_x;
        public double position_y;
        public double position_z;

        public double roll;
        public double yaw;
        public double pitch;

        public double rotation_x;
        public double rotation_y;
        public double rotation_z;
        public double rotation_w;

        public double linear_velocity_x;
        public double linear_velocity_y;
        public double linear_velocity_z;
        public double speed;

        public double angular_velocity_x;
        public double angular_velocity_y;
        public double angular_velocity_z;

        public double linear_acceleration_x;
        public double linear_acceleration_y;
        public double linear_acceleration_z;

        public double angular_acceleration_x;
        public double angular_acceleration_y;
        public double angular_acceleration_z;
    }



    public class SendUavState : MonoBehaviour
    {
        public string IP = "192.168.116.128";
        public int Port = 8009;
        [Header("是否重新开启")]
        public bool IsStartAgain = false;
        [Header("是否使用动态初始化IP")]
        public bool IsInitIpD = false;

        public float MessageHz;

        public Rigidbody UavRigidbody;

        private int _sleepTime;
        private Socket _socketSend;
        private SocketClientBase _clientBase;
        private StructBytes _strb;
        private bool _endFlag;
        private CurrentUavStateMsg _uavState;

        private Thread _pubThread;
        private Vector3 _lastLinearVelocity;
        private Vector3 _lastAngularVelocity;
        private double _runTime;
        void Start()
        {
            _endFlag = false;
            _strb = new StructBytes();
            _uavState = new CurrentUavStateMsg();
            _sleepTime = (int)((1.0 / MessageHz) * 1000);
            _runTime = (1.0 / MessageHz);
            _lastAngularVelocity = UavRigidbody.angularVelocity;
            _lastLinearVelocity = UavRigidbody.velocity;
            connect();
        }



        private void connect()
        {
            if (IsInitIpD == true)
            {
                IP = PlayerPrefs.GetString("IP");
            }

            _clientBase = new SocketClientBase(IP, Port);
            _socketSend = _clientBase.ConnectServer();
            if (_socketSend == null)
            {
                Debug.Log("Connection failed!!!");
            }
            else
            {
                Debug.Log("Connection succeeded!!!");
                _endFlag = false;
                Loom.RunAsync(
                    () =>
                    {
                        _pubThread = new Thread(Send);
                        _pubThread.IsBackground = true;
                        _pubThread.Start();
                    }
                );
            }
        }
        void Send()
        {
            Vector3 rosPosition = new Vector3();
            Vector3 rosLinearVelocity = new Vector3();
            Vector3 rosAngularVelocity = new Vector3();
            Vector3 rosAngularAcceleration = new Vector3();
            Vector3 rosLinearAcceleration = new Vector3();
            Quaternion rosRotation = new Quaternion();
            Vector3 rosAngular = new Vector3();
            double speed = 0.0;
            while (!_endFlag)
            {

                Loom.QueueOnMainThread(() =>
                {
                     rosPosition = TF.TF.Unity2Ros(UavRigidbody.position);
                     rosLinearVelocity = TF.TF.Unity2Ros(UavRigidbody.velocity);
                     rosAngularVelocity = TF.TF.Unity2Ros(UavRigidbody.angularVelocity);
                     rosAngularAcceleration = TF.TF.Unity2Ros(UavRigidbody.angularVelocity - _lastAngularVelocity);
                     _lastAngularVelocity = UavRigidbody.angularVelocity;
                     rosLinearAcceleration = TF.TF.Unity2Ros(UavRigidbody.velocity - _lastLinearVelocity);
                     _lastLinearVelocity = UavRigidbody.velocity;
                     rosRotation = TF.TF.Unity2Ros(UavRigidbody.rotation);
                     rosAngular = TF.TF.Unity2Ros(UavRigidbody.rotation.eulerAngles);
                     speed = UavRigidbody.velocity.magnitude;
                });

                _uavState.position_x = rosPosition.x;
                _uavState.position_y = rosPosition.y;
                _uavState.position_z = rosPosition.z;
                _uavState.linear_velocity_x = rosLinearVelocity.x;
                _uavState.linear_velocity_y = rosLinearVelocity.y;
                _uavState.linear_velocity_z = rosLinearVelocity.z;
                _uavState.rotation_x = rosRotation.x;
                _uavState.rotation_y = rosRotation.y;
                _uavState.rotation_z = rosRotation.z;
                _uavState.rotation_w = rosRotation.w;
                _uavState.roll = rosAngular.x;
                _uavState.pitch = rosAngular.y;
                _uavState.yaw = rosAngular.z;
                _uavState.angular_velocity_x = rosAngularVelocity.x;
                _uavState.angular_velocity_y = rosAngularVelocity.y;
                _uavState.angular_velocity_z = rosAngularVelocity.z;
                _uavState.linear_acceleration_x = rosLinearAcceleration.x / _runTime;
                _uavState.linear_acceleration_y = rosLinearAcceleration.y / _runTime;
                _uavState.linear_acceleration_z = rosLinearAcceleration.z / _runTime;
                _uavState.angular_acceleration_x = rosAngularAcceleration.x / _runTime;
                _uavState.angular_acceleration_y = rosAngularAcceleration.y / _runTime;
                _uavState.angular_acceleration_z = rosAngularAcceleration.z / _runTime;
                _uavState.speed = speed;

                try
                {
                    byte[] buffer = _strb.StructToBytes(_uavState);
                    _socketSend.Send(buffer);
                }
                catch
                {
                    Debug.Log("Send error!!!");
                }

                Thread.Sleep(_sleepTime);
            }
        }

        // Start is called before the first frame update
       

        // Update is called once per frame
        void Update()
        {
            if (IsStartAgain)
            {
                _endFlag = true;
                _socketSend.Close();
                if (_socketSend.IsBound)
                {
                    _socketSend.Close();
                }
                if (_pubThread.IsAlive)
                {
                    _pubThread.Abort();
                }
                Start();
                IsStartAgain = false;
            }
        }

        void OnGUI()
        {

        }

        void OnDestroy()
        {
            _endFlag = true;
            if (_socketSend.IsBound)
            {
                _socketSend.Close();
            }
            if (_pubThread.IsAlive)
            {
                _pubThread.Abort();
            }

        }
    }
}
