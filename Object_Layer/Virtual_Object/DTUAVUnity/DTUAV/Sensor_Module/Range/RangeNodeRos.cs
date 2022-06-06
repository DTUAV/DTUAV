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
using DTUAV.Math.DataNoise;
using RosSharp.RosBridgeClient;
using System.Collections;
using System.Collections.Generic;
using System.Threading;
using UnityEngine;

namespace DTUAV.Sensor_Module.Range
{
    public class RangeNodeRos : UnityPublisher<RosSharp.RosBridgeClient.MessageTypes.Sensor.Range>
    {
        [Header("The Frame ID of Range Message")]
        public string FrameId = "F450";
        [Header("The Minimum Range")] 
        public float MinRange;
        [Header("The Maximum Range")]
        public float MaxRange;
        [Header("The Layer Mask of Ranger Perception")]
        public LayerMask LayerMaskUsing;
        [Header("The Perceived Direction of Ranger")]
        public Vector3 PreDirection = new Vector3(0, -1, 0);
        [Header("The Running Frequency of Ranger")]
        public float RunHz;
        [Header("Is Show")]
        public bool IsShow = false;
        [Header("The Transform of Range Object")]
        public Transform RangeObject;
        [Header("Is Add Noise")]
        public bool IsAddNoise = false;
        private Thread _rangeThread;
        private Range _rangeNode;
        private RosSharp.RosBridgeClient.MessageTypes.Sensor.Range _message;
        private int _sleepTime;
        private bool _isRun;
        private float _curRange;
        protected override void Start()
        {
            base.Start();
            _message = new RosSharp.RosBridgeClient.MessageTypes.Sensor.Range()
            {
                header = new RosSharp.RosBridgeClient.MessageTypes.Std.Header { frame_id = FrameId },
                min_range = MinRange,
                max_range = MaxRange,
                range = 0
            };
            _sleepTime = (int)((1.0 / RunHz) * 1000);
            _isRun = true;
            _rangeNode =new Range(MinRange,MaxRange,LayerMaskUsing,PreDirection,IsShow);

            Loom.RunAsync(
                () =>
                {
                    _rangeThread = new Thread(UpdateSensor);
                    _rangeThread.IsBackground = true;
                    _rangeThread.Start();
                }
            );
        }

        void UpdateSensor()
        {
            while (_isRun)
            {
                Loom.QueueOnMainThread(() =>
                {
                    _curRange = _rangeNode.UpdateSensor(RangeObject.position)+ (float)DataNoise.GaussNiose1() / 100.0f; 

                });
                SendRangeMsg();
                System.Threading.Thread.Sleep(_sleepTime);
            }
        }
        private void SendRangeMsg()
        {
            _message.header.Update();
            _message.range = _curRange;
            Publish(_message);
           
        }
        void OnDestroy()
        {
            _isRun = false;
        }
    }
}
