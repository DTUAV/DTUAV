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
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using std_msgs;

namespace RosSharp.RosBridgeClient
{
    public class BoolMsgLcmSub : UnitySubscriber<MessageTypes.Std.Bool>
    {
        public string _lcmMessageTopicName;
        private std_msgs.Bool _lcmMessage;
        private LCM.LCM.LCM _lcmMessagePub;
        protected override void ReceiveMessage(MessageTypes.Std.Bool message)
        {
            _lcmMessage.data = message.data;
            _lcmMessagePub.Publish(_lcmMessageTopicName,_lcmMessage);
        }

        protected override void Start()
        {
            _lcmMessagePub = LCM.LCM.LCM.Singleton;
            _lcmMessage = new Bool();
            base.Start();
        }
    }
}
