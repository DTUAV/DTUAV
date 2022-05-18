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

namespace DTUAV.Sensor_Module.DepthCamera
{
    public class GetDepthImage : MonoBehaviour
    {
        public Material depthMaterial;

        public int imageWidth;

        public int imageHeigh;

        public Camera dephtCamera;

        [HideInInspector]
        public Texture2D depthImage;

        [HideInInspector]
        public Texture2D updateDepthImage;

        [HideInInspector]
        public bool getDepthImageFlag = false;

        [HideInInspector]
        public float cameraNearPlanes;

        [HideInInspector]
        public float cameraFarPlanes;

        private RenderTexture depthRenderTexture;
        private bool getDataFlag = false;
        private Rect depthImageRect;

        // Start is called before the first frame update
        void Start()
        {
            depthImage = new Texture2D(imageWidth,imageHeigh,TextureFormat.RGB24,false);
            updateDepthImage = new Texture2D(imageWidth, imageHeigh, TextureFormat.RGB24, false);

            depthRenderTexture = new RenderTexture(imageWidth, imageHeigh, 24);
            depthImageRect = new Rect(0,0,imageWidth,imageHeigh);
            
            dephtCamera.depthTextureMode = DepthTextureMode.Depth;
            dephtCamera.targetTexture = depthRenderTexture;
            cameraNearPlanes = dephtCamera.nearClipPlane;
            cameraFarPlanes = dephtCamera.farClipPlane;
            
        }
        void OnRenderImage(RenderTexture source, RenderTexture destination)
        {
            
            Graphics.Blit(source, destination, depthMaterial);
            RenderTexture currentRT = RenderTexture.active;
            RenderTexture.active = destination;
            updateDepthImage.ReadPixels(depthImageRect, 0, 0);
            updateDepthImage.Apply();
            RenderTexture.active = currentRT;
            if (getDataFlag)
            {
                    depthImage = updateDepthImage;
                    getDataFlag = false;
            }
        }
        // Update is called once per frame
        void Update()
        {
            if (getDepthImageFlag && !getDataFlag)
            {
                getDepthImageFlag = false;
                getDataFlag = true;

            }
        }
    }
}
