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
using Pose = geometry_msgs.Pose;
using Quaternion = UnityEngine.Quaternion;
using Vector3 = UnityEngine.Vector3;

namespace DTUAV.Network_Module.LCM_Network
{
    public class PosePub : BasePub
    {
        // Start is called before the first frame update
        private int sleepTimeS; //线程休眠的时间，秒为单位
        private Thread pubThread;//发布消息的线程
        private bool isEnd;//线程是否结束
        private PoseStamp poseMsg;
        public Rigidbody RibObject;
        private Vector3 RibPosition;
        private Quaternion RibQuaternion;
        void Start()
        {
            RibPosition = new Vector3(0,0,0);
            RibQuaternion = new Quaternion(0,0,0,1);
            isEnd = false;
            poseMsg = new PoseStamp();
            poseMsg.position = new Point();
            poseMsg.orientation = new geometry_msgs.Quaternion();
            base.BaseStart();
            sleepTimeS = (int)(1 / (base.MessagePubHz)) * 1000;
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
                poseMsg.timestamp = elapsedSpan.TotalMilliseconds;//返回ms。
                poseMsg.position.x = RibPosition.x;
                poseMsg.position.y = RibPosition.y;
                poseMsg.position.z = RibPosition.z;
                poseMsg.orientation.x = RibQuaternion.x;
                poseMsg.orientation.y = RibQuaternion.y;
                poseMsg.orientation.z = RibQuaternion.z;
                poseMsg.orientation.w = RibQuaternion.w;
                base.BaseLcm.Publish(base.MesageName,poseMsg);
                System.Threading.Thread.Sleep(sleepTimeS);
            }
        }

        void OnDestroy()
        {
            isEnd = true;
            if (pubThread!=null)
            {
                if (pubThread.IsAlive)
                {
                    pubThread.Abort();
                }
            }
        }
    }
}