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
using LCM.LCM;
using lcm_iot_msgs;
using DTUAV.Message;

namespace DTUAV.Network_Module.Local_Network
{
    public class LocalClient : MonoBehaviour, LCM.LCM.LCMSubscriber
    {
        public string IP = "192.168.152.12";
        public int Port = 8080;
        public bool IsStartAgain = false;
        public string IotMessageSubName;
        public string IotMessagePubName;
        public float DataRecvHz;
        public bool isAutoMessageName = true;
        private LCM.LCM.LCM PubLcm;
        private LCM.LCM.LCM SubLcm;
        private LcmIotMessage _lcmIotMessage;
        private IotMessage _iotMessage;
        private Socket socketSend;
        private SocketClientBase clientBase;
        private Thread c_thread;
        private bool endFlag = false;
        private int _recvTime;
        private void connect()
        {
            clientBase = new SocketClientBase(IP, Port);
            socketSend = clientBase.ConnectServer();
            if (socketSend == null)
            {
                Debug.Log("Connection Failed");
            }
            else
            {
                Debug.Log("Connection Successful!");
                endFlag = false;
                c_thread = new Thread(Received);
                c_thread.IsBackground = true;
                c_thread.Start();
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

        void Received()
        {
            while (!endFlag)
            {
                try
                {
                    byte[] buf = new byte[2];
                    if (socketSend.Receive(buf, 0, 2, SocketFlags.None) == 2)
                    {
                        if (buf[0] == '\n' && buf[1] == '\n')
                        {
                            byte[] bufDataSize = new byte[32];
                            if (socketSend.Receive(bufDataSize, 0, 32, SocketFlags.None) == 32)//
                            {
                                string dataLenstr = System.Text.Encoding.UTF8.GetString(bufDataSize);//byte[]-->string//
                                Int32 recvDataLen = Convert.ToInt32(dataLenstr, 2);//string -->int32//
                                byte[] bufRecvData = new byte[recvDataLen];
                                if (socketSend.Receive(bufRecvData, 0, (int)recvDataLen, SocketFlags.None) == recvDataLen)
                                {
                                    string check_ctr = CheckRecvData(Encoding.ASCII.GetString(bufRecvData));
                                    Debug.Log("data:" + check_ctr + "dd:" + Encoding.ASCII.GetString(bufRecvData));
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
        // Start is called before the first frame update
        void Start()
        {
            if (isAutoMessageName)
            {
                IotMessageSubName ="/"+ this.gameObject.transform.parent.name + IotMessageSubName;
                IotMessagePubName = "/" + this.gameObject.transform.parent.name + IotMessagePubName;
            }


            SubLcm = new LCM.LCM.LCM();
            SubLcm.Subscribe(IotMessageSubName, this);
            PubLcm = LCM.LCM.LCM.Singleton;
            _lcmIotMessage = new LcmIotMessage();
            _iotMessage = new IotMessage();
            _recvTime = (int)((1.0 / DataRecvHz) * 1000);
            connect();

        }

        // Update is called once per frame
        void Update()
        {
            if (IsStartAgain)
            {
                endFlag = true;
                socketSend.Close();
                if (c_thread.IsAlive)
                {
                    c_thread.Abort();
                }
                Start();
                IsStartAgain = false;
            }
        }

        void OnDestroy()
        {
            endFlag = true;
            socketSend.Close();
            if (c_thread.IsAlive)
            {
                c_thread.Abort();
            }

        }
        public static int BytesToInt(byte[] src, int offset)
        {
            int value;
            value = (int)(((src[offset] & 0xFF) << 24)
                          | ((src[offset + 1] & 0xFF) << 16)
                          | ((src[offset + 2] & 0xFF) << 8)
                          | (src[offset + 3] & 0xFF));
            return value;
        }

        public static byte[] IntToBytes(int value)
        {
            byte[] src = new byte[4];
            src[0] = (byte)((value >> 24) & 0xFF);
            src[1] = (byte)((value >> 16) & 0xFF);
            src[2] = (byte)((value >> 8) & 0xFF);
            src[3] = (byte)(value & 0xFF);
            return src;
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
                socketSend.Send(dataFlagBuffer);
                socketSend.Send(dataSizeBuffer);
                socketSend.Send(dataSendBuffer);
                 Debug.Log("dataLen:"+dataLen);
                // DateTime centuryBegin = new DateTime(2001, 1, 1);
                // DateTime currentDate = DateTime.Now;
                // long elapsedTicks = currentDate.Ticks - centuryBegin.Ticks;
                // TimeSpan elapsedSpan = new TimeSpan(elapsedTicks);
                // Debug.Log("recv"+elapsedSpan.TotalSeconds);
            }
        }
    }
}