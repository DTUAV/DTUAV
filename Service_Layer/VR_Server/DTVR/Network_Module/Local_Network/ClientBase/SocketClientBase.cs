﻿/*
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
namespace DTUAV.Network_Module.Local_Network
{
    public class SocketClientBase
    {
        private string IP;
        private int Port;
        public SocketClientBase(string ip,int port)
        {
            this.IP = ip;
            this.Port = port;
        }

        public Socket ConnectServer()
        {
            Socket socketSend;
            try
            {
                int _port = Port;
                string _ip = IP;
                socketSend = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                IPAddress ip = IPAddress.Parse(_ip);
                IPEndPoint point = new IPEndPoint(ip, _port);
                socketSend.Connect(point);
                Debug.Log("Connection Succeeded!");
                return socketSend;
            }
            catch (Exception)
            {
                Debug.Log("IP or Port error.... Reconnect");
                return null;
            }
        }
    }
}
