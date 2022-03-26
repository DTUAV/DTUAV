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