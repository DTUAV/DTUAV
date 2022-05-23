using UnityEngine;
using System.Collections;
using System.Net.Sockets;
using System.Net;
using System.Collections.Generic;
using System.Threading;
using System.Text;
using System.Runtime.InteropServices;

public class ServerFor4G : MonoBehaviour
{
    public string IP = "183.63.119.27";//服务端的IP
    public System.Int32 Port = 9000;//连接的端口
    public bool isOpenSocket = true;
    Socket tcpServer = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
    Thread t_Send;
    Thread t_Read;

    public bool isSend { get; private set; }
    public string messageRead { get; private set; }

    // Start is called before the first frame update
    void Start()
    {
        tcpServer.Bind(new IPEndPoint(IPAddress.Parse(IP), Port));
        Debug.Log("服务端启动完成");
        
        tcpServer.Listen(100);
        
        t_Send = new Thread(SendToClient);
        t_Send.Start();

        t_Read = new Thread(ReadFormClient);
        t_Read.Start();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void SendToClient()
    {
        while (isOpenSocket)
        {
            try
                {
                    byte[] buffer = new byte[5];
                    buffer[0] = 1;
                    buffer[1] = 1;
                    buffer[2] = 1;
                    buffer[3] = 1;
                    buffer[4] = 1;
                    tcpServer.Send(buffer);
                    Debug.Log(buffer[1]);
                }
                catch
                {

                }
               
        }
        t_Send.Abort();
    }

    public void ReadFormClient()
    {
        while (isOpenSocket)
        {
            try
            {
                byte[] buffer = new byte[1024];
                //实际接收到的有效字节数
                int len = tcpServer.Receive(buffer);
                if (len == 0)
                {

                }
                else
                {
                    messageRead = Encoding.UTF8.GetString(buffer, 0, len) + tcpServer.RemoteEndPoint;
                    Debug.Log("get" + messageRead);
                }
              
            }
            catch
            {

            }
        }
        t_Read.Abort();
    }
    void OnDestroy()
    {
        isOpenSocket = false;

    }
}
