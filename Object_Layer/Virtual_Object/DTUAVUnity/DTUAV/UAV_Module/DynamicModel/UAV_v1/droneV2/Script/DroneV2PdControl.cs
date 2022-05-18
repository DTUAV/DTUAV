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
namespace DTUAV.UAV_Module.droneV2
{

    [System.Serializable]
    public class DroneV2PdControl 
    {
        public float Pfactor;
        public float Dfactor;

        public float lastError;

        public DroneV2PdControl(float pFactor, float dFactor)
        {
            this.Dfactor = dFactor;
            this.Pfactor = pFactor;
        }

        public float UpdatePD(float refValue, float feeBackValue, float timeFrame)
        {
            float presentError = refValue - feeBackValue;
            float deriv = (presentError - lastError) / timeFrame;
            lastError = presentError;
            float finalPID = presentError * Pfactor + deriv * Dfactor;
            return finalPID;


        }
    }
}