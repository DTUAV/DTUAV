
Shader "Custom/GetDepthData" {
    Properties{
                                           _data("depth_data",Float) = 1
                                           _Diffuse("Diffuse",Color) = (1,1,1,1)
    }

        SubShader{
        Tags { "RenderType" = "Opaque" }

        Pass{
        CGPROGRAM
        #pragma vertex vert
        #pragma fragment frag
        #include "UnityCG.cginc"

        sampler2D _CameraDepthTexture;
        float _data;
        half4 _Diffuse;
        struct v2f {
           float4 pos : SV_POSITION;
           float4 scrPos:TEXCOORD1;
        };

        //Vertex Shader
        v2f vert(appdata_base v) {
           v2f o;
           o.pos = UnityObjectToClipPos(v.vertex);
           o.scrPos = ComputeScreenPos(o.pos);
           //for some reason, the y position of the depth texture comes out inverted
           //o.scrPos.y = 1 - o.scrPos.y;
           return o;
        }

        //Fragment Shader
        half4 frag(v2f i) : COLOR{
           float depthValue = Linear01Depth(tex2Dproj(_CameraDepthTexture, UNITY_PROJ_COORD(i.scrPos)).r);
        //float depthValue = LinearEyeDepth(tex2Dproj(_CameraDepthTexture, UNITY_PROJ_COORD(i.scrPos)).r);
       half4 depth;
       _data = depthValue;

       depth.r = depthValue;
       depth.g = 1;
       depth.b = 1;

       depth.a = 1;
       _Diffuse = depth;
       return depth;
    }
    ENDCG
    }
    }
        FallBack "Diffuse"
}