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

using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using LCM.LCM;
using lcm_iot_msgs;
using DTUAV.Message;
using geometry_msgs;
using DTUAV.Time;
using UnityEditor;
using UnityEditor.Experimental.GraphView;

namespace DTUAV.Network_Module.Local_Network
{
    public class LocalNetworkPack
    {
        private bool _isSendGlobalPosition;
        private bool _isSendLocalPosition;
        private bool _isSendVelocity;

        private int _sourceId;
        private int _targetId;

        private string _globalPositionTopicName;
        private string _localPositionTopicName;
        private string _velocityTopicName;
        private string _globalNetworkSubTopicName;

        private LCM.LCM.LCM _lcmLocalPositionSub;
        private LCM.LCM.LCM _lcmGlobalPositionSub;
        private LCM.LCM.LCM _lcmVelocitySub;

        private LCM.LCM.LCM _lcmMessagePub;
        private LcmIotMessage _lcmIotMessage;

        public string GetGlobalNetworkSubTopicName()
        {
            return _globalNetworkSubTopicName;
        }
        public string GetVelocityTopicName()
        {
            return _velocityTopicName;
        }
        public string GetLocalPositionTopicName()
        {
            return _localPositionTopicName;
        }
        public string GetGlobalPositionTopicName()
        {
            return _globalPositionTopicName;
        }

        public bool SetGlobalNetworkSubTopicName(string name)
        {
            _globalPositionTopicName = name;
            return true;
        }
        public bool SetVelocityTopicName(string name)
        {
            _velocityTopicName = name;
            return true;
        }
        public bool SetLocalPositionTopicName(string name)
        {
            _localPositionTopicName = name;
            return true;
        }
        public bool SetGlobalPositionTopicName(string name)
        {
            _globalPositionTopicName = name;
            return true;
        }

        public bool GetIsSendVelocity()
        {
            return _isSendVelocity;
        }
        public bool GetIsSendLocalPosition()
        {
            return _isSendLocalPosition;
        }
        public bool GetIsSendGlobalPosition()
        {
            return _isSendGlobalPosition;
        }

        public bool SetIsSendVelocity(bool isSend)
        {
            _isSendVelocity = isSend;
            return true;
        }
        public bool SetIsSendLocalPosition(bool isSend)
        {
            _isSendLocalPosition = isSend;
            return true;
        }
        public bool SetIsSendGlobalPosition(bool isSend)
        {
            _isSendGlobalPosition = isSend;
            return true;
        }

        public int GetTargetId()
        {
            return _targetId;
        }
        public int GetSourceId()
        {
            return _sourceId;
        }

        public bool SetSourceId(int sourceId)
        {
            _sourceId = sourceId;
            return true;
        }

        public bool SetTargetId(int targetId)
        {
            _targetId = targetId;
            return true;
        }

        public LcmIotMessage getLcmIotMessage()
        {
            return _lcmIotMessage;
        }
        public bool LcmPublishMessage(string messageData,int messageId)
        {
            if (_isSendGlobalPosition && messageId == MessageId.CurrentUnityGlobalPositionMsgID)
            {
                _lcmIotMessage.SourceID = _sourceId;
                _lcmIotMessage.TargetID = _targetId;
                _lcmIotMessage.MessageData = messageData;
                _lcmIotMessage.MessageID = messageId;
                _lcmIotMessage.TimeStamp = SimTime.GetSystemTimeStampMs();
                try
                {
                    _lcmMessagePub.Publish(_globalNetworkSubTopicName, _lcmIotMessage);
                    return true;
                }
                catch (Exception e)
                {
                    Console.WriteLine(e);
                    return false;
                }
            }
            else if (_isSendLocalPosition && messageId == MessageId.CurrentLocalPositionMsgID)
            {
                _lcmIotMessage.SourceID = _sourceId;
                _lcmIotMessage.TargetID = _targetId;
                _lcmIotMessage.MessageData = messageData;
                _lcmIotMessage.MessageID = messageId;
                _lcmIotMessage.TimeStamp = SimTime.GetSystemTimeStampMs();
                try
                {
                    _lcmMessagePub.Publish(_globalNetworkSubTopicName, _lcmIotMessage);
                    return true;
                }
                catch (Exception e)
                {
                    Console.WriteLine(e);
                    return false;
                }
            }
            else if (_isSendVelocity && messageId == MessageId.CurrentVelocityMsgID)
            {
                _lcmIotMessage.SourceID = _sourceId;
                _lcmIotMessage.TargetID = _targetId;
                _lcmIotMessage.MessageData = messageData;
                _lcmIotMessage.MessageID = messageId;
                _lcmIotMessage.TimeStamp = SimTime.GetSystemTimeStampMs();
                try
                {
                    _lcmMessagePub.Publish(_globalNetworkSubTopicName, _lcmIotMessage);
                    return true;
                }
                catch (Exception e)
                {
                    Console.WriteLine(e);
                    return false;
                }
            }
            else
            {
                return false;
            }


        }

