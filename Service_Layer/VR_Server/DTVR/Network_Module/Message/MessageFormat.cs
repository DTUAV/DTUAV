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
using System;
using System.Collections;
using System.Collections.Generic;

namespace DTUAV.Message
{
    [Serializable]
    public class MessageFormat
    {

    }
    
    public class BaseMessage
    {
     //    T data = new T();
    }
    /// <typeparam name="T"></typeparam>
    public class IotMessageList
    {
        public int TargetID;
        public int SourceID;
        public int MessageID;
        public ArrayList MessageData;
        public double TimeStamp;
    }




    [Serializable]
    public class IotMessage 
    {
        public int TargetID;
        public int SourceID;
        public int MessageID;
        public string MessageData;
        public double TimeStamp;
    }


    [Serializable]
    public class CurrentPoseMessage
    {
        public float PositionX;
        public float PositionY;
        public float PositionZ;
        public float RotationX;
        public float RotationY;
        public float RotationZ;
        public float RotationW;
    }

    [Serializable]
    public class TargetPoseMessage
    {
        public float PositionX;
        public float PositionY;
        public float PositionZ;
        public float RotationX;
        public float RotationY;
        public float RotationZ;
        public float RotationW;
    }

    [Serializable]
    public class UavCurrentPoseMessage
    {
        public double position_x;
        public double position_y;
        public double position_z;
        public double rotation_x;
        public double rotation_y;
        public double rotation_z;
        public double rotation_w;
    }

    [Serializable]
    public class UavRefPoseMessage
    {
        public double position_x;
        public double position_y;
        public double position_z;
        public double rotation_x;
        public double rotation_y;
        public double rotation_z;
        public double rotation_w;
    }

    [Serializable]
    public class UavCurrentVelocityMessage
    {
        public double linear_velocity_x;
        public double linear_velocity_y;
        public double linear_velocity_z;
        public double anger_velocity_x;
        public double anger_velocity_y;
        public double anger_velocity_z;
    }

    [Serializable]
    public class UavRefVelocityMessage
    {
        public double linear_velocity_x;
        public double linear_velocity_y;
        public double linear_velocity_z;
        public double anger_velocity_x;
        public double anger_velocity_y;
        public double anger_velocity_z;
    }

    [Serializable]
    public class UavStartMessage
    {
        public bool start;
    }

    [Serializable]
    public class UavGlobalPositionMessage
    {
        public int status;
        public int service;
        public double latitude;
        public double longitude;
        public double altitude;
        public double[] position_covariance;
        public int position_covariance_type;
    }

    [Serializable]
    public class UavLocalPositionMessage
    {
        public double position_x;
        public double position_y;
        public double position_z;
        public double rotation_x;
        public double rotation_y;
        public double rotation_z;
        public double rotation_w;
    } 

    [Serializable]
    public class UavLocalVelocityMessage
    {
        public double linear_velocity_x;
        public double linear_velocity_y;
        public double linear_velocity_z;
        public double anger_velocity_x;
        public double anger_velocity_y;
        public double anger_velocity_z;
    }

    [Serializable]
    public class HitMessage
    {
        public bool isHit;
    }

    [Serializable]
    public class CompressedImageMessage
    {
        public string format;
        public byte[] data;
    }
    
    [Serializable]
    public class VirtualGuideMessage
    {
        public float guideVelocityX;
        public float guideVelocityY;
        public float guideVelocityZ;
    }

    [Serializable]
    public class CurrentLocalPositionMsg
    {
       public double position_x;
       public double position_y;
       public double position_z;
       public double rotation_x;
       public double rotation_y;
       public double rotation_z;
       public double rotation_w;
    };

    [Serializable]
    public class CurrentGlobalPositionMsg
    {
       public double latitude;
       public double longitude;
       public double altitude;
    };

    [Serializable]
    public class CurrentVelocityMsg
    {
      public double linear_velocity_x;
      public double linear_velocity_y;
      public double linear_velocity_z;
      public double anger_velocity_x;
      public double anger_velocity_y;
      public double anger_velocity_z;
    };

    [Serializable]
    public class CurrentStateMsg
    {
       public bool connected;
       public bool armed;
       public bool guided;
       public bool manual_input;
       public string mode;
       public uint system_status;
    };
    public class TargetLocalPositionMsg
    {
        public double position_x;
        public double position_y;
        public double position_z;
        public double rotation_x;
        public double rotation_y;
        public double rotation_z;
        public double rotation_w;
    };

    [Serializable]
    public class TargetGlobalPositionMsg
    {
        public double latitude;
        public double longitude;
        public double altitude;
    };

    [Serializable]
    public class TargetVelocityMsg
    {
        public double linear_velocity_x;
        public double linear_velocity_y;
        public double linear_velocity_z;
        public double anger_velocity_x;
        public double anger_velocity_y;
        public double anger_velocity_z;
    };

    [Serializable]
    public class TargetCmdTypeMsg
    {
       public int type;
    };

    [Serializable]
    public class ControlApplyMsg
    {
       public bool apply_info;
    };

    public class MissionPoint
    {
        public double[] x;
        public double[] y;
        public double[] z;
    }
}
