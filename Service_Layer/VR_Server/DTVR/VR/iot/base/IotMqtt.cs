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
//using UnityEditor.Experimental.GraphView;

namespace SimUnity.Aliyun
{

    public struct unpackPart
    {
        public string pack_id;
        public string pack_data_size;
        public string pack_data;
    }



    public class IotMqtt: MonoBehaviour
    {
        public string ProductKey = "a1cfhQNta1r";
        public string DeviceName = "test";
        public string DeviceSecret = "38eca2c980a3871272985cac3e636285";
        public string RegionId = "cn-shanghai";

        public string PubTopic ;
        public string SubTopic;

        public string Pub = "/update";
        public string Sub = "/get";

        private MqttClient clientPub;
        private Thread deal_thread;

        private List<string> list_recv = new List<string>();
        private List<string> list_deal = new List<string>();

        private bool endFlag = false;
        private bool dealFlag = false;

        unpackPart unpackGetData(string str)
        {
            unpackPart pacPart = new unpackPart();
            pacPart.pack_id = str.Substring(1, 3);
            pacPart.pack_data_size = str.Substring(4, 7);
            pacPart.pack_data = str.Substring(11, str.Length - 12);
            return pacPart;
        }

        string packData(string strJson,int strjson_id)
        {
            StringBuilder strBuilder = new StringBuilder();
            int id_1 = strjson_id/100;
            int id_2 = (strjson_id % 100) / 10;
            int id_3 = (strjson_id % 100) % 10;
            int data_size = strJson.Length;
            strBuilder.Append("B");
            strBuilder.Append(id_1);
            strBuilder.Append(id_2);
            strBuilder.Append(id_3);
            strBuilder.Append(size2string(data_size));
            strBuilder.Append(strJson);
            strBuilder.Append("E");
            return strBuilder.ToString();
        }

        string size2string(int data_size)
        {
            StringBuilder strBuilder = new StringBuilder();
            int id_1, id_2, id_3, id_4, id_5, id_6, id_7;
            id_7 = data_size / 1000000;
            int id_7_l = data_size % 1000000;
            id_6 = id_7_l / 100000;
            int id_6_l = id_7_l % 100000;
            id_5 = id_6_l / 10000;
            int id_5_l = id_6_l % 10000;
            id_4 = id_5_l / 1000;
            int id_4_l = id_5_l % 1000;
            id_3 = id_4_l / 100;
            int id_3_l = id_4_l % 100;
            id_2 = id_3_l / 10;
            int id_2_l = id_3_l % 10;
            id_1 = id_2_l / 1;

            strBuilder.Append(id_1);
            strBuilder.Append(id_2);
            strBuilder.Append(id_3);
            strBuilder.Append(id_4);
            strBuilder.Append(id_5);
            strBuilder.Append(id_6);
            strBuilder.Append(id_7);

            return strBuilder.ToString();

        }


        // Start is called before the first frame update
        void Start()
        {
            PubTopic = "/" + ProductKey + "/" + DeviceName + Pub;
            SubTopic = "/" + ProductKey + "/" + DeviceName + Sub;
            Run();
            deal_thread = new Thread(deal_process);
            deal_thread.IsBackground = true;
            deal_thread.Start();
        }