        public LocalNetworkPack(bool isSendGlobalPosition,bool isSendLocalPosition,bool isSendVelocity,string globalPositionTopicName,string localPositionTopicName,string velocityTopicName,string globalNetworkSubTopicName,int sourceId,int targetId)
        {
            _isSendGlobalPosition = isSendGlobalPosition;
            _isSendLocalPosition = isSendLocalPosition;
            _isSendVelocity = isSendVelocity;
            _globalPositionTopicName = globalPositionTopicName;
            _localPositionTopicName = localPositionTopicName;
            _velocityTopicName = velocityTopicName;
            _globalNetworkSubTopicName = globalNetworkSubTopicName;

            _sourceId = sourceId;
            _targetId = targetId;

            _lcmGlobalPositionSub = new LCM.LCM.LCM();
            _lcmGlobalPositionSub.Subscribe(_globalPositionTopicName, new GlobalPositionSubscriber(this));

            _lcmLocalPositionSub = new LCM.LCM.LCM();
            _lcmLocalPositionSub.Subscribe(_localPositionTopicName, new LocalPositionSubscriber(this));

            _lcmVelocitySub = new LCM.LCM.LCM();
            _lcmVelocitySub.Subscribe(_velocityTopicName, new VelocitySubscriber(this));

            _lcmMessagePub = LCM.LCM.LCM.Singleton;
            _lcmIotMessage = new LcmIotMessage();
        }



        internal class GlobalPositionSubscriber : LCMSubscriber
        {
            private LocalNetworkPack _globalNetworkPack;
            public GlobalPositionSubscriber(LocalNetworkPack globalNetworkPack)
            {
                _globalNetworkPack = globalNetworkPack;
            }
            public void MessageReceived(LCM.LCM.LCM lcm, string channel, LCM.LCM.LCMDataInputStream dins)
            {
                PoseStamp globalPose = new PoseStamp(dins);
                CurrentLocalPositionMsg globalPositionMsg  = new CurrentLocalPositionMsg();
                globalPositionMsg.position_x = globalPose.position.x;
                globalPositionMsg.position_y = globalPose.position.y;
                globalPositionMsg.position_z = globalPose.position.z;
                globalPositionMsg.rotation_x = globalPose.orientation.x;
                globalPositionMsg.rotation_y = globalPose.orientation.y;
                globalPositionMsg.rotation_z = globalPose.orientation.z;
                globalPositionMsg.rotation_w = globalPose.orientation.w;

                string messageData = JsonUtility.ToJson(globalPositionMsg);
                _globalNetworkPack.LcmPublishMessage(messageData, MessageId.CurrentUnityGlobalPositionMsgID);
            }
        }

        internal class LocalPositionSubscriber : LCMSubscriber
        {
            private LocalNetworkPack _globalNetworkPack;
            public LocalPositionSubscriber(LocalNetworkPack globalNetworkPack)
            {
                _globalNetworkPack = globalNetworkPack;
            }
            public void MessageReceived(LCM.LCM.LCM lcm, string channel, LCM.LCM.LCMDataInputStream dins)
            {

                PoseStamp localPose = new PoseStamp(dins);
                CurrentLocalPositionMsg localPositionMsg = new CurrentLocalPositionMsg();
                localPositionMsg.position_x = localPose.position.x;
                localPositionMsg.position_y = localPose.position.y;
                localPositionMsg.position_z = localPose.position.z;
                localPositionMsg.rotation_x = localPose.orientation.x;
                localPositionMsg.rotation_y = localPose.orientation.y;
                localPositionMsg.rotation_z = localPose.orientation.z;
                localPositionMsg.rotation_w = localPose.orientation.w;

                string messageData = JsonUtility.ToJson(localPositionMsg);
                _globalNetworkPack.LcmPublishMessage(messageData, MessageId.CurrentLocalPositionMsgID);

            }
        }

        internal class VelocitySubscriber : LCMSubscriber
        {
            private LocalNetworkPack _globalNetworkPack;
            public VelocitySubscriber(LocalNetworkPack globalNetworkPack)
            {
                _globalNetworkPack = globalNetworkPack;
            }
            public void MessageReceived(LCM.LCM.LCM lcm, string channel, LCM.LCM.LCMDataInputStream dins)
            {
                TwistStamp currentVelocity = new TwistStamp(dins);
                CurrentVelocityMsg velocityMsg = new CurrentVelocityMsg();
                velocityMsg.linear_velocity_x = currentVelocity.linear.x;
                velocityMsg.linear_velocity_y = currentVelocity.linear.y;
                velocityMsg.linear_velocity_z = currentVelocity.linear.z;
                velocityMsg.anger_velocity_x = currentVelocity.angular.x;
                velocityMsg.anger_velocity_y = currentVelocity.angular.y;
                velocityMsg.anger_velocity_z = currentVelocity.angular.z;
                string messageData = JsonUtility.ToJson(velocityMsg);
                _globalNetworkPack.LcmPublishMessage(messageData, MessageId.CurrentVelocityMsgID);

            }
        }

    }
}
