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
    public sealed class BoolStamp : LCM.LCM.LCMEncodable
    {
        public double timestamp;
        public bool data;
 
        public BoolStamp()
        {
        }
 
        public static readonly ulong LCM_FINGERPRINT;
        public static readonly ulong LCM_FINGERPRINT_BASE = 0x69d301c7aca4d4b3L;
 
        static BoolStamp()
        {
            LCM_FINGERPRINT = _hashRecursive(new List<String>());
        }
 
        public static ulong _hashRecursive(List<String> classes)
        {
            if (classes.Contains("std_msgs.BoolStamp"))
                return 0L;
 
            classes.Add("std_msgs.BoolStamp");
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
 
        public BoolStamp(byte[] data) : this(new LCMDataInputStream(data))
        {
        }
 
        public BoolStamp(LCMDataInputStream ins)
        {
            if ((ulong) ins.ReadInt64() != LCM_FINGERPRINT)
                throw new System.IO.IOException("LCM Decode error: bad fingerprint");
 
            _decodeRecursive(ins);
        }
 
        public static std_msgs.BoolStamp _decodeRecursiveFactory(LCMDataInputStream ins)
        {
            std_msgs.BoolStamp o = new std_msgs.BoolStamp();
            o._decodeRecursive(ins);
            return o;
        }
 
        public void _decodeRecursive(LCMDataInputStream ins)
        {
            this.timestamp = ins.ReadDouble();
 
            this.data = ins.ReadBoolean();
 
        }
 
        public std_msgs.BoolStamp Copy()
        {
            std_msgs.BoolStamp outobj = new std_msgs.BoolStamp();
            outobj.timestamp = this.timestamp;
 
            outobj.data = this.data;
 
            return outobj;
        }
    }
}

