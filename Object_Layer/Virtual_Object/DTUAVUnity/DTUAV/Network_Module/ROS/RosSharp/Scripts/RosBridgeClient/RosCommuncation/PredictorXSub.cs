using RosSharp.RosBridgeClient.MessageTypes.Std;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace RosSharp.RosBridgeClient
{
    public class PredictorXSub : UnitySubscriber<MessageTypes.Std.Float64MultiArray>
    {
        public int predictedWindow;
        public double[] data;
        protected override void ReceiveMessage(Float64MultiArray message)
        {
            // throw new System.NotImplementedException();
            data = message.data;
        }

        protected override void Start()
        {
            base.Start();
            data = new double[predictedWindow];
            for (int i = 0; i < predictedWindow; i++)
            {
                data[i] = 0;
            }
        }
    }
}