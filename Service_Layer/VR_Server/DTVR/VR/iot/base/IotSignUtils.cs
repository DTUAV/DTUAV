using System.Collections;
using System.Collections.Generic;
using System;
using System.Linq;
using System.Text;
using System.Security.Cryptography;
using Org.BouncyCastle.Crypto.Operators;

namespace SimUnity.Aliyun
{
    public class IotSignUtils
    {
        public static string sign(Dictionary<string, string> param, string deviceSecret, string signMethod)
        {
            string[] sortedKey = param.Keys.ToArray();
            Array.Sort(sortedKey);

            StringBuilder builder = new StringBuilder();
            foreach (var i in sortedKey)
            {
                builder.Append(i).Append(param[i]);
            }

            byte[] key = Encoding.UTF8.GetBytes(deviceSecret);
            byte[] signContent = Encoding.UTF8.GetBytes(builder.ToString());
            //这里根据signMethod动态调整，本例子硬编码了： 'hmacmd5'
            var hmac = new HMACMD5(key);
            byte[] hashBytes = hmac.ComputeHash(signContent);

            StringBuilder signBuilder = new StringBuilder();
            foreach (byte b in hashBytes)
                signBuilder.AppendFormat("{0:x2}", b);

            return signBuilder.ToString();

        }
    }
}
