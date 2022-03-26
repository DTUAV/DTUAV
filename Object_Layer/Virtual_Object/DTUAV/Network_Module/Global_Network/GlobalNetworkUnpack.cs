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

using LCM.LCM;
using lcm_iot_msgs;
using DTUAV.Message;
using geometry_msgs;
using DTUAV.Message;
using DTUAV.Time;
using std_msgs;
using UnityEngine;

namespace DTUAV.Network_Module.Global_Network
{
    public class GlobalNetworkUnpack
    {
        private bool _isGetTargetGlobalPosition;
        private bool _isGetTargetLocalPosition;
        private bool _isGetTargetVelocity;
        private bool _isGetTargetCmdType;

        private int _sourceId;
        private int _targetId;

        private string _targetGlobalPositionTopicName;
        private string _targetLocalPositionTopicName;
        private string _targetVelocityTopicName;
        private string _targetCmdTypeName;

        private string _globalNetworkPubTopicName;

        private LCM.LCM.LCM _lcmTargetLocalPositionPub;
        private LCM.LCM.LCM _lcmTargetGlobalPositionPub;
        private LCM.LCM.LCM _lcmTargetVelocityPub;
        private LCM.LCM.LCM _lcmTargetCmdPub;

        private LCM.LCM.LCM _lcmMessageSub;

        private PoseStamp _localPoseStamp;
        private PoseStamp _globalPoseStamp;
        private TwistStamp _twistStamp;

        private Int16 _cmdInt16;

        private LcmIotMessage _lcmIotMessage;

        public string GetGlobalNetworkPubTopicName()
        {
            return _globalNetworkPubTopicName;
        }
        public string GetTargetVelocityTopicName()
        {
            return _targetVelocityTopicName;
        }
        public string GetTargetLocalPositionTopicName()
        {
            return _targetLocalPositionTopicName;
        }
        public string GetTargetGlobalPositionTopicName()
        {
            return _targetGlobalPositionTopicName;
        }

        public bool SetTargetNetworkPubTopicName(string name)
        {
            _globalNetworkPubTopicName = name;
            return true;
        }
        public bool SetTargetVelocityTopicName(string name)
        {
            _targetVelocityTopicName = name;
            return true;
        }
        public bool SetTargetLocalPositionTopicName(string name)
        {
            _targetLocalPositionTopicName = name;
            return true;
        }
        public bool SetTargetGlobalPositionTopicName(string name)
        {
            _targetGlobalPositionTopicName = name;
            return true;
        }

        public bool GetIsGetTargetVelocity()
        {
            return _isGetTargetVelocity;
        }
        public bool GetIsGetTargetLocalPosition()
        {
            return _isGetTargetLocalPosition;
        }
        public bool GetIsGetTargetGlobalPosition()
        {
            return _isGetTargetGlobalPosition;
        }

        public bool SetIsGetTargetVelocity(bool isSend)
        {
            _isGetTargetVelocity = isSend;
            return true;
        }
        public bool SetIsGetTargetLocalPosition(bool isSend)
        {
            _isGetTargetLocalPosition = isSend;
            return true;
        }
        public bool SetIsGetTargetGlobalPosition(bool isSend)
        {
            _isGetTargetGlobalPosition = isSend;
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

        public bool LcmPublishMessage(LcmIotMessage msg)
        {
            if (msg.TargetID == _targetId&&msg.SourceID == _sourceId)
            {
                switch (msg.MessageID)
                {
                    case MessageId.TargetLocalPositionMsgID:
                        {
                            TargetLocalPositionMsg localPositionMsg =
                                JsonUtility.FromJson<TargetLocalPositionMsg>(msg.MessageData);
                            _localPoseStamp.orientation = new geometry_msgs.Quaternion();
                            _localPoseStamp.position = new Point();
                            _localPoseStamp.orientation.x = localPositionMsg.rotation_x;
                            _localPoseStamp.orientation.y = localPositionMsg.rotation_y;
                            _localPoseStamp.orientation.z = localPositionMsg.rotation_z;
                            _localPoseStamp.orientation.w = localPositionMsg.rotation_w;
                            _localPoseStamp.position.x = localPositionMsg.position_x;
                            _localPoseStamp.position.y = localPositionMsg.position_y;
                            _localPoseStamp.position.z = localPositionMsg.position_z;
                            _localPoseStamp.timestamp = SimTime.GetSystemTimeStampMs();
                            if (_isGetTargetLocalPosition)
                            {
                                _lcmTargetLocalPositionPub.Publish(_targetLocalPositionTopicName, _localPoseStamp);
                            }

                        }
                        break;
                    case MessageId.TargetGlobalPositionMsgID:
                        {
                            //

                        }
                        break;
                    case MessageId.TargetVelocityMsgID:
                        {
                            TargetVelocityMsg velocityMsg = JsonUtility.FromJson<TargetVelocityMsg>(msg.MessageData);

                            _twistStamp.linear = new geometry_msgs.Vector3();
                            _twistStamp.angular = new geometry_msgs.Vector3();
                            _twistStamp.linear.x = velocityMsg.linear_velocity_x;
                            _twistStamp.linear.y = velocityMsg.linear_velocity_y;
                            _twistStamp.linear.z = velocityMsg.linear_velocity_z;
                            _twistStamp.angular.x = velocityMsg.anger_velocity_x;
                            _twistStamp.angular.y = velocityMsg.anger_velocity_y;
                            _twistStamp.angular.z = velocityMsg.anger_velocity_z;
                            _twistStamp.timestamp = SimTime.GetSystemTimeStampMs();
                            if (_isGetTargetVelocity)
                            {
                                _lcmTargetVelocityPub.Publish(_targetVelocityTopicName, _twistStamp);
                            }


                        }
                        break;
                    case MessageId.TargetCmdTypeMsgID:
                        {
                            TargetCmdTypeMsg cmdTypeMsg = JsonUtility.FromJson<TargetCmdTypeMsg>(msg.MessageData);

                            _cmdInt16.data = (short)cmdTypeMsg.type;
                            if (_isGetTargetCmdType)
                            {
                                _lcmTargetCmdPub.Publish(_targetCmdTypeName, _cmdInt16);
                            }

                        }
                        break;
                    default:
                        break;
                }
            }
            return true;
        }

        public GlobalNetworkUnpack(bool isGetTargetGlobalPosition, bool isGetTargetLocalPosition, bool isGetTargetVelocity, bool isGetTargetCmdType,string targetGlobalPositionTopicName, string targetLocalPositionTopicName, string targetVelocityTopicName, string globalNetworkPubTopicName,string targetCmdTypeName, int sourceId, int targetId)
        {
            _isGetTargetGlobalPosition = isGetTargetGlobalPosition;
            _isGetTargetLocalPosition = isGetTargetLocalPosition;
            _isGetTargetVelocity = isGetTargetVelocity;
            _isGetTargetCmdType = isGetTargetCmdType;

            _targetGlobalPositionTopicName = targetGlobalPositionTopicName;
            _targetLocalPositionTopicName = targetLocalPositionTopicName;
            _targetVelocityTopicName = targetVelocityTopicName;
            _globalNetworkPubTopicName = globalNetworkPubTopicName;
            _targetCmdTypeName = targetCmdTypeName;

            _sourceId = sourceId;
            _targetId = targetId;

            _lcmTargetGlobalPositionPub = LCM.LCM.LCM.Singleton;
            
            _lcmTargetLocalPositionPub = LCM.LCM.LCM.Singleton;
            
            _lcmTargetVelocityPub = LCM.LCM.LCM.Singleton;

            _lcmTargetCmdPub = LCM.LCM.LCM.Singleton;

            _twistStamp = new TwistStamp();
            _twistStamp.linear = new geometry_msgs.Vector3();
            _twistStamp.angular = new geometry_msgs.Vector3();

            _localPoseStamp = new PoseStamp();
            _localPoseStamp.orientation = new geometry_msgs.Quaternion();
            _localPoseStamp.position = new Point();

            _globalPoseStamp = new PoseStamp();
            _globalPoseStamp.orientation = new geometry_msgs.Quaternion();
            _globalPoseStamp.position = new Point();

            _cmdInt16 = new Int16();

            _lcmMessageSub = new LCM.LCM.LCM();
            _lcmMessageSub.Subscribe(_globalNetworkPubTopicName, new LcmIotMessageSubscriber(this));
            _lcmIotMessage = new LcmIotMessage();
        }


        internal class LcmIotMessageSubscriber : LCMSubscriber
        {
            private GlobalNetworkUnpack _globalNetworkUnpack;

            public LcmIotMessageSubscriber(GlobalNetworkUnpack globalNetworkUnpack)
            {
                _globalNetworkUnpack = globalNetworkUnpack;
            }

            public void MessageReceived(LCM.LCM.LCM lcm, string channel, LCMDataInputStream ins)
            {
                LcmIotMessage iotMessage = new LcmIotMessage(ins);
                _globalNetworkUnpack.LcmPublishMessage(iotMessage);
            }
        }

      

    }
}
