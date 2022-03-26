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