        void deal_process()
        {
            while (!endFlag)
            {
                if (dealFlag == true)
                {
                    //Debug.Log("deal_process");
                    StringBuilder strBuilder = new StringBuilder();
                    string B_str = " ";
                    string E_str = " ";
                    string E_left= " ";

                    int B_position = 0;
                    int E_position = 0;

                    int B_str_id = 0;
                    int E_str_id = 0;

                    bool B_find = false;
                    bool E_find = false;
                   // Debug.Log(list_deal.Count);
                    for (int i = 0; i < list_deal.Count; i++)
                    {
                        B_str = list_deal[i];
                        B_position = B_str.IndexOf("B");
                        if (B_position != -1)
                        {
                            B_str_id = i;
                            B_find = true;
                            break;
                        }
                    }

                    if (B_find == true)
                    {
                        for (int i = 0; i < list_deal.Count; i++)
                        {
                            E_str = list_deal[i];
                            E_position = E_str.IndexOf("E");
                            if (E_position != -1)
                            {
                                E_str_id = i;
                                E_find = true;
                                break;
                            }
                        }
                    }

                    //Debug.Log("B_str"+B_str);
                    //Debug.Log("E_str"+E_str);


                    if (E_find == true && B_find == true && E_str_id >=B_str_id)
                    {
                        for (int i = B_str_id; i <= E_str_id; i++)
                        {
                            if (B_str_id == E_str_id)
                            {
                                string part = B_str.Substring(B_position, E_position - B_position + 1);
                                E_left = E_str.Substring(E_position + 1);
                                strBuilder.Append(part);
                            }
                            else
                            {
                                if (i == B_str_id)
                                {
                                    string b_str_part = B_str.Substring(B_position);
                                    strBuilder.Append(b_str_part);
                                }
                                else if (i == E_str_id)
                                {
                                    string e_str_part = E_str.Substring(0, E_position + 1);
                                    E_left = E_str.Substring(E_position + 1);
                                    strBuilder.Append(e_str_part);
                                }
                                else
                                {
                                    strBuilder.Append(list_deal[i]);
                                }
                            }

                        }
                       // Debug.Log("E_str_id" + E_str_id);

                        for (int i = 0; i < E_str_id; i++)
                        {
                            Debug.Log("list_deal.count"+list_deal.Count);
                            list_deal.RemoveAt(i);
                        }

                        if (list_deal.Count == 0)
                        {
                            list_deal.Add(E_left);
                        }
                        else
                        {
                            list_deal.Insert(0, E_left);
                        }
                        
                        string data = strBuilder.ToString();
                      //  Debug.Log(strBuilder.ToString());
                      if (data != "")
                      {
                          unpackPart pack = unpackGetData(data);
                          Debug.Log("unpackPart_data" + pack.pack_data);

                        }
                       
                    }

                    dealFlag = false;

                }
            }

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
            string mqttPassword = IotSignUtils.sign(dict, DeviceSecret, signmethod);
            string mqttClientId = clientId + "|securemode=3,signmethod=" + signmethod + ",timestamp=" + t + "|";

            string targetServer = ProductKey + ".iot-as-mqtt." + RegionId + ".aliyuncs.com";
            Debug.Log("xxxxxxxxxxxx");
            ConnectMqtt(targetServer, mqttClientId, mqttUserName, mqttPassword);
        }
        void ConnectMqtt(string targetServer, string mqttClientId, string mqttUserName,string mqttPassword)
        {
            MqttClient client = new MqttClient(targetServer);
            client.ProtocolVersion = MqttProtocolVersion.Version_3_1_1;
            clientPub = client;
            client.Connect(mqttClientId, mqttUserName, mqttPassword, false, 60);
            client.MqttMsgPublishReceived += Client_MqttMsgPublishReceived;

            //发布消息
            String content = "{'content':'msg from :" + mqttClientId + "hello px4'}";
            var id = client.Publish(PubTopic, Encoding.ASCII.GetBytes(content));

            //订阅消息
            client.Subscribe(new string[] { SubTopic }, new byte[] { 2 });

        }

        void Client_MqttMsgPublishReceived(object sender, MqttMsgPublishEventArgs e)
        {
            //handle message received
            string topic = e.Topic;
            string message = Encoding.ASCII.GetString(e.Message);
           // Debug.Log(message);
            list_recv.Add(message);
            if (dealFlag == false)
            {
                list_deal.AddRange(list_recv);
                list_recv.Clear();
                //list_recv = new List<string>();
                dealFlag = true;
            }


        }

        // Update is called once per frame
        void Update()
        {

        }

        void FixedUpdate()
        {
            if (Input.GetKeyDown(KeyCode.A))
            {
                String data = "74567";
                byte[] data1 = new byte[5];
                data1[0] = 1;
                data1[1] = 2;
                data1[2] = 3;
                data1[3] = 4;
                data1[4] = 5;

                String content = "{'content':'msg from :" + "Unity" + "hello px4'}";

                string data_send = packData(content,222);
                Debug.Log("data_send"+data_send);
                var id = clientPub.Publish(PubTopic, Encoding.ASCII.GetBytes(data_send));
               // var id = clientPub.Publish(PubTopic, data1);
            }
        }

        void OnDestroy()
        {
            endFlag = true;
            if (deal_thread.IsAlive)
            {
                deal_thread.Abort();
            }
        }

    }
}
