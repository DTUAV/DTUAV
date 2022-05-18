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
    public class LcmLocalPositionPub
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

        private Vector3 _initPosition;
        private UnityEngine.Quaternion _initRotation;

        private PoseStamp _localPoseStamp;

        private Quaternion _localQuaternion;

        private Vector3 _localAngle;

        private Vector3 _rosLocalPosition;
        private UnityEngine.Quaternion _rosQuaternion;
        public Vector3 GetInitPosition()
        {
            return _initPosition;
        }

        public bool SetInitPosition(Vector3 pos)
        {
            _initPosition = pos;
            return true;
        }
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

                _localAngle = _globalRotation.eulerAngles - _initRotation.eulerAngles;
                _localQuaternion = Quaternion.Euler(_localAngle);

                _rosQuaternion = TF.TF.Unity2Ros(_localQuaternion);
                _rosLocalPosition = TF.TF.Unity2Ros(_globalPosition - _initPosition);


                _localPoseStamp.orientation.x = _rosQuaternion.x;
                _localPoseStamp.orientation.y = _rosQuaternion.y;
                _localPoseStamp.orientation.z = _rosQuaternion.z;
                _localPoseStamp.orientation.w = _rosQuaternion.w;

                _localPoseStamp.position.x = _rosLocalPosition.x;
                _localPoseStamp.position.y = _rosLocalPosition.y;
                _localPoseStamp.position.z = _rosLocalPosition.z;

                _lcmMessagePub.Publish(_topicName, _localPoseStamp);
                System.Threading.Thread.Sleep(_sleepTime);
            }

        }
        public LcmLocalPositionPub(Transform objecTransform, string topicName, float messageFrequency)
        {
            _objecTransform = objecTransform;
            _topicName = topicName;
            _messageFrequency = messageFrequency;
            _initPosition = objecTransform.position;
            _initRotation = objecTransform.rotation;

            _globalPosition = _objecTransform.position;
            _localQuaternion = objecTransform.rotation;

            _lcmMessagePub = LCM.LCM.LCM.Singleton;
            _sleepTime = (int)((1.0 / _messageFrequency) * 1000);
            _isRun = true;

            _globalPosition = new UnityEngine.Vector3();
            _globalRotation = new UnityEngine.Quaternion();

            _rosQuaternion = new UnityEngine.Quaternion();
            _rosLocalPosition = new Vector3();

            _localQuaternion = new Quaternion();
            _localAngle = new Vector3();

            _localPoseStamp = new PoseStamp();
            _localPoseStamp.orientation = new geometry_msgs.Quaternion();
            _localPoseStamp.position = new Point();

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
