using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using OpenCVForUnity.CoreModule;
using OpenCVForUnity.UnityUtils;

namespace DTUAV.Sensor_Module.DepthCamera
{

    public class GetDepthData : MonoBehaviour
    {
        public GetDepthImage depthImage; 

        private Mat depthImageMat;

        // Start is called before the first frame update
        void Start()
        {
            depthImageMat = new Mat(depthImage.imageWidth,depthImage.imageHeigh, CvType.CV_8UC4);
        }

        // Update is called once per frame
        void Update()
        {
            depthImage.getDepthImageFlag = true;
            Utils.texture2DToMat(depthImage.depthImage, depthImageMat);
            Debug.Log("aaaa" + (depthImageMat.get(1, 2)[0] / 255) * (depthImage.cameraFarPlanes - depthImage.cameraNearPlanes) + depthImage.cameraNearPlanes);
            Debug.Log("aaaa" + depthImageMat.get(1, 3)[0] / 255 * (depthImage.cameraFarPlanes - depthImage.cameraNearPlanes) + depthImage.cameraNearPlanes);
            Debug.Log("aaaa" + depthImageMat.get(2, 4)[0] / 255 * (depthImage.cameraFarPlanes - depthImage.cameraNearPlanes) + depthImage.cameraNearPlanes);
            Debug.Log("aaaa" + depthImageMat.get(3, 5)[0] / 255 * (depthImage.cameraFarPlanes - depthImage.cameraNearPlanes) + depthImage.cameraNearPlanes);
            Debug.Log("aaaa" + depthImageMat.get(4, 6)[0] / 255 * (depthImage.cameraFarPlanes - depthImage.cameraNearPlanes) + depthImage.cameraNearPlanes);
            Debug.Log("aaaa" + depthImageMat.get(5, 7)[0] / 255 * (depthImage.cameraFarPlanes - depthImage.cameraNearPlanes) + depthImage.cameraNearPlanes);
        }
    }
}
