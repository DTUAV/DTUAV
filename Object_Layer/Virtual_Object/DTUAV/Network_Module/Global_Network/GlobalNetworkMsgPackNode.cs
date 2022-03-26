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
