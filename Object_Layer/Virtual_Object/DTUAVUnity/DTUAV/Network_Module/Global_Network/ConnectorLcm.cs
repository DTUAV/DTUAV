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
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using UnityEngine;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;
using DTUAV.Message;
using LCM.LCM;
using lcm_iot_msgs;
using Unity.VisualScripting;

namespace DTUAV.Network_Module.Global_Network
{
    public class ConnectorLcm
    {
        private string _productKey; //The key of product in cloud platform  
        private string _deviceName; //The name of device in cloud platform
        private string _deviceSecret;//The secret of device in cloud platform
        private string _regionId;//
        private string _publishTopic;//The message publish topic in cloud platform
        private string _subscribeTopic;//The message subscribe topic in cloud plafrom

        private string _completePublishTopic;
        private string _completeSubscribeTopic;

        private MqttClient _mqttClient;

        private string _lcmMessageSubName;
        private string _lcmMessagePubName;

        private LCM.LCM.LCM _lcmPublisher;
        private LCM.LCM.LCM _lcmSubscriber;
        private LcmIotMessage _lcmIotMessage;
        private IotMessage _iotMessage;

        public LcmIotMessage GetLcmIotMessage()
        {
            return _lcmIotMessage;
        }

        public IotMessage GetIotMessage()
        {
            return _iotMessage;
        }

        public string GetLcmMessagePubName()
        {
            return _lcmMessagePubName;
        }
        public string GetLcmMessageSubName()
        {
            return _lcmMessageSubName;
        }

        public string GetSubscribeTopic()
        {
            return _subscribeTopic;
        }
        public string GetPublishTopic()
        {
            return _publishTopic;
        }
        public string GetRegionID()
        {
            return _regionId;
        }
        public string GetDeviceSecret()
        {
            return _deviceSecret;
        }
        public string GetProductKey()
        {
            return _productKey;
        }

