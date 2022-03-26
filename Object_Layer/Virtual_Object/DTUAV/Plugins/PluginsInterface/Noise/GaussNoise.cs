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
using System.Runtime.InteropServices;

namespace DTUAV.Noise
{
    public class GaussNoise
    {
        [DllImport("GaussNoiseDll")]
        public extern static double GaussianNoiseData(double mean, double dev);
    }

}