using System.Collections;
using System.Collections.Generic;
using System.Threading;
using geometry_msgs;
using LCM.LCM;
using UnityEngine;
namespace RosSharp.RosBridgeClient
{
    public class PoseStampedMsgLcmPub : UnityPublisher<MessageTypes.Geometry.PoseStamped>, LCMSubscriber
    {
        public string _lcmSubTopicName;

        private MessageTypes.Geometry.PoseStamped _message;
        private geometry_msgs.PoseStamp _lcmSubMessage;
        private LCM.LCM.LCM _lcmMessageSub;

        protected override void Start()
        {
            _lcmMessageSub = new LCM.LCM.LCM();
            _lcmMessageSub.Subscribe(_lcmSubTopicName, this);
            base.Start();
            InitializeMessage();
        }


        private void InitializeMessage()
        {
            _message = new MessageTypes.Geometry.PoseStamped
            {
                header = new MessageTypes.Std.Header()
                {
                    frame_id = "Unity"
                }
            };
        }

        public void MessageReceived(LCM.LCM.LCM lcm, string channel, LCMDataInputStream ins)
        {
            if (channel == _lcmSubTopicName)
            {
                _lcmSubMessage = new PoseStamp(ins);
                _message.pose.position.x = _lcmSubMessage.position.x;
                _message.pose.position.y = _lcmSubMessage.position.y;
                _message.pose.position.z = _lcmSubMessage.position.z;
                _message.pose.orientation.x = _lcmSubMessage.orientation.x;
                _message.pose.orientation.y = _lcmSubMessage.orientation.y;
                _message.pose.orientation.z = _lcmSubMessage.orientation.z;
                _message.pose.orientation.w = _lcmSubMessage.orientation.w;
                _message.header.Update();
                Publish(_message);
            }

            
        }
    }
}