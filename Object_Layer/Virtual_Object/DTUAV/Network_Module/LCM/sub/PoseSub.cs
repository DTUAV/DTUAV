using System.Collections;
using System.Collections.Generic;
using geometry_msgs;
using UnityEngine;
using LcmNetwork.MessageType;
namespace DTUAV.Network_Module.LCM_Network
{
    public class PoseSub : BaseSub
    {
        
        // Start is called before the first frame update
        void Start()
        {
            base.BaseStart();
            base.BaseLcm.Subscribe(base.MessageName,new PoseSubscriber());
        }

        // Update is called once per frame
       // void Update()
       // {

      //  }

        internal class PoseSubscriber:LCM.LCM.LCMSubscriber
        {
            public void MessageReceived(LCM.LCM.LCM lcm, string channel, LCM.LCM.LCMDataInputStream dins)
            {
                geometry_msgs.PoseStamp msg = new geometry_msgs.PoseStamp(dins); 
                Debug.Log(msg.timestamp);
            }
        }
 
    }
}
