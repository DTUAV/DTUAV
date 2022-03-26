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
    public struct TargetLocalPosition
    {
        public double position_x;
        public double position_y;
        public double position_z;
        public double rotation_x;
        public double rotation_y;
        public double rotation_z;
        public double rotation_w;
    }



    public class RecvUavTargetLocalPosition : MonoBehaviour
    {
        public string IP = "192.168.116.128";
        public int Port = 8009;
        [Header("�Ƿ����¿���")]
        public bool IsStartAgain = false;
        [Header("�Ƿ�ʹ�ö�̬��ʼ��IP")]
        public bool IsInitIpD = false;
        public float MessageHz;
        private int _sleepTime;
        private Socket _socketRecv;
        private SocketClientBase _clientBase;
        private StructBytes _strb;
        private bool _endFlag;
        private TargetLocalPosition _targetLocalPosition;

        private Thread _recvThread;
        void Start()
        {
            _endFlag = false;
            _strb = new StructBytes();
            _targetLocalPosition = new TargetLocalPosition();
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
                    byte[] buffer = _strb.StructToBytes(_targetLocalPosition);
                    //ʵ�ʽ��յ�����Ч�ֽ���
                    int len = _socketRecv.Receive(buffer);
                    if (len == 0)
                    {
                        break;
                    }
                    _targetLocalPosition = _strb.Bytes2Struct<TargetLocalPosition>(buffer);
                    Debug.Log("ref_position_x: " + _targetLocalPosition.position_x);
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
