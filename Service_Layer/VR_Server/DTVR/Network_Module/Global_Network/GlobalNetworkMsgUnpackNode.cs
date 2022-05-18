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
using UnityEngine;
using lcm_iot_msgs;
using UnityEditor.Experimental.GraphView;
using DTUAV.Message;
using geometry_msgs;

namespace DTUAV.Network_Module.Global_Network
{
    public class GlobalNetworkMsgUnpackNode: MonoBehaviour
    {
        [Header("Configure LCM Network")]
        [Header("Choose whether to get target local position")]
        public bool IsGetTargetLocalPosition;

        [Header("Target Local position topic name in LCM Network")]
        public string TargetLocalPositionMsgPubName;

        [Header("Choose whether to get target global position")]
        public bool IsGetTargetGlobalPosition;

        [Header("Target Global position topic name in LCM Network")]
        public string TargetGlobalPositionMsgPubName;

        [Header("Choose whether to get target velocity")]
        public bool IsGetTargetVelocity;

        [Header("Target velocity topic name in LCM Network")]
        public string TargetVelocityMsgPubName;

        [Header("Choose whether to get target cmd type")]
        public bool IsGetTargetCmdType;

        [Header("Target cmd type topic name in LCM Network")]
        public string TargetCmdTypeMsgPubName;



        [Header("The Subscribe Topic of LCM Network to ConnectorLcmNode Publisher")]
        public string GlobalNetworkMessageSubName;

        [Header("Configure Object ID")]
        [Header("The Object Id of Message From")]
        public int SourceId;

        [Header("The Object Id of Message To")]
        public int TargetId;

        private GlobalNetworkUnpack _globalNetworkUnpack;
        // Start is called before the first frame update
        void Start()
        {
            _globalNetworkUnpack = new GlobalNetworkUnpack(IsGetTargetGlobalPosition, IsGetTargetLocalPosition,
                IsGetTargetVelocity, IsGetTargetCmdType, TargetGlobalPositionMsgPubName, TargetLocalPositionMsgPubName,
                TargetVelocityMsgPubName, GlobalNetworkMessageSubName, TargetCmdTypeMsgPubName, SourceId, TargetId);

        }



    }
}
