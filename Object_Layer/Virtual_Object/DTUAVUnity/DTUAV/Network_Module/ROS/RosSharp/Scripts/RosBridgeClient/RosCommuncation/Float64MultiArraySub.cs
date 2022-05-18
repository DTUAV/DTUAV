using RosSharp.RosBridgeClient.MessageTypes.Std;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace RosSharp.RosBridgeClient
{
    public class Float64MultiArraySub : UnitySubscriber<MessageTypes.Std.Float64MultiArray>
    {
        public double[] data;
        protected override void ReceiveMessage(Float64MultiArray message)
        {
            // throw new System.NotImplementedException();
            data = message.data;
        }
    }
}