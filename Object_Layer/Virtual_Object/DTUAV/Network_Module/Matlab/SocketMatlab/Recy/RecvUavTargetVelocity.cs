/*
 *
 *  GNU General Public License (GPL)
 *
 * Update Information:
 *                    First: 2021-8-6 In Guangdong University of Technology By Yuanlin Yang  Email: yongwang0808@163.com
 *
 *
 *
 *
 *
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
        [Header("是否重新开启")]
        public bool IsStartAgain = false;
        [Header("是否使用动态初始化IP")]
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
