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
using LCM.LCM;
using geometry_msgs;

namespace DTUAV.Network_Module.LCM_Network
{
    public class TestLcmCurrentVelocityPub : MonoBehaviour, LCM.LCM.LCMSubscriber
    {
        // Start is called before the first frame update
        public string TopicName;
        private LCM.LCM.LCM SubLcm;

        public void MessageReceived(LCM.LCM.LCM lcm, string channel, LCMDataInputStream ins)
        {
           TwistStamp twistStamp = new TwistStamp(ins);
            Debug.Log("LocalVelocity.x: " + twistStamp.linear.x);
        }

        void Start()
        {
            SubLcm = new LCM.LCM.LCM();
            SubLcm.Subscribe(TopicName, this);
        }

    }
}