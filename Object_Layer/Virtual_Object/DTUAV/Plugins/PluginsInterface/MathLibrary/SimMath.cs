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
using System.Runtime.InteropServices;
namespace DTUAV.Math
{
    
    public struct Vector4Float
    {
        public float x;
        public float y;
        public float z;
        public float w;
    }

    public struct Vector4Double
    {
        public double x;
        public double y;
        public double z;
        public double w;
    }

    public struct Vector4Int
    {
        public int x;
        public int y;
        public int z;
        public int w;
    }
    public struct Vector2Float
    {
        public float x;
        public float y;
    }

    public struct Vector2Double
    {
        public double x;
        public double y;
    }

    public struct Vector2Int
    {
        public int x;
        public int y;
    }

    public struct Vector3Float
    {
        public float x;
        public float y;
        public float z;
    }

    public struct Vector3Double
    {
        public double x;
        public double y;
        public double z;
    }

    public struct Vector3Int
    {
        public int x;
        public int y;
        public int z;
    }

    public class SimMath
    {



        public static double M_PI = 3.1415926535898;

        [DllImport("MathLibraryDll")]
        public extern static double acosD(double x);
        [DllImport("MathLibraryDll")]
        public extern static float acosF(float x);
        [DllImport("MathLibraryDll")]
        public extern static double asinD(double x);
        [DllImport("MathLibraryDll")]
        public extern static float asinF(float x);

        [DllImport("MathLibraryDll")]
        public extern static double atanD(double x);
        [DllImport("MathLibraryDll")]
        public extern static float atanF(float x);
        [DllImport("MathLibraryDll")]
        public extern static double absD(double x);
        [DllImport("MathLibraryDll")]
        public extern static float absF(float x);
        [DllImport("MathLibraryDll")]
        public extern static int absI(int x);

        [DllImport("MathLibraryDll")]
        public extern static double cosD(double x);
        [DllImport("MathLibraryDll")]
        public extern static float cosF(float x);
        [DllImport("MathLibraryDll")]
        public extern static double sinD(double x);
        [DllImport("MathLibraryDll")]
        public extern static float sinF(float x);

        [DllImport("MathLibraryDll")]
        public extern static double tanD(double x);
        [DllImport("MathLibraryDll")]
        public extern static float tanF(float x);

        [DllImport("MathLibraryDll")]
        public extern static double coshD(double x);
        [DllImport("MathLibraryDll")]
        public extern static float coshF(float x);
        [DllImport("MathLibraryDll")]
        public extern static double sinhD(double x);
        [DllImport("MathLibraryDll")]
        public extern static float sinhF(float x);

        [DllImport("MathLibraryDll")]
        public extern static double expD(double x);
        [DllImport("MathLibraryDll")]
        public extern static float expF(float x);
        [DllImport("MathLibraryDll")]
        public extern static double fabsD(double x);
        [DllImport("MathLibraryDll")]
        public extern static float fabsF(float x);

        [DllImport("MathLibraryDll")]
        public extern static double fmodD(double x);
        [DllImport("MathLibraryDll")]
        public extern static float fmodF(float x);

        [DllImport("MathLibraryDll")]
        public extern static double logD(double x);
        [DllImport("MathLibraryDll")]
        public extern static float logF(float x);

        [DllImport("MathLibraryDll")]
        public extern static double log10D(double x);
        [DllImport("MathLibraryDll")]
        public extern static float log10F(float x);

        [DllImport("MathLibraryDll")]
        public extern static double powD(double x, double y);
        [DllImport("MathLibraryDll")]
        public extern static float powF(float x, float y);

        [DllImport("MathLibraryDll")]
        public extern static double sqrtD(double x);
        [DllImport("MathLibraryDll")]
        public extern static float sqrtF(float x);

        [DllImport("MathLibraryDll")]
        public extern static double maxD(double x, double y);
        [DllImport("MathLibraryDll")]
        public extern static float maxF(float x, float y);
        [DllImport("MathLibraryDll")]
        public extern static double minD(double x, double y);
        [DllImport("MathLibraryDll")]
        public extern static float minF(float x, float y);
        [DllImport("MathLibraryDll")]
        public extern static double ceilD(double x);
        [DllImport("MathLibraryDll")]
        public extern static float ceilF(float x);
        [DllImport("MathLibraryDll")]
        public extern static double floorD(double x);
        [DllImport("MathLibraryDll")]
        public extern static float floorF(float x);
        [DllImport("MathLibraryDll")]
        public extern static double ldexpD(double x, double y);
        [DllImport("MathLibraryDll")]
        public extern static float ldexpF(float x, float y);

        [DllImport("MathLibraryDll")]
        public extern static double hypotD(double x, double y);
        [DllImport("MathLibraryDll")]
        public extern static float hypotF(float x, float y);
        [DllImport("Math_Project")]
        public extern static double atan2D(double y, double x);
        [DllImport("Math_Project")]
        public extern static int RandomIntWithMt19937_64(int min_value, int max_value);

        [DllImport("Math_Project")]
        public extern static long RandomLongWithMt19937_64(long min_value, long max_value);

        [DllImport("Math_Project")]
        public extern static double RandomDoubleWithMt19937_64(int min_value, int max_value);

        [DllImport("Math_Project")]
        public extern static int RandomIntWithDefaultRandomEngine(int min_value, int max_value);

        [DllImport("Math_Project")]
        public extern static long RandomLongWithDefaultRandomEngine(long min_value, long max_value);

        [DllImport("Math_Project")]
        public extern static double RandomDoubleWithDefaultRandomEngine(int min_value, int max_value);

        [DllImport("Math_Project")]
        public extern static double NormalDistribution(double mu, double sigma);

        [DllImport("Math_Project")] 
        public extern static int UniformIntDistribution(int low_value, int top_value);

        public static double NormalDistribution()
        {
            Random rand = new Random();
            double u1, u2, v1 = 0, v2 = 0, s = 0, z1 = 0, z2 = 0;
            while (s > 1 || s == 0)
            {
                u1 = rand.NextDouble();
                u2 = rand.NextDouble();
                v1 = 2 * u1 - 1;
                v2 = 2 * u2 - 1;
                s = v1 * v1 + v2 * v2;
            }
            z1 = System.Math.Sqrt(-2 * System.Math.Log(s) / s) * v1;
            z2 = System.Math.Sqrt(-2 * System.Math.Log(s) / s) * v2;
            return z1;
        }
    }

}