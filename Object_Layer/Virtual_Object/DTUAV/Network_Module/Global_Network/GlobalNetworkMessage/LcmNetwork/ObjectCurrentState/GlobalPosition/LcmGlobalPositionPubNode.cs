using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace DTUAV.Network_Module.LCM_Network
{

    public class LcmGlobalPositionPubNode : MonoBehaviour
    {
        [Header("Configure Object Transform")]
        public Transform ObjecTransform;
        [Header("Configure Topic Name of LCM Network")]
        public string TopicName;
        [Header("Configure Message Sending Frequency")]
        public float MessageFrequency;

        private LcmGlobalPositionPub _lcmGlobalPositionPub;
        // Start is called before the first frame update
        void Start()
        {
            _lcmGlobalPositionPub = new LcmGlobalPositionPub(ObjecTransform,TopicName,MessageFrequency);
        }

        void OnDestroy()
        {
            _lcmGlobalPositionPub.SetIsRun(false);
        }
    }
}
