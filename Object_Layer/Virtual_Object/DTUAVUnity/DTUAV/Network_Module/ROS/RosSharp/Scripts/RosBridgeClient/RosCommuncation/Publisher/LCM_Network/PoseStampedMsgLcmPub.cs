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
using System.Collections;
using System.Collections.Generic;
using System.Threading;
using geometry_msgs;
using LCM.LCM;
using UnityEngine;
namespace RosSharp.RosBridgeClient
{
    public class PoseStampedMsgLcmPub : UnityPublisher<MessageTypes.Geometry.PoseStamped>, LCMSubscriber
    {
        public string _lcmSubTopicName;

        private MessageTypes.Geometry.PoseStamped _message;
        private geometry_msgs.PoseStamp _lcmSubMessage;
        private LCM.LCM.LCM _lcmMessageSub;

        protected override void Start()
        {
            _lcmMessageSub = new LCM.LCM.LCM();
            _lcmMessageSub.Subscribe(_lcmSubTopicName, this);
            base.Start();
            InitializeMessage();
        }


        private void InitializeMessage()
        {
            _message = new MessageTypes.Geometry.PoseStamped
            {
                header = new MessageTypes.Std.Header()
                {
                    frame_id = "Unity"
                }
            };
        }

        public void MessageReceived(LCM.LCM.LCM lcm, string channel, LCMDataInputStream ins)
        {
            if (channel == _lcmSubTopicName)
            {
                _lcmSubMessage = new PoseStamp(ins);
                _message.pose.position.x = _lcmSubMessage.position.x;
                _message.pose.position.y = _lcmSubMessage.position.y;
                _message.pose.position.z = _lcmSubMessage.position.z;
                _message.pose.orientation.x = _lcmSubMessage.orientation.x;
                _message.pose.orientation.y = _lcmSubMessage.orientation.y;
                _message.pose.orientation.z = _lcmSubMessage.orientation.z;
                _message.pose.orientation.w = _lcmSubMessage.orientation.w;
                _message.header.Update();
                Publish(_message);
            }

            
        }
    }
}