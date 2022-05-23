using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net;
using System.Text;
using System.Linq;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;
using System;
using System.Threading;
using DTUAV.Message;
using DTUAV.TF;

namespace DigitalTwin.UavCarProject
{
    public class VR_Server : MonoBehaviour
    {
        public string ProductKey = "a1GcqS5WFte";
        public string DeviceName = "VR_Server";
        public string DeviceSecret = "67a5eb9e157e61261a5b0a75a8e2f7d1";
        public string RegionId = "cn-shanghai";
        private string PubTopic;
        private string SubTopic;
        public string Pub = "/user/VR_Server_PUB";
        public string Sub = "/user/VR_Server_SUB";
        private MqttClient clientPub;

        public Rigidbody SimulationUAV;

        public Rigidbody PhysicalUAV;

        private Vector3 _simObjPosition;
        private Quaternion _simObjRotation;
        private Vector3 _phsObjPosition;
        private Quaternion _phsObjRotation;


        // Start is called before the first frame update
        void Start()
        {
            _simObjPosition = new Vector3();
            _simObjRotation = new Quaternion();
            _phsObjPosition = new Vector3();
            _phsObjRotation = new Quaternion();
            PubTopic = "/" + ProductKey + "/" + DeviceName + Pub;
            SubTopic = "/" + ProductKey + "/" + DeviceName + Sub;
            Run();
        }
        void Run()
        {
            IPHostEntry host = Dns.GetHostEntry(Dns.GetHostName());
            string clientId = host.AddressList.FirstOrDefault(
                ip => ip.AddressFamily == System.Net.Sockets.AddressFamily.InterNetwork).ToString();
            string t = Convert.ToString(DateTimeOffset.Now.ToUnixTimeMilliseconds());
            string signmethod = "hmacmd5";

            Dictionary<string, string> dict = new Dictionary<string, string>();
            dict.Add("productKey", ProductKey);
            dict.Add("deviceName", DeviceName);
            dict.Add("clientId", clientId);
            dict.Add("timestamp", t);

            string mqttUserName = DeviceName + "&" + ProductKey;
            string mqttPassword = SignUtils.sign(dict, DeviceSecret, signmethod);
            string mqttClientId = clientId + "|securemode=3,signmethod=" + signmethod + ",timestamp=" + t + "|";

            string targetServer = ProductKey + ".iot-as-mqtt." + RegionId + ".aliyuncs.com";
            ConnectMqtt(targetServer, mqttClientId, mqttUserName, mqttPassword);
        }

        void ConnectMqtt(string targetServer, string mqttClientId, string mqttUserName, string mqttPassword)
        {
            MqttClient client = new MqttClient(targetServer);
            client.ProtocolVersion = MqttProtocolVersion.Version_3_1_1;
            clientPub = client;
            client.Connect(mqttClientId, mqttUserName, mqttPassword, false, 60);
            client.MqttMsgPublishReceived += Client_MqttMsgPublishReceived;

            String content = "{'content':'msg from :" + mqttClientId + "hello px4'}";
            var id = client.Publish(PubTopic, Encoding.ASCII.GetBytes(content));

            client.Subscribe(new string[] { SubTopic }, new byte[] { 2 });

        }

        void Client_MqttMsgPublishReceived(object sender, MqttMsgPublishEventArgs e)
        {
            //handle message received
           // Debug.Log("ddddddddddddddddd");
            string topic = e.Topic;
            string message = Encoding.ASCII.GetString(e.Message);
           // Debug.Log("message: "+message);
            UnpackMsg(message);
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
               IotMessage iotMsg = JsonUtility.FromJson<IotMessage>(data_msg);
               if (iotMsg.MessageID == MessageId.CurrentLocalPositionMsgID)
                {
                    CurrentLocalPositionMsg positionMsg =
                        JsonUtility.FromJson<CurrentLocalPositionMsg>(iotMsg.MessageData);
                    if (iotMsg.SourceID == ObjectId.R_UAV_0)
                    {
                        _phsObjPosition = TF.Ros2Unity(new Vector3((float)positionMsg.position_x, (float)positionMsg.position_y,
                            (float)positionMsg.position_z));
                        _phsObjRotation = TF.Ros2Unity(new Quaternion((float) positionMsg.rotation_x,
                            (float) positionMsg.rotation_y, (float) positionMsg.rotation_z,
                            (float) positionMsg.rotation_w));
                    }
                    else if (iotMsg.SourceID == ObjectId.V_UAV_0)
                    {
                        _simObjPosition = TF.Ros2Unity(new Vector3((float)positionMsg.position_x, (float)positionMsg.position_y,
                            (float)positionMsg.position_z));  
                        _simObjRotation = TF.Ros2Unity(new Quaternion((float)positionMsg.rotation_x,
                            (float)positionMsg.rotation_y, (float)positionMsg.rotation_z,
                            (float)positionMsg.rotation_w));
                      //  Debug.Log("get simulation data");
                    }
                }
                

            }
        }

        // Update is called once per frame
        public void SendMessage(string message)
        {
            clientPub.Publish(PubTopic, Encoding.ASCII.GetBytes(message));
        }
        /*
           //send ref_position to V_UAV_0
           IOT_MSG iotMsg = new IOT_MSG();
               iotMsg.packet_id = message_id.VR_REF_UAV_POSITION_ID;
               iotMsg.packet_object_from = object_id.VR_Server;
               iotMsg.packet_object_to = object_id.V_UAV_0;
               REF_UAV_POSITION_MSG refUavPositionMsg = new REF_UAV_POSITION_MSG();
               refUavPositionMsg.ref_position_x = RefUavPosition.x;
               refUavPositionMsg.ref_position_y = RefUavPosition.y;
               refUavPositionMsg.ref_position_z = RefUavPosition.z;
               iotMsg.packet_data = JsonUtility.ToJson(refUavPositionMsg);
               string iotMsgJson = JsonUtility.ToJson(iotMsg);
               var id = clientPub.Publish(PubTopic, Encoding.ASCII.GetBytes(iotMsgJson));

               //send ref_position to R_UAV_0
               iotMsg.packet_object_to = object_id.R_UAV_0;
               iotMsgJson = JsonUtility.ToJson(iotMsg);
               id = clientPub.Publish(PubTopic, Encoding.ASCII.GetBytes(iotMsgJson));

               IsSendMessage = false;
        */
        void Update()
        {
            SimulationUAV.position = _simObjPosition;
            SimulationUAV.rotation = _simObjRotation.normalized;
            PhysicalUAV.position = _phsObjPosition;
            PhysicalUAV.rotation = _phsObjRotation.normalized;
        }
    }
}
