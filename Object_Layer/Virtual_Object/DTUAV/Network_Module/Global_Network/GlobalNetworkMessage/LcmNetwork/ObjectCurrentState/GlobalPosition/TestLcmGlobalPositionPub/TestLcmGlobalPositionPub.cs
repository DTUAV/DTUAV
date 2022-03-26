using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using LCM.LCM;
using geometry_msgs;

namespace DTUAV.Network_Module.LCM_Network
{
    public class TestLcmGlobalPositionPub : MonoBehaviour,LCM.LCM.LCMSubscriber
    {
        // Start is called before the first frame update
        public string TopicName;
        private LCM.LCM.LCM SubLcm;

        public void MessageReceived(LCM.LCM.LCM lcm, string channel, LCMDataInputStream ins)
        {
            PoseStamp gloPoseStamp = new PoseStamp(ins);
            Debug.Log("globalPosition.x: "+gloPoseStamp.position.x);
        }

        void Start()
        {
            SubLcm = new LCM.LCM.LCM();
            SubLcm.Subscribe(TopicName, this);
        }

    }
}
