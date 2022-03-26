using System;
using UnityEngine;
using UnityEngine.UI;
using System.Runtime.InteropServices;
using LCM.LCM;
using lcm_iot_msgs;
using DTUAV.Message;

namespace DTUAV.Network_Module.LCM_Network
{

    public class test_show_camera_data : MonoBehaviour, LCM.LCM.LCMSubscriber
    {
        public string IotMessageSubName;
        private LCM.LCM.LCM SubLcm;
        private byte[] _imageData;
        private bool isGet = false;
        void Start()
        {
            SubLcm = new LCM.LCM.LCM();
            SubLcm.Subscribe(IotMessageSubName, this);
        }
        public void MessageReceived(LCM.LCM.LCM lcm, string channel, LCMDataInputStream ins)
        {
            Debug.Log("mgggggggggggggggggg " );

            if (channel == IotMessageSubName)
            {
                LcmIotMessage msg = new LcmIotMessage(ins);
                Debug.Log("msg_id: "+msg.MessageID);
                if (msg.MessageID == MessageId.CompressedImageMessageID)
                {
                    CompressedImageMessage imageMessage = JsonUtility.FromJson<CompressedImageMessage>(msg.MessageData);
                    _imageData = imageMessage.data;
                    Debug.Log("dddd");
                    isGet = true;
                }
            }

           
        }
        void OnGUI()
        {
            if (isGet)
            {
                Texture2D texture2DData = new Texture2D(120, 120);
                texture2DData.LoadImage(_imageData);
               // Debug.Log("dddddddddddddddd" + data);
                GUI.Label(new Rect(20, 34, 120, 120), texture2DData);
            }

        }
    }
}
