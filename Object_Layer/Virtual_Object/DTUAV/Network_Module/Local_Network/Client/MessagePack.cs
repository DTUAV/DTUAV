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
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using LCM;
using geometry_msgs;
using System.Threading;
using Pose = geometry_msgs.Pose;
using Quaternion = UnityEngine.Quaternion;
using Vector3 = UnityEngine.Vector3;
using lcm_iot_msgs;
using DTUAV.Message;
using DTUAV.Network_Module.LCM_Network;
namespace DTUAV.Network_Module.Local_Network
{
    public class MessagePack : BasePub
    {
        // Start is called before the first frame update
        private int sleepTimeS; 
        private Thread pubThread;
        private bool isEnd;
        private PoseStamp poseMsg;
        public Rigidbody RibObject;
        private Vector3 RibPosition;
        private Quaternion RibQuaternion;
        void Start()
        {
            RibPosition = new Vector3(0, 0, 0);
            RibQuaternion = new Quaternion(0, 0, 0, 1);
            isEnd = false;
            poseMsg = new PoseStamp();
            poseMsg.position = new Point();
            poseMsg.orientation = new geometry_msgs.Quaternion();
            base.BaseStart();
            sleepTimeS = (int)((1 / (base.MessagePubHz)) * 1000);
            pubThread = new Thread(PubData);
            pubThread.IsBackground = true;//线程才会随着主线程的退出而退出
            pubThread.Start();
        }

        void Update()
        {
            RibPosition = RibObject.position;
            RibQuaternion = RibObject.rotation;
        }
        void PubData()
        {
            while (!isEnd)
            {
                DateTime centuryBegin = new DateTime(2001, 1, 1);
                DateTime currentDate = DateTime.Now;

                long elapsedTicks = currentDate.Ticks - centuryBegin.Ticks;
                TimeSpan elapsedSpan = new TimeSpan(elapsedTicks);
                CurrentPoseMessage cureCurrentPoseMessage = new CurrentPoseMessage();
                LcmIotMessage msg = new LcmIotMessage();
                msg.TargetID = 1;
                msg.SourceID = 201;
                msg.MessageID = 1;
                msg.TimeStamp = elapsedSpan.TotalMilliseconds;
                cureCurrentPoseMessage.PositionX = RibPosition.x;
                cureCurrentPoseMessage.PositionY = RibPosition.y;
                cureCurrentPoseMessage.PositionZ = RibPosition.z;
                cureCurrentPoseMessage.RotationW = RibQuaternion.w;
                cureCurrentPoseMessage.RotationX = RibQuaternion.x;
                cureCurrentPoseMessage.RotationY = RibQuaternion.y;
                cureCurrentPoseMessage.RotationZ = RibQuaternion.z;
                msg.MessageData = JsonUtility.ToJson(cureCurrentPoseMessage);
                base.BaseLcm.Publish(base.MesageName, msg);
                // Debug.Log("send"+elapsedSpan.TotalSeconds);
                System.Threading.Thread.Sleep(sleepTimeS);
            }
        }

        void OnDestroy()
        {
            isEnd = true;
            if (pubThread != null)
            {
                if (pubThread.IsAlive)
                {
                    pubThread.Abort();
                }
            }
        }
    }
}