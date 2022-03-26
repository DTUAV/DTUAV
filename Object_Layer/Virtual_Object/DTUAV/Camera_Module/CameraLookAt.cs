using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace DTUAV.Camera_Module
{
    public class CameraLookAt : MonoBehaviour
    {
        public Transform target;
        public float distanceUp = 15f;
        public float distanceAway = 10f;
        public float smooth = 2f; 

        public float camDepthSmooth = 5f;

    

        // Update is called once per frame
        void Update()
        {
            
            if ((Input.mouseScrollDelta.y < 0 && Camera.main.fieldOfView >= 3) ||
                Input.mouseScrollDelta.y > 0 && Camera.main.fieldOfView <= 80)
            {
                Camera.main.fieldOfView += Input.mouseScrollDelta.y * camDepthSmooth * UnityEngine.Time.deltaTime;
            }
        }

        void LateUpdate()
        {
            
            Vector3 disPos = target.position + Vector3.up * distanceUp - target.forward * distanceAway;
            transform.position = Vector3.Lerp(transform.position, disPos, UnityEngine.Time.deltaTime * smooth);
            transform.LookAt(target.position);
        }
    }
}
