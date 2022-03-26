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
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DTUAV.Network_Module.Global_Network;
using LCM.LCM;

public class ConnectorLcmNode : MonoBehaviour
{
    [Header("Configure Cloud Device")]
    [Header("The Product Key")]
    public string ProductKey; //The key of product in cloud platform  
    [Header("The Device Name")]
    public string DeviceName; //The name of device in cloud platform
    [Header("The Device Secret")]
    public string DeviceSecret;//The secret of device in cloud platform
    [Header("The Publish Topic")]
    public string PublishTopic;//The message publish topic in cloud platform
    [Header("The Subscribe Topic")]
    public string SubscribeTopic;//The message subscribe topic in cloud plafrom

    [Header("Configure LCM Network")]
    [Header("The Subscribe Topic of LCM Network")]
    public string LcmMessageSubName;
    [Header("The Publish Topic of LCM Network")]
    public string LcmMessagePubName;

    private ConnectorLcm _connectorLcm;

 

    void Start()
    {
        _connectorLcm = new ConnectorLcm(ProductKey,DeviceName,DeviceSecret,PublishTopic,SubscribeTopic,LcmMessageSubName,LcmMessagePubName);
    }

}
