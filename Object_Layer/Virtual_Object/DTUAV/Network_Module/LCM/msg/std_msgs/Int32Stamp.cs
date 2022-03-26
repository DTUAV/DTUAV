/* LCM type definition class file
 * This file was automatically generated by lcm-gen
 * DO NOT MODIFY BY HAND!!!!
 */

using System;
using System.Collections.Generic;
using System.IO;
using LCM.LCM;
 
namespace std_msgs
{
    public sealed class Int32Stamp : LCM.LCM.LCMEncodable
    {
        public double timestamp;
        public int data;
 
        public Int32Stamp()
        {
        }
 
        public static readonly ulong LCM_FINGERPRINT;
        public static readonly ulong LCM_FINGERPRINT_BASE = 0x62d2070079a6ceb3L;
 
        static Int32Stamp()
        {
            LCM_FINGERPRINT = _hashRecursive(new List<String>());
        }
 
        public static ulong _hashRecursive(List<String> classes)
        {
            if (classes.Contains("std_msgs.Int32Stamp"))
                return 0L;
 
            classes.Add("std_msgs.Int32Stamp");
            ulong hash = LCM_FINGERPRINT_BASE
                ;
            classes.RemoveAt(classes.Count - 1);
            return (hash<<1) + ((hash>>63)&1);
        }
 
        public void Encode(LCMDataOutputStream outs)
        {
            outs.Write((long) LCM_FINGERPRINT);
            _encodeRecursive(outs);
        }
 
        public void _encodeRecursive(LCMDataOutputStream outs)
        {
            outs.Write(this.timestamp); 
 
            outs.Write(this.data); 
 
        }
 
        public Int32Stamp(byte[] data) : this(new LCMDataInputStream(data))
        {
        }
 
        public Int32Stamp(LCMDataInputStream ins)
        {
            if ((ulong) ins.ReadInt64() != LCM_FINGERPRINT)
                throw new System.IO.IOException("LCM Decode error: bad fingerprint");
 
            _decodeRecursive(ins);
        }
 
        public static std_msgs.Int32Stamp _decodeRecursiveFactory(LCMDataInputStream ins)
        {
            std_msgs.Int32Stamp o = new std_msgs.Int32Stamp();
            o._decodeRecursive(ins);
            return o;
        }
 
        public void _decodeRecursive(LCMDataInputStream ins)
        {
            this.timestamp = ins.ReadDouble();
 
            this.data = ins.ReadInt32();
 
        }
 
        public std_msgs.Int32Stamp Copy()
        {
            std_msgs.Int32Stamp outobj = new std_msgs.Int32Stamp();
            outobj.timestamp = this.timestamp;
 
            outobj.data = this.data;
 
            return outobj;
        }
    }
}
