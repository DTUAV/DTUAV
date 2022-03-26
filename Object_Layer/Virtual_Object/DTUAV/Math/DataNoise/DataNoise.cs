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

using System;
namespace DTUAV.Math.DataNoise
{
    public class DataNoise
    {
        private static int GetRandomSeed() //产生随机种子
        {
            byte[] bytes = new byte[4];
            System.Security.Cryptography.RNGCryptoServiceProvider rng =
                new System.Security.Cryptography.RNGCryptoServiceProvider();
            rng.GetBytes(bytes);
            return BitConverter.ToInt32(bytes, 0);
        }

        public static double GaussNiose1() //用box muller的方法产生均值为0，方差为1的正太分布随机数
        {
            // Random ro = new Random(10);
            // long tick = DateTime.Now.Ticks;
            System.Random ran = new System.Random(GetRandomSeed());
            // Random rand = new Random();
            double r1 = ran.NextDouble();
            double r2 = ran.NextDouble();
            double result = System.Math.Sqrt((-2) * System.Math.Log(r2)) * System.Math.Sin(2 * System.Math.PI * r1);
            return result; //返回随机数
        }
    }
}
