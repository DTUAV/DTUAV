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
