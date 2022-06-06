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
namespace DTUAV.Math.DataNoise
{
    public class DataNoise
    {
        private static int GetRandomSeed() 
        {
            byte[] bytes = new byte[4];
            System.Security.Cryptography.RNGCryptoServiceProvider rng =
                new System.Security.Cryptography.RNGCryptoServiceProvider();
            rng.GetBytes(bytes);
            return BitConverter.ToInt32(bytes, 0);
        }

        public static double GaussNiose1() 
        {
            // Random ro = new Random(10);
            // long tick = DateTime.Now.Ticks;
            System.Random ran = new System.Random(GetRandomSeed());
            // Random rand = new Random();
            double r1 = ran.NextDouble();
            double r2 = ran.NextDouble();
            double result = System.Math.Sqrt((-2) * System.Math.Log(r2)) * System.Math.Sin(2 * System.Math.PI * r1);
            return result; 
        }
    }
}
