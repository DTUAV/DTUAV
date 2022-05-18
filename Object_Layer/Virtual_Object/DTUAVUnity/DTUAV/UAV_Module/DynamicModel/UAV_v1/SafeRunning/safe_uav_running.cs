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
using RosSharp.RosBridgeClient.MessageTypes.Std;
using UnityEngine;
using DTUAV.UAV_Module.droneV2;

namespace RosSharp.RosBridgeClient
{
    public class safe_uav_running : UnityPublisher<MessageTypes.Std.Int8MultiArray>
    {
        public GameObject Uav;//无人机对象
        public float FixedUpdateTime;//FixedUpdate函数运行时间间隔
        public float MsgPubHz;//碰撞检测的频率
        public DroneV2XYZControl UavControl;//无人机控制脚本
        public get_collision GetCollisionState;//碰撞检测脚本
        public bool IsCheckDownCollision = false;//是否开启无人机底部避障
        [HideInInspector]
        public bool IsWillCollision = false;
        [HideInInspector]
        public bool isUpCollision = false;
        [HideInInspector]
        public bool isDownCollision = false;
        [HideInInspector]
        public bool isRightCollision = false;
        [HideInInspector]
        public bool isLeftCollision = false;
        [HideInInspector]
        public bool isForwardCollision = false;
        [HideInInspector]
        public bool isBackCollision = false;
        [HideInInspector]
        public Vector3 UavCurrentPosition;//碰撞时无人机的位置
        private MessageTypes.Std.Int8MultiArray _checkCollisionMsg;//碰撞检测消息
        private int _updateTime;//Fixedupdate需要运行多少次
        private int _index;//更新索引

        protected override void Start()
        {
            _updateTime = Mathf.RoundToInt((1 / MsgPubHz) / FixedUpdateTime);//计算需要等待几次
            _index = 0;//初始化索引值
            base.Start();
            _checkCollisionMsg = new Int8MultiArray()//初始化消息
            {
                layout = new MultiArrayLayout(),
                data = new sbyte[6]
            };
        }

        private void FixedUpdate()//固定FixedTime间隔调用，在Unity界面可设置
        {
            if (_index < _updateTime)//没有到发布的频率，更新索引值
            {
                _index = _index + 1;
            }
            else//一旦到发布频率，进行碰撞检测并发布消息
            {
                _index = 0;
                isUpCollision = GetCollisionState.CheckUpCollision();
                isDownCollision = GetCollisionState.CheckDownCollision();
                isRightCollision = GetCollisionState.CheckRightCollision();
                isLeftCollision = GetCollisionState.CheckLeftCollision();
                isForwardCollision = GetCollisionState.CheckForwardCollision();
                isBackCollision = GetCollisionState.CheckBackCollision();
                if (!IsCheckDownCollision)
                {
                    isDownCollision = false;
                }

                _checkCollisionMsg.data[0] = (sbyte)(isUpCollision ? 1 : 0);
                _checkCollisionMsg.data[1] = (sbyte)(isDownCollision ? 1 : 0);
                _checkCollisionMsg.data[2] = (sbyte)(isRightCollision ? 1 : 0);
                _checkCollisionMsg.data[3] = (sbyte)(isLeftCollision ? 1 : 0);
                _checkCollisionMsg.data[4] = (sbyte)(isForwardCollision ? 1 : 0);
                _checkCollisionMsg.data[5] = (sbyte)(isBackCollision ? 1 : 0);
                if (isBackCollision || isDownCollision || isForwardCollision || isLeftCollision || isRightCollision ||
                    isUpCollision)
                {
                    IsWillCollision = true;
                   // UavControl.uavPosition_x = Uav.transform.position.x;
                   // UavControl.uavPosition_y = Uav.transform.position.y;
                   // UavControl.uavPosition_z = Uav.transform.position.z;
                    UavCurrentPosition.x = Uav.transform.position.x;
                    UavCurrentPosition.y = Uav.transform.position.y;
                    UavCurrentPosition.z = Uav.transform.position.z;
                }
                else
                {
                    IsWillCollision = false;
                }
                Publish(_checkCollisionMsg);
            }
        }
    }
}
