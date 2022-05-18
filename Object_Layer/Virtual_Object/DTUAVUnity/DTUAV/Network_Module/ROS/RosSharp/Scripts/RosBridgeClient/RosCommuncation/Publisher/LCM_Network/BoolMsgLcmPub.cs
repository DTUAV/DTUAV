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
using System.Threading;
using LCM.LCM;
using UnityEngine;
using std_msgs;

namespace RosSharp.RosBridgeClient
{

    public class BoolMsgLcmPub : UnityPublisher<MessageTypes.Std.Bool>, LCMSubscriber
    {
        public string _lcmSubTopicName;

        private MessageTypes.Std.Bool _message;
        private std_msgs.Bool _lcmSubMessage;
        private LCM.LCM.LCM _lcmMessageSub;
        public void MessageReceived(LCM.LCM.LCM lcm, string channel, LCMDataInputStream ins)
        {
            if (channel == _lcmSubTopicName)
            {
                _lcmSubMessage = new Bool(ins);
                _message.data = _lcmSubMessage.data;
                Publish(_message);
            }
        }
        protected override void Start()
        {
            _lcmMessageSub = new LCM.LCM.LCM();
            _lcmMessageSub.Subscribe(_lcmSubTopicName, this);
            base.Start();
            InitializeMessage();

        }
        private void InitializeMessage()
        {
            _message = new MessageTypes.Std.Bool();
        }
    }
}