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
    public class GlobalNetworkMsgPackNode : MonoBehaviour
    {
        [Header("Configure LCM Network")]
        [Header("Choose whether to send local position")]
        public bool IsSendLocalPosition;

        [Header("Local position topic name in LCM Network")]
        public string LocalPositionMsgSubName;

        [Header("Choose whether to send global position")]
        public bool IsSendGlobalPosition;

        [Header("Global position topic name in LCM Network")]
        public string GlobalPositionMsgSubName;

        [Header("Choose whether to send current velocity")]
        public bool IsSendVelocity;

        [Header("Current velocity topic name in LCM Network")]
        public string CurrentVelocityMsgSubName;

        [Header("The Publish Topic of LCM Network to ConnectorLcmNode Subscribe")]
        public string GlobalNetworkMessagePubName;

        [Header("Configure Object ID")] 
        [Header("The Object Id of Message From")]
        public int SourceId;

        [Header("The Object Id of Message To")]
        public int TargetId;

        private GlobalNetworkPack _globalNetworkPack;
        // Start is called before the first frame update
        void Start()
        {
           _globalNetworkPack = new GlobalNetworkPack(IsSendGlobalPosition,IsSendLocalPosition,IsSendVelocity,GlobalPositionMsgSubName,LocalPositionMsgSubName,CurrentVelocityMsgSubName,GlobalNetworkMessagePubName,SourceId,TargetId);

        }

        

    }
}
