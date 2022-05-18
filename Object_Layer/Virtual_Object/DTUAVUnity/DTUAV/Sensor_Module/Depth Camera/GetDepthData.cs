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
