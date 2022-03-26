using System;
using UnityEngine;
using System.Collections;
using System.Net.Sockets;
using System.Net;
using System.Collections.Generic;
using System.Threading;
using System.Text;
using System.Runtime.InteropServices;
using DTUAV.Message;
using UnityEditor.PackageManager;
using LCM.LCM;
using lcm_iot_msgs;

namespace DTUAV.Network_Module.Local_Network
{
    public class LocalServer : MonoBehaviour, LCM.LCM.LCMSubscriber
    {
        public string IP = "192.168.1.11";//服务端的IP
        public System.Int32 Port = 9000;//连接的端口

        public float RecvHz;

        public string IotMessageSubName;
        public string IotMessagePubName;

        private Socket _serverSocket;
        private Socket _clienttSocket;

        private Thread _recvThread;

        private Thread _connectThread;

        private bool _isRecvMsg;
        private bool _isConnect;

        private int _recvTime;

        private LcmIotMessage _lcmIotMessage;
        private IotMessage _iotMessage;

        private LCM.LCM.LCM PubLcm;
        private LCM.LCM.LCM SubLcm;

        private bool _isHaveConnect;
        void Start()
        {
            StartSocket();
        }

        // Start is called before the first frame update
        void StartSocket()
        {
            SubLcm = new LCM.LCM.LCM();
            SubLcm.Subscribe(IotMessageSubName, this);
            PubLcm = LCM.LCM.LCM.Singleton;
            _lcmIotMessage = new LcmIotMessage();
            _iotMessage = new IotMessage();

            _isRecvMsg = true;
            _isConnect = true;
            _isHaveConnect = false;
            _recvTime = (int)((1.0 / RecvHz) * 1000);
            _serverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            _serverSocket.Bind(new IPEndPoint(IPAddress.Parse(IP), Port));
            _serverSocket.Listen(100);

            _connectThread = new Thread(WaitConnect);
            _connectThread.Start();

            _recvThread = new Thread(ReadFormClient);
            _recvThread.Start();

        }

        void WaitConnect()
        {
            while (_isConnect)
            {
                _clienttSocket = _serverSocket.Accept();
                Debug.Log("client：" + _serverSocket.RemoteEndPoint);
                _isHaveConnect = true;
                _isConnect = false;
            }
        }
        string CheckRecvData(string msg)
        {
            string ret = "";
            if (msg[0] != '{')
            {
                ret = "";
            }
            else
            {
                int num = 0;
                for (int i = 0; i < msg.Length; i++)
                {
                    if (msg[i] == '}')
                    {
                        num++;
                    }
                    if (num == 2)
                    {
                        ret = msg.Substring(0, i + 1);
                        break;
                    }
                }
            }
            return ret;
        }
        public void ReadFormClient()
        {
            while (_isRecvMsg)
            {
                try
                {
                    byte[] buf = new byte[2];
                    if (_clienttSocket.Receive(buf, 0, 2, SocketFlags.None) == 2)
                    {
                        if (buf[0] == '\n' && buf[1] == '\n')
                        {
                            byte[] bufDataSize = new byte[32];
                            if (_clienttSocket.Receive(bufDataSize, 0, 32, SocketFlags.None) == 32) //
                            {
                                string dataLenstr =
                                    System.Text.Encoding.UTF8.GetString(bufDataSize); //byte[]-->string//
                                Int32 recvDataLen = Convert.ToInt32(dataLenstr, 2); //string -->int32//
                                byte[] bufRecvData = new byte[recvDataLen];
                                if (_clienttSocket.Receive(bufRecvData, 0, (int) recvDataLen, SocketFlags.None) ==
                                    recvDataLen)
                                {
                                    string check_ctr = CheckRecvData(Encoding.ASCII.GetString(bufRecvData));
                                     Debug.Log("server data:" + check_ctr + "dd:" + Encoding.ASCII.GetString(bufRecvData));
                                    if (check_ctr != "")
                                    {
                                        IotMessage recvMessage = JsonUtility.FromJson<IotMessage>(check_ctr);
                                        _lcmIotMessage.TimeStamp = recvMessage.TimeStamp;
                                        _lcmIotMessage.MessageData = recvMessage.MessageData;
                                        _lcmIotMessage.MessageID = recvMessage.MessageID;
                                        _lcmIotMessage.SourceID = recvMessage.SourceID;
                                        _lcmIotMessage.TargetID = recvMessage.TargetID;
                                        PubLcm.Publish(IotMessagePubName, _lcmIotMessage);
                                        //   Debug.Log(Encoding.ASCII.GetString(bufRecvData));
                                        //    Debug.Log(_lcmIotMessage.TimeStamp);
                                    }
                                }
                            }

                        }
                    }
                }
                catch
                {

                }

                System.Threading.Thread.Sleep(_recvTime);
            }
        }

        void OnDestroy()
        {
            _isRecvMsg = false;
            _serverSocket.Close();
            if (_recvThread.IsAlive)
            {
                _recvThread.Abort();
            }
        }

        public void MessageReceived(LCM.LCM.LCM lcm, string channel, LCMDataInputStream ins)
        {
            if (channel == IotMessageSubName)
            {
                LcmIotMessage msg = new LcmIotMessage(ins);
                _iotMessage.TimeStamp = msg.TimeStamp;
                _iotMessage.TargetID = msg.TargetID;
                _iotMessage.SourceID = msg.SourceID;
                _iotMessage.MessageID = msg.MessageID;
                _iotMessage.MessageData = msg.MessageData;
                string iotMsgJson = JsonUtility.ToJson(_iotMessage);
                Int32 dataLen = Encoding.UTF8.GetBytes(iotMsgJson).Length;
                string dataLenStr = Convert.ToString(dataLen, 2).PadLeft(32, '0');
                byte[] dataSizeBuffer = Encoding.UTF8.GetBytes(dataLenStr);//
                byte[] dataFlagBuffer = new byte[2];
                dataFlagBuffer[0] = (byte)'\n';
                dataFlagBuffer[1] = (byte)'\n';
                byte[] dataSendBuffer = Encoding.UTF8.GetBytes(iotMsgJson);
                _clienttSocket.Send(dataFlagBuffer);
                _clienttSocket.Send(dataSizeBuffer);
                _clienttSocket.Send(dataSendBuffer);
                // Debug.Log("dataLen:"+dataLen);
                // DateTime centuryBegin = new DateTime(2001, 1, 1);
                // DateTime currentDate = DateTime.Now;
                // long elapsedTicks = currentDate.Ticks - centuryBegin.Ticks;
                // TimeSpan elapsedSpan = new TimeSpan(elapsedTicks);
                // Debug.Log("recv"+elapsedSpan.TotalSeconds);
            }
        }
    }

}