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
using UnityEngine;
using UnityEngine;
using System.Threading;

namespace RosSharp.RosBridgeClient
{
    public class PoseStampedMsgPub : UnityPublisher<MessageTypes.Geometry.PoseStamped>
    {
        public Transform PublishedTransform;
        public string FrameId = "Unity";
        public float MessageHz;

        private MessageTypes.Geometry.PoseStamped message;
        private Thread _runningThread;
        private int _runningTimes;
        private bool _isStop;
        protected override void Start()
        {
            base.Start();
            InitializeMessage();
            _isStop = false;
            _runningTimes = (int)((1.0 / MessageHz) * 1000);
            Loom.RunAsync(
                () =>
                {
                    _runningThread = new Thread(PublishMsg);
                    _runningThread.IsBackground = true;
                    _runningThread.Start();
                }
            );
            
        }


        private void InitializeMessage()
        {
            message = new MessageTypes.Geometry.PoseStamped
            {
                header = new MessageTypes.Std.Header()
                {
                    frame_id = FrameId
                }
            };
        }

        private void PublishMsg()
        {
            while (!_isStop)
            {
                Loom.QueueOnMainThread(() => { UpdateMessage(); });
                Publish(message);
                System.Threading.Thread.Sleep(_runningTimes);
            }
        }
        private void UpdateMessage()
        {
            message.header.Update();
            GetGeometryPoint(PublishedTransform.position.Unity2Ros(), message.pose.position);
            GetGeometryQuaternion(PublishedTransform.rotation.Unity2Ros(), message.pose.orientation);
        }

        private static void GetGeometryPoint(Vector3 position, MessageTypes.Geometry.Point geometryPoint)
        {
            geometryPoint.x = position.x;
            geometryPoint.y = position.y;
            geometryPoint.z = position.z;
        }

        private static void GetGeometryQuaternion(Quaternion quaternion, MessageTypes.Geometry.Quaternion geometryQuaternion)
        {
            geometryQuaternion.x = quaternion.x;
            geometryQuaternion.y = quaternion.y;
            geometryQuaternion.z = quaternion.z;
            geometryQuaternion.w = quaternion.w;
        }

        void OnDestroy()
        {
            _isStop = true;
        }

    }
}