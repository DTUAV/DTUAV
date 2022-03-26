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

namespace RosSharp.RosBridgeClient
{
    public class BoolMsgSub : UnitySubscriber<MessageTypes.Std.Bool>
    {
        public bool RecvData;
        protected override void ReceiveMessage(MessageTypes.Std.Bool message)
        {
            RecvData = message.data;
        }

        protected override void Start()
        {
            base.Start();
        }
    }
}
