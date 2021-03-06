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

using System.Runtime.InteropServices;

namespace DTUAV.Time
{
    public class SimTime
    {
        [DllImport("Time_Project")]
        public extern static long GetSystemTimeStampNs();//Get the System Time with Nanosecond Format

        [DllImport("Time_Project")]
        public extern static long GetSystemTimeStampUs();//Get the System Time with Microseconds Format

        [DllImport("Time_Project")]
        public extern static long GetSystemTimeStampMs();//Get the System Time with Millisecond Format

        [DllImport("Time_Project")]
        public extern static long GetSystemTimeStampS();//Get the System Time with Seconds Format

        [DllImport("Time_Project")]
        public extern static long GetMachineRunTimeStampNs();//Get the Application Start to Now Time with Nanosecond Format

        [DllImport("Time_Project")]
        public extern static long GetMachineRunTimeStampUs();//Get the Application Start to Now Time with Microseconds Format

        [DllImport("Time_Project")]
        public extern static long GetMachineRunTimeStampMs();//Get the Application Start to Now Time with Millisecond Format

        [DllImport("Time_Project")]
        public extern static long GetMachineRunTimeStampS();//Get the Application Start to Now Time with Seconds Format
    }
}
