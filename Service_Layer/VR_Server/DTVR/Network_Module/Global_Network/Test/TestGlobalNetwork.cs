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
using DTUAV.Message;
using UnityEngine;
using LCM.LCM;
using lcm_iot_msgs;
public class TestGlobalNetwork : MonoBehaviour,LCMSubscriber
{
    [Header("Configure LCM Network")]
    [Header("The Subscribe Topic of LCM Network")]
    public string LcmMessageSubName;
    [Header("The Publish Topic of LCM Network")]
    public string LcmMessagePubName;

    private LCM.LCM.LCM _lcmPublisher;
    private LCM.LCM.LCM _lcmSubscriber;
    private LcmIotMessage _lcmIotMessage;
    private IotMessage _iotMessage;
    public void MessageReceived(LCM.LCM.LCM lcm, string channel, LCMDataInputStream ins)
    {
        if (channel == LcmMessageSubName)
        {
            LcmIotMessage msg = new LcmIotMessage(ins);
            Debug.Log("TestGlobalNetwork--: "+msg.SourceID);
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        _lcmSubscriber = new LCM.LCM.LCM();
        _lcmSubscriber.Subscribe(LcmMessageSubName, this);
        _lcmPublisher = LCM.LCM.LCM.Singleton;
        _lcmIotMessage = new LcmIotMessage();
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.S))
        {
            IotMessage iotMessage = new IotMessage();
            _lcmIotMessage.TimeStamp = 1555533;
            _lcmIotMessage.MessageID = MessageId.UavLocalPositionMessageID;
            _lcmIotMessage.SourceID = ObjectId.R_UAV_0;
            _lcmIotMessage.TargetID = ObjectId.V_UAV_0;
            UavLocalPositionMessage localPositionMessage = new UavLocalPositionMessage();
            localPositionMessage.position_x = 0.0;
            localPositionMessage.position_y = 1.0;
            localPositionMessage.position_z = 2.0;
            localPositionMessage.rotation_x = 0;
            localPositionMessage.rotation_y = 0;
            localPositionMessage.rotation_z = 0;
            localPositionMessage.rotation_w = 1;
            _lcmIotMessage.MessageData = JsonUtility.ToJson(localPositionMessage);

            _lcmPublisher.Publish(LcmMessagePubName, _lcmIotMessage);
            Debug.Log("testGlobalNetwork--local--: "+ localPositionMessage.position_x);
        }
    }
}
