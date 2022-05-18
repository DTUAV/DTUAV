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
using System.Threading;
using geometry_msgs;
using Quaternion = UnityEngine.Quaternion;
using Vector3 = UnityEngine.Vector3;

namespace DTUAV.Network_Module.LCM_Network
{
    public class LcmGlobalPositionPub
    {
        private Transform _objecTransform;
        private string _topicName;
        private float _messageFrequency;

        private LCM.LCM.LCM _lcmMessagePub;

        private bool _isRun;
        private Thread _pubThread;
        private int _sleepTime;
        private UnityEngine.Vector3 _globalPosition;
        private UnityEngine.Quaternion _globalRotation;

        private PoseStamp _globalPoseStamp;
        private Vector3 _rosGlobalPosition;
        private Quaternion _rosQuaternion;
        public bool SetTopicName(string name)
        {
            _topicName = name;
            return true;
        }
        public bool SetMessageFrequency(float hz)
        {
            _messageFrequency = hz;
            _sleepTime = (int)((1.0 / _messageFrequency) * 1000);
            return true;
        }
        public bool SetIsRun(bool isRun)
        {
            _isRun = isRun;
            return true;
        }
        private void Run()
        {
            while (_isRun)
            {
                Loom.QueueOnMainThread(() =>
                {
                    _globalPosition = _objecTransform.position;
                    _globalRotation = _objecTransform.rotation;
                });

                _rosGlobalPosition = TF.TF.Unity2Ros(_globalPosition);
                _rosQuaternion = TF.TF.Unity2Ros(_rosQuaternion);

                _globalPoseStamp.orientation.x = _rosQuaternion.x;
                _globalPoseStamp.orientation.y = _rosQuaternion.y;
                _globalPoseStamp.orientation.z = _rosQuaternion.z;
                _globalPoseStamp.orientation.w = _rosQuaternion.w;

                _globalPoseStamp.position.x = _rosGlobalPosition.x;
                _globalPoseStamp.position.y = _rosGlobalPosition.y;
                _globalPoseStamp.position.z = _rosGlobalPosition.z;

                _lcmMessagePub.Publish(_topicName, _globalPoseStamp);
                System.Threading.Thread.Sleep(_sleepTime);
            }

        }
        public LcmGlobalPositionPub(Transform objecTransform,string topicName,float messageFrequency)
        {
            _objecTransform = objecTransform;
            _topicName = topicName;
            _messageFrequency = messageFrequency;

            _lcmMessagePub = LCM.LCM.LCM.Singleton;
            _sleepTime = (int)((1.0 / _messageFrequency) * 1000);
            _isRun = true;

            _globalPosition = new UnityEngine.Vector3();
            _globalRotation = new UnityEngine.Quaternion();

            _rosQuaternion = new Quaternion();
            _rosGlobalPosition = new Vector3();

            _globalPoseStamp = new PoseStamp();
            _globalPoseStamp.orientation = new geometry_msgs.Quaternion();
            _globalPoseStamp.position = new Point();

            Loom.RunAsync(
                () =>
                {
                    _pubThread = new Thread(Run);
                    _pubThread.IsBackground = true;
                    _pubThread.Start();
                }
            );
        }


    }
}
