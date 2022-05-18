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
using LCM.LCM;
using System.Collections;
using System.Collections.Generic;
using DTUAV.Message;
using DTUAV.UAV_Module.Quadrotor;
using lcm_iot_msgs;
using UnityEngine;

namespace DTUAV.VR
{
    public class VRControlWrapper : MonoBehaviour, LCM.LCM.LCMSubscriber
    {
        private bool _isVRControl;
        public string TopicName;
        public bool IsPositionControl = true;
        public PositionControl PositionControlNode;
        public bool IsVelocityControl = false;
        public MotionWithVelocityNode VelocityControlNode;
        private LCM.LCM.LCM SubLcm;
        public void MessageReceived(LCM.LCM.LCM lcm, string channel, LCMDataInputStream ins)
        {
            lcm_iot_msgs.LcmIotMessage msg = new lcm_iot_msgs.LcmIotMessage(ins);
            if (msg.SourceID == ObjectId.VR_0)
            {
                switch (msg.MessageID)
                {
                    case MessageId.ControlApplyMsgID:
                    {
                        ControlApplyMsg applyMsg = JsonUtility.FromJson<ControlApplyMsg>(msg.MessageData);
                        _isVRControl = applyMsg.apply_info;
                    }
                        break;
                    case MessageId.TargetLocalPositionMsgID:
                    {
                        if (_isVRControl)
                        {
                            TargetLocalPositionMsg targetPosition =
                                JsonUtility.FromJson<TargetLocalPositionMsg>(msg.MessageData);
                            PositionControlNode.RefLocalPoseRos.x = (float)targetPosition.position_x;
                            PositionControlNode.RefLocalPoseRos.y = (float)targetPosition.position_y;
                            PositionControlNode.RefLocalPoseRos.z = (float)targetPosition.position_z;
                            Quaternion rotation = new Quaternion((float)targetPosition.rotation_x, (float)targetPosition.rotation_y, (float)targetPosition.rotation_z, (float)targetPosition.rotation_w);
                            PositionControlNode.RefRotationRos.x = rotation.eulerAngles.x;
                            PositionControlNode.RefRotationRos.y = rotation.eulerAngles.y;
                            PositionControlNode.RefRotationRos.z = rotation.eulerAngles.z;
                        }
                    }
                        break;
                    case MessageId.TargetVelocityMsgID:
                    {
                        if (_isVRControl)
                        {
                            TargetVelocityMsg targetVelocity = JsonUtility.FromJson<TargetVelocityMsg>(msg.MessageData);
                            VelocityControlNode.targetVelocity.x = (float)targetVelocity.linear_velocity_x;
                            VelocityControlNode.targetVelocity.y = (float)targetVelocity.linear_velocity_y;
                            VelocityControlNode.targetVelocity.z = (float)targetVelocity.linear_velocity_z;

                        }
                    }
                        break;
                }
            }
        }

        // Start is called before the first frame update
        void Start()
        {
            SubLcm = new LCM.LCM.LCM();
            SubLcm.Subscribe(TopicName, this);
            if (IsPositionControl&&IsVelocityControl)
            {
                IsPositionControl = true;
                IsVelocityControl = false;
            }
        }

    }
}