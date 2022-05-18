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
    public struct TargetVelocity
    {
       public double linear_velocity_x;
       public double linear_velocity_y;
       public double linear_velocity_z;
       public double anger_velocity_x;
       public double anger_velocity_y;
       public double anger_velocity_z;
    }



    public class RecvUavTargetVelocity : MonoBehaviour
    {
        public string IP = "192.168.116.128";
        public int Port = 8009;
        [Header("need to be restarted?")]
        public bool IsStartAgain = false;
        [Header("need to use dynamic initialization IP?")]
        public bool IsInitIpD = false;
        public float MessageHz;
        private int _sleepTime;
        private Socket _socketRecv;
        private SocketClientBase _clientBase;
        private StructBytes _strb;
        private bool _endFlag;
        private TargetVelocity _targetVelocity;

        private Thread _recvThread;
        void Start()
        {
            _endFlag = false;
            _strb = new StructBytes();
            _targetVelocity = new TargetVelocity();
            _sleepTime = (int)((1.0 / MessageHz) * 1000);
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

            }
        }
        void Recv()
        {
            
            while (!_endFlag)
            {
                try
                {
                    byte[] buffer = _strb.StructToBytes(_targetVelocity);
                    //实际接收到的有效字节数
                    int len = _socketRecv.Receive(buffer);
                    if (len == 0)
                    {
                        break;
                    }
                    _targetVelocity = _strb.Bytes2Struct<TargetVelocity>(buffer);
                     Debug.Log("ref_position_x: " + _targetVelocity.linear_velocity_x);
                }
                catch
                {
                    Debug.Log("Recv error!!!");
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
                _socketRecv.Close();
                if (_socketRecv.IsBound)
                {
                    _socketRecv.Close();
                }
                if (_recvThread.IsAlive)
                {
                    _recvThread.Abort();
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
            if (_socketRecv.IsBound)
            {
                _socketRecv.Close();
            }
            if (_recvThread.IsAlive)
            {
                _recvThread.Abort();
            }

        }
    }
}
