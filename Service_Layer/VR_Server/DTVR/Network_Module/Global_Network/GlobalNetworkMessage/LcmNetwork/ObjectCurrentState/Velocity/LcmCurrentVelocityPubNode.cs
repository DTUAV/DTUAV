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

namespace DTUAV.Network_Module.LCM_Network
{

    public class LcmCurrentVelocityPubNode : MonoBehaviour
    {
        [Header("Configure Object Rigidbody")]
        public Rigidbody ObjecRigidbody;
        [Header("Configure Topic Name of LCM Network")]
        public string TopicName;
        [Header("Configure Message Sending Frequency")]
        public float MessageFrequency;

        private LcmCurrentVelocityPub _lcmCurrentVelocityPub;
        // Start is called before the first frame update
        void Start()
        {
            _lcmCurrentVelocityPub = new LcmCurrentVelocityPub(ObjecRigidbody, TopicName, MessageFrequency);
        }

        void OnDestroy()
        {
            _lcmCurrentVelocityPub.SetIsRun(false);
        }
    }
}