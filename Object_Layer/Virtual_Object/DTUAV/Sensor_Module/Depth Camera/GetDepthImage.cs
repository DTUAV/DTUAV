/*
 *
 *  GNU General Public License (GPL)
 *
 * Update Information:
 *                    First: 2021-8-6 In Guangdong University of Technology By Yuanlin Yang  Email: yongwang0808@163.com
 *
 *
 *
 *
 *
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
