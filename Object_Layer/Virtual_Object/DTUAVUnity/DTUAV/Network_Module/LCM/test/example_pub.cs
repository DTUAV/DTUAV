using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Linq;
using System.Text;
using exlcm;
using  LCM;

public class example_pub : MonoBehaviour
{
    LCM.LCM.LCM myLCM = LCM.LCM.LCM.Singleton;
    exlcm.example_t msg = new example_t();

    private int i = 0;
    // Start is called before the first frame update
    void Start()
    {
      
      TimeSpan span = DateTime.Now - new DateTime(1970, 1, 1);
      msg.timestamp = span.Ticks * 100;
      msg.position = new double[3]{1,2,3};
      msg.orientation = new double[4]{1,2,3,0};
      msg.num_ranges = 15;
      msg.ranges = new short[msg.num_ranges];
      for (int i = 0; i < msg.num_ranges; i++)
      {
            msg.ranges[i] = (short)i;
      }

      msg.name = "example string";
      msg.enabled = true;
    //  myLCM.Publish("EXAMPLE",msg);

    }

    void Update()
    {
        if (i==0)
        {
            myLCM.Publish("EXAMPLE", msg);
            i = 1;
        }
  
    }

}