        public string GetDeviceName()
        {
            return _deviceName;
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

        void UnpackMsg(string msg)
        {
            string data_msg = CheckRecvData(msg);
            if (data_msg != "")
            {
                IotMessage iotMessage = JsonUtility.FromJson<IotMessage>(data_msg);
                _lcmIotMessage.TimeStamp = iotMessage.TimeStamp;
                _lcmIotMessage.MessageData = iotMessage.MessageData;
                _lcmIotMessage.MessageID = iotMessage.MessageID;
                _lcmIotMessage.SourceID = iotMessage.SourceID;
                _lcmIotMessage.TargetID = iotMessage.TargetID;
                _lcmPublisher.Publish(_lcmMessagePubName, _lcmIotMessage);
                // Debug.Log(_lcmIotMessage.TimeStamp);

            }
        }

        void MqttMsgReceived(object sender, MqttMsgPublishEventArgs e)
        {
            //handle message received
            string topic = e.Topic;
            string message = Encoding.ASCII.GetString(e.Message);
            //Debug.Log("message: "+message);
            UnpackMsg(message);


        }
        private bool Link()
        {
            IPHostEntry host = Dns.GetHostEntry(Dns.GetHostName());
            string clientId = host.AddressList.FirstOrDefault(ip => ip.AddressFamily == System.Net.Sockets.AddressFamily.InterNetwork).ToString();
            string t = Convert.ToString(DateTimeOffset.Now.ToUnixTimeMilliseconds());
            string signmethod = "hmacmd5";

            Dictionary<string, string> dict = new Dictionary<string, string>();
            dict.Add("productKey", _productKey);
            dict.Add("deviceName", _deviceName);
            dict.Add("clientId", clientId);
            dict.Add("timestamp", t);

            string mqttUserName = _deviceName + "&" + _productKey;
            string mqttPassword = SignUtils.sign(dict, _deviceSecret, signmethod);
            string mqttClientId = clientId + "|securemode=3,signmethod=" + signmethod + ",timestamp=" + t + "|";

            string targetServer = _productKey + ".iot-as-mqtt." + _regionId + ".aliyuncs.com";

            _mqttClient = new MqttClient(targetServer);
            _mqttClient.ProtocolVersion = MqttProtocolVersion.Version_3_1_1;

            _mqttClient.Connect(mqttClientId, mqttUserName, mqttPassword, false, 60);
            _mqttClient.MqttMsgPublishReceived += MqttMsgReceived;

            //发布消息
            String content = "{'content':'msg from :" + mqttClientId + "hello'}";
            var id = _mqttClient.Publish(_completePublishTopic, Encoding.ASCII.GetBytes(content));

            //订阅消息
            _mqttClient.Subscribe(new string[] { _completeSubscribeTopic }, new byte[] { 2 });

            return true;
        }


        public bool SendMessage(string iotMsg)
        {
            var id = _mqttClient.Publish(_completePublishTopic, Encoding.ASCII.GetBytes(iotMsg));
            return true;
        }

        public void MessageReceived(LCM.LCM.LCM lcm, string channel, LCMDataInputStream ins)
        {
            Debug.Log("ddd");
            Debug.Log(_lcmMessageSubName);
            Debug.Log("channel: "+channel);
            if (channel == _lcmMessageSubName)
            {
                Debug.Log("ddd");
                LcmIotMessage msg = new LcmIotMessage(ins);
                _iotMessage.TimeStamp = msg.TimeStamp;
                _iotMessage.TargetID = msg.TargetID;
                _iotMessage.SourceID = msg.SourceID;
                _iotMessage.MessageID = msg.MessageID;
                _iotMessage.MessageData = msg.MessageData;
              
                string iotMsgJson = JsonUtility.ToJson(_iotMessage);

                var id = _mqttClient.Publish(_completePublishTopic, Encoding.ASCII.GetBytes(iotMsgJson));
            }
        }

        public ConnectorLcm(string productKey, string deviceName, string deviceSecret,string publishTopic, string subscribeTopic, string lcmMessageSubName, string lcmMessagePubName, string regionId)
        {
            _productKey = productKey;
            _deviceName = deviceName;
            _deviceSecret = deviceSecret;
            _publishTopic = publishTopic;
            _subscribeTopic = subscribeTopic;
            _regionId = regionId;
            _lcmMessageSubName = lcmMessageSubName;
            _lcmMessagePubName = lcmMessagePubName;

            _completePublishTopic = "/" + _productKey + "/" + _deviceName + _publishTopic;
            _completeSubscribeTopic = "/" + _productKey + "/" + _deviceName + _subscribeTopic;


            _lcmSubscriber = new LCM.LCM.LCM();
            _lcmSubscriber.Subscribe(_lcmMessageSubName, new RunSubscriber(this));
            _lcmPublisher = LCM.LCM.LCM.Singleton;
            _lcmIotMessage = new LcmIotMessage();
            _iotMessage = new IotMessage();

            Link();
        }

        public ConnectorLcm(string productKey, string deviceName, string deviceSecret, string publishTopic, string subscribeTopic,string lcmMessageSubName, string lcmMessagePubName)
        {
            _productKey = productKey;
            _deviceName = deviceName;
            _deviceSecret = deviceSecret;
            _publishTopic = publishTopic;
            _subscribeTopic = subscribeTopic;
            _regionId = "cn-shanghai";
            _lcmMessageSubName = lcmMessageSubName;
            _lcmMessagePubName = lcmMessagePubName;

            _completePublishTopic = "/" + _productKey + "/" + _deviceName + _publishTopic;
            _completeSubscribeTopic = "/" + _productKey + "/" + _deviceName + _subscribeTopic;

            _lcmSubscriber = new LCM.LCM.LCM();
            _lcmSubscriber.Subscribe(_lcmMessageSubName, new RunSubscriber(this));
            _lcmPublisher = LCM.LCM.LCM.Singleton;
            _lcmIotMessage = new LcmIotMessage();
            _iotMessage = new IotMessage();

            Link();
        }

        internal class RunSubscriber : LCMSubscriber
        {
            private ConnectorLcm _connectorLcm;
            private IotMessage _iotMessage;
            public RunSubscriber(ConnectorLcm connectorLcm)
            {
                _connectorLcm = connectorLcm;
                _iotMessage = new IotMessage();
            }
            public void MessageReceived(LCM.LCM.LCM lcm, string channel, LCM.LCM.LCMDataInputStream dins)
            {
                
                LcmIotMessage msg = new LcmIotMessage(dins);
                _iotMessage.TimeStamp = msg.TimeStamp;
                _iotMessage.TargetID = msg.TargetID;
                _iotMessage.SourceID = msg.SourceID;
                _iotMessage.MessageID = msg.MessageID;
                _iotMessage.MessageData = msg.MessageData;
                string iotMsgJson = JsonUtility.ToJson(_iotMessage);
                _connectorLcm.SendMessage(iotMsgJson);
              
            }
        }

    }

    
}
