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
