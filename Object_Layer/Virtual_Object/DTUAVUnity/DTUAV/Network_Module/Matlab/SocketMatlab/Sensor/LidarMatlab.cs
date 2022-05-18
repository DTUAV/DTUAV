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
using DTUAV.Sensor_Module.LiDAR;
using DTUAV.UAV_Module.Quadrotor;

namespace DTUAV.Network_Module.Matlab
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct PointCloud
    {

        /// double[1000]
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1000, ArraySubType = UnmanagedType.R8)]
        public double[] x;

        /// double[1000]
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1000, ArraySubType = UnmanagedType.R8)]
        public double[] y;

        /// double[1000]
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1000, ArraySubType = UnmanagedType.R8)]
        public double[] z;

        /// double[1000]
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1000, ArraySubType = UnmanagedType.R8)]
        public double[] values;



    }

    public class LidarMatlab : MonoBehaviour
    {
        public string IP = "192.168.116.128";
        public int Port = 8009;
        [Header("need to be restarted?")]
        public bool IsStartAgain = false;
        [Header("need to use dynamic initialization IP?")]
        public bool IsInitIpD = false;
        public float RecvMessageHz;
        private int _recvSleepTime;
        public float SendMessageHz;
        public LidarNode LidarNodeInstance;
        public PositionControl PositionNode;
        private int _sendSleepTime;
        private Socket _socketRecv;
        private SocketClientBase _clientBase;
        private StructBytes _strb;
        private bool _endFlag;
        private TargetLocalPosition _targetLocalPosition;

        private Thread _recvThread;
        private PointCloud _pointCloud;
        private Thread _pubThread;
        private double _runTime;
        // Start is called before the first frame update
        void Start()
        {
            _pointCloud.x = new Double[1000];
            _pointCloud.y = new double[1000];
            _pointCloud.z = new double[1000];
            _pointCloud.values = new double[1000];
            _endFlag = false;
            _strb = new StructBytes();
            _targetLocalPosition = new TargetLocalPosition();
            _recvSleepTime = (int)((1.0 / RecvMessageHz) * 1000);
            _sendSleepTime = (int)((1.0 / SendMessageHz) * 1000);
            _runTime = (1.0 / SendMessageHz);
            connect();
        }
        private void connect()
        {
            if (IsInitIpD == true)
            {
                IP = PlayerPrefs.GetString("IP");
            }

            _clientBase = new SocketClientBase(IP, Port);
            _socketRecv = _clientBase.ConnectServer();
            if (_socketRecv == null)
            {
                Debug.Log("Connection failed!!!");
            }
            else
            {
                Debug.Log("Connection succeeded!!!");
                _endFlag = false;
                _recvThread = new Thread(Recv);
                _recvThread.IsBackground = true;
                _recvThread.Start();
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
        void Recv()
        {

            while (!_endFlag)
            {
                try
                {
                    byte[] buffer = _strb.StructToBytes(_targetLocalPosition);
                    int len = _socketRecv.Receive(buffer);
                    if (len == 0)
                    {
                        break;
                    }
                    _targetLocalPosition = _strb.Bytes2Struct<TargetLocalPosition>(buffer);
                    Debug.Log("ref_position_x: " + _targetLocalPosition.position_x);
                    PositionNode.RefLocalPoseRos.x = (float)_targetLocalPosition.position_x;
                    PositionNode.RefLocalPoseRos.y = (float)_targetLocalPosition.position_y;
                    PositionNode.RefLocalPoseRos.z = (float)_targetLocalPosition.position_z;
                }
                catch
                {
                    Debug.Log("Recv error!!!");
                }

                Thread.Sleep(_recvSleepTime);
            }
        }
        void Send()
        { 
            List<Vector3> data = new List<Vector3>();
            float minRange = LidarNodeInstance.minRange;
            float maxRange = LidarNodeInstance.maxRange;
            while (!_endFlag)
            {

                Loom.QueueOnMainThread(() =>
                {

                });
                data = LidarNodeInstance.RayPositions;
                if (data.Count==1000)
                {
                    for (int i = 0; i < 1000; i++)
                    {
                        _pointCloud.x[i] = data[i].z;
                        _pointCloud.y[i] = -data[i].x;
                        _pointCloud.z[i] = data[i].y;
                        _pointCloud.values[i] = (data[i].magnitude - minRange)*255 / (maxRange-minRange);
                    }

                    try
                    {
                        byte[] buffer = _strb.StructToBytes(_pointCloud);
                        _socketRecv.Send(buffer);
                    }
                    catch
                    {
                        Debug.Log("Send error!!!");
                    }
                }
                else
                {
                   // Debug.LogError("The number of Lidar data not equal to 1000.");
                }
               

                Thread.Sleep(_sendSleepTime);
            }
        }

        // Start is called before the first frame update


        // Update is called once per frame
        void Update()
        {
            if (IsStartAgain)
            {
                _endFlag = true;
                _socketRecv.Close();
                if (_socketRecv.IsBound)
                {
                    _socketRecv.Close();
                }
                if (_recvThread.IsAlive)
                {
                    _recvThread.Abort();
                }
                if (_pubThread.IsAlive)
                {
                    _pubThread.Abort();
                }
                Start();
                IsStartAgain = false;
            }
        }
        void OnDestroy()
        {
            _endFlag = true;
            if (_socketRecv.IsBound)
            {
                _socketRecv.Close();
            }
            if (_recvThread.IsAlive)
            {
                _recvThread.Abort();
            }
            if (_pubThread.IsAlive)
            {
                _pubThread.Abort();
            }

        }
    }
}
