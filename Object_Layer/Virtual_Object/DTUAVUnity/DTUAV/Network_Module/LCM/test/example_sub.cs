using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Linq;
using System.Text;
using exlcm;
using LCM;


public class example_sub : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        LCM.LCM.LCM myLcm;
        myLcm = new LCM.LCM.LCM();
        myLcm.SubscribeAll(new SimpleSubscriber());

    }

    // Update is called once per frame
    internal class SimpleSubscriber:LCM.LCM.LCMSubscriber
    {
        public void MessageReceived(LCM.LCM.LCM lcm, string channel, LCM.LCM.LCMDataInputStream dins)
        {
            Debug.Log("RECV:"+channel);
            if (channel == "EXAMPLE")
            {
                exlcm.example_t msg = new example_t(dins);
                Debug.Log("Received message of the type example_t:");
                Debug.Log(" timestamp   = {0:D}" + msg.timestamp);
            }
        }
    }
}
