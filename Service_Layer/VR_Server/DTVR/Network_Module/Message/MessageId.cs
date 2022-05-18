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


namespace DTUAV.Message
{
    public class MessageId
    {
        public const int CurrentPositionMessageID = 1;
        public const int TargetPositionMessageID = 2;
        public const int CompressedImageMessageID = 28;
        public const int UavCurrentPoseMessageID = 101;
        public const int UavRefPoseMessageID = 102;
        public const int UavCurrentVelocityMessageID = 103;
        public const int UavRefVelocityMessageID = 104;
        public const int UavStartMessageID = 105;
        public const int UavGlobalPositionMessageID = 106;
        public const int UavLocalPositionMessageID = 107;
        public const int UavLocalVelocityMessageID = 108;
        public const int VirtualGuideMessageID = 109;
        public const int HitMessageID = 1000;

        public const int CurrentLocalPositionMsgID = 1;
        public const int CurrentGlobalPositionMsgID = 2;
        public const int CurrentVelocityMsgID = 3;
        public const int CurrentStateMsgID = 4;
        public const int CurrentUnityGlobalPositionMsgID = 5;
        public const int TargetLocalPositionMsgID = 11;
        public const int TargetGlobalPositionMsgID = 12;
        public const int TargetVelocityMsgID = 13;
        public const int TargetCmdTypeMsgID = 14;
        public const int ControlApplyMsgID = 15;
        public const int MissionPointID = 16;


    }
}
