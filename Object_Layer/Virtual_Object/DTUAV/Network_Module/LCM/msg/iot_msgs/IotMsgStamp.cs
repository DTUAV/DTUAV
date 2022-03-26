/* LCM type definition class file
 * This file was automatically generated by lcm-gen
 * DO NOT MODIFY BY HAND!!!!
 */

using System;
using System.Collections.Generic;
using System.IO;
using LCM.LCM;
 
namespace iot_msgs
{
    public sealed class IotMsgStamp : LCM.LCM.LCMEncodable
    {
        public double timestamp;
        public int packet_object_to;
        public int packet_object_from;
        public int packet_id;
        public String packet_data;
 
        public IotMsgStamp()
        {
        }
 
        public static readonly ulong LCM_FINGERPRINT;
        public static readonly ulong LCM_FINGERPRINT_BASE = 0x0629d2c4dd06bb1fL;
 
        static IotMsgStamp()
        {
            LCM_FINGERPRINT = _hashRecursive(new List<String>());
        }
 
        public static ulong _hashRecursive(List<String> classes)
        {
            if (classes.Contains("iot_msgs.IotMsgStamp"))
                return 0L;
 
            classes.Add("iot_msgs.IotMsgStamp");
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
            byte[] __strbuf = null;
            outs.Write(this.timestamp); 
 
            outs.Write(this.packet_object_to); 
 
            outs.Write(this.packet_object_from); 
 
            outs.Write(this.packet_id); 
 
            __strbuf = System.Text.Encoding.GetEncoding("US-ASCII").GetBytes(this.packet_data); outs.Write(__strbuf.Length+1); outs.Write(__strbuf, 0, __strbuf.Length); outs.Write((byte) 0); 
 
        }
 
        public IotMsgStamp(byte[] data) : this(new LCMDataInputStream(data))
        {
        }
 
        public IotMsgStamp(LCMDataInputStream ins)
        {
            if ((ulong) ins.ReadInt64() != LCM_FINGERPRINT)
                throw new System.IO.IOException("LCM Decode error: bad fingerprint");
 
            _decodeRecursive(ins);
        }
 
        public static iot_msgs.IotMsgStamp _decodeRecursiveFactory(LCMDataInputStream ins)
        {
            iot_msgs.IotMsgStamp o = new iot_msgs.IotMsgStamp();
            o._decodeRecursive(ins);
            return o;
        }
 
        public void _decodeRecursive(LCMDataInputStream ins)
        {
            byte[] __strbuf = null;
            this.timestamp = ins.ReadDouble();
 
            this.packet_object_to = ins.ReadInt32();
 
            this.packet_object_from = ins.ReadInt32();
 
            this.packet_id = ins.ReadInt32();
 
            __strbuf = new byte[ins.ReadInt32()-1]; ins.ReadFully(__strbuf); ins.ReadByte(); this.packet_data = System.Text.Encoding.GetEncoding("US-ASCII").GetString(__strbuf);
 
        }
 
        public iot_msgs.IotMsgStamp Copy()
        {
            iot_msgs.IotMsgStamp outobj = new iot_msgs.IotMsgStamp();
            outobj.timestamp = this.timestamp;
 
            outobj.packet_object_to = this.packet_object_to;
 
            outobj.packet_object_from = this.packet_object_from;
 
            outobj.packet_id = this.packet_id;
 
            outobj.packet_data = this.packet_data;
 
            return outobj;
        }
    }
}

