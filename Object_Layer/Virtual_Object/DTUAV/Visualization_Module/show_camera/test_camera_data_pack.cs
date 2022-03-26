using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DTUAV.Message;
namespace DTUAV.Network_Module.LCM_Network
{
    public class test_camera_data_pack : MonoBehaviour
    {
        // Start is called before the first frame update
        void Start()
        {
            CompressedImageMessage imageMessage = new CompressedImageMessage();
            imageMessage.format = "jpeg";
            imageMessage.data = new byte[50];
            for (byte i = 0; i < imageMessage.data.Length; i++)
            {
                imageMessage.data[i] = i;
            }

            string imageString = JsonUtility.ToJson(imageMessage);
            Debug.Log("imageString"+imageString);
            CompressedImageMessage iotMsg = JsonUtility.FromJson<CompressedImageMessage>(imageString);
            Debug.Log("iotMsg.format"+iotMsg.format);
        }

        // Update is called once per frame
        void Update()
        {

        }
    }
}
