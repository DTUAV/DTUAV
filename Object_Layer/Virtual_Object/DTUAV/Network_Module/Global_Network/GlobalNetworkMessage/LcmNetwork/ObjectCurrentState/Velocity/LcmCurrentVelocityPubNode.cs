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