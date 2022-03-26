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
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using lcm_iot_msgs;
using UnityEditor.Experimental.GraphView;
using DTUAV.Message;
using geometry_msgs;

namespace DTUAV.Network_Module.Local_Network
{
    public class LocalNetworkMsgUnpackNode: MonoBehaviour
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

        private LocalNetworkUnpack _globalNetworkUnpack;
        // Start is called before the first frame update
        void Start()
        {
            _globalNetworkUnpack = new LocalNetworkUnpack(IsGetTargetGlobalPosition, IsGetTargetLocalPosition,
                IsGetTargetVelocity, IsGetTargetCmdType, TargetGlobalPositionMsgPubName, TargetLocalPositionMsgPubName,
                TargetVelocityMsgPubName, GlobalNetworkMessageSubName, TargetCmdTypeMsgPubName, SourceId, TargetId);

        }



    }
}
