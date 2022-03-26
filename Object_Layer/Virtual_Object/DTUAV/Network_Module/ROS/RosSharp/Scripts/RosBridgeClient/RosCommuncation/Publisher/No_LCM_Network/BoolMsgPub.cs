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
using System.Threading;
using UnityEngine;

namespace RosSharp.RosBridgeClient
{

    public class BoolMsgPub : UnityPublisher<MessageTypes.Std.Bool>
    {
        public float MessageHz;
        public bool SendData;

        private Thread _pubThread;
        private MessageTypes.Std.Bool _message;
        private int _sleepTime;
        private bool _isPub;
        protected override void Start()
        {
            _isPub = true;
            _sleepTime = (int)((1.0 / MessageHz) * 1000);
            base.Start();
            InitializeMessage();
            _pubThread = new Thread(PubMessage);
            _pubThread.IsBackground = true;
            _pubThread.Start();

        }
        private void InitializeMessage()
        {
            _message = new MessageTypes.Std.Bool();
        }

        void PubMessage()
        {
            while (_isPub)
            {
                _message.data = SendData;
                Publish(_message);
                Thread.Sleep(_sleepTime);
            }
        }


        void OnDestroy()
        {
            _isPub = true;
            if (_pubThread.IsAlive)
            {
                _pubThread.Abort();
            }
        }

    }
}
