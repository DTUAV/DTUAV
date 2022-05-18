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
    public class LcmCurrentVelocityPub
    {
        private Rigidbody _objecRigidbody;
        private string _topicName;
        private float _messageFrequency;

        private LCM.LCM.LCM _lcmMessagePub;

        private bool _isRun;
        private Thread _pubThread;
        private int _sleepTime;
        private Vector3 _globalLinearVelocity;
        private Vector3 _globalRotationVelocity;

        private TwistStamp _twistStamp;

        private Vector3 _rosGlobalLinearVelocity;
        private Vector3 _rosGlobalRotationVelocity;
        
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
                    _globalLinearVelocity = _objecRigidbody.velocity;
                    _globalRotationVelocity = _objecRigidbody.angularVelocity;
                });

                _rosGlobalLinearVelocity = TF.TF.Unity2Ros(_globalLinearVelocity);
                _rosGlobalRotationVelocity = TF.TF.Unity2Ros(_globalRotationVelocity);

                _twistStamp.angular.x = _rosGlobalRotationVelocity.x;
                _twistStamp.angular.y = _rosGlobalRotationVelocity.y;
                _twistStamp.angular.z = _rosGlobalRotationVelocity.z;

                _twistStamp.linear.x = _rosGlobalLinearVelocity.x;
                _twistStamp.linear.y = _rosGlobalLinearVelocity.y;
                _twistStamp.linear.z = _rosGlobalLinearVelocity.z;

                _lcmMessagePub.Publish(_topicName, _twistStamp);
                System.Threading.Thread.Sleep(_sleepTime);
            }

        }
        public LcmCurrentVelocityPub(Rigidbody objecRigidbody, string topicName, float messageFrequency)
        {
            _objecRigidbody = objecRigidbody;
            _topicName = topicName;
            _messageFrequency = messageFrequency;

            _globalLinearVelocity = objecRigidbody.velocity;
            _globalRotationVelocity = objecRigidbody.angularVelocity;

            _lcmMessagePub = LCM.LCM.LCM.Singleton;
            _sleepTime = (int)((1.0 / _messageFrequency) * 1000);
            _isRun = true;

            _rosGlobalLinearVelocity = new Vector3();
            _rosGlobalRotationVelocity = new Vector3();
            
            _twistStamp = new TwistStamp();
            _twistStamp.linear = new geometry_msgs.Vector3();
            _twistStamp.angular = new geometry_msgs.Vector3();

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
