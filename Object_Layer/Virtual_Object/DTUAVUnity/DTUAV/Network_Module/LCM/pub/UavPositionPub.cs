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
using LCM;
using geometry_msgs;
using System.Threading;
using DTUAV.Message;
using lcm_iot_msgs;
using Pose = geometry_msgs.Pose;
using Quaternion = UnityEngine.Quaternion;
using Vector3 = UnityEngine.Vector3;
using DTUAV.Time;
using DTUAV.TF;

namespace DTUAV.Network_Module.LCM_Network
{
    public class UavPositionPub : BasePub
    {
        // Start is called before the first frame update
        private int sleepTimeS; //线程休眠的时间，秒为单位
        private Thread pubThread;//发布消息的线程
        private bool isEnd;//线程是否结束
        public Rigidbody RibObject;
        private Vector3 RibPosition;
        private Quaternion RibQuaternion;
        public int TargetID;
        public int SourceID;
        public int MessageID;
        public bool isAutoMessageName = true;
        void Start()
        {
            if (isAutoMessageName)
            {
                this.MesageName = "/" + this.gameObject.transform.parent.name + this.MesageName;
            }
            RibPosition = new Vector3(0, 0, 0);
            RibQuaternion = new Quaternion(0, 0, 0, 1);
            isEnd = false;
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
                DateTime centuryBegin = new DateTime(1970, 1, 1);
                DateTime currentDate = DateTime.Now;
                long elapsedTicks = currentDate.Ticks - centuryBegin.Ticks;
                TimeSpan elapsedSpan = new TimeSpan(elapsedTicks);
                UavLocalPositionMessage localPositionMessage = new UavLocalPositionMessage();
                Vector3 localPositionRos = TF.TF.Unity2Ros(RibPosition);
                localPositionMessage.position_x = localPositionRos.x;
                localPositionMessage.position_y = localPositionRos.y;
                localPositionMessage.position_z = localPositionRos.z;
                Quaternion localQuaternionRos = TF.TF.Unity2Ros(RibQuaternion);
                localPositionMessage.rotation_x = localQuaternionRos.x;
                localPositionMessage.rotation_w = localQuaternionRos.w;
                localPositionMessage.rotation_y = localQuaternionRos.y;
                localPositionMessage.rotation_z = localQuaternionRos.z;
                LcmIotMessage msg = new LcmIotMessage();
                msg.MessageID = MessageID;
                msg.SourceID = SourceID;
                msg.TargetID = TargetID;
                msg.MessageData = JsonUtility.ToJson(localPositionMessage);
                msg.TimeStamp = elapsedSpan.TotalMilliseconds;//返回ms。
               // Debug.Log("msg.TimeStamp: "+ msg.TimeStamp);
                base.BaseLcm.Publish(base.MesageName, msg);
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