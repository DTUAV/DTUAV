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
