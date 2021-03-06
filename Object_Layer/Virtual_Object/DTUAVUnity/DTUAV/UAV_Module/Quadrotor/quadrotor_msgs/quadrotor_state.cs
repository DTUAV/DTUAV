/* LCM type definition class file
 * This file was automatically generated by lcm-gen
 * DO NOT MODIFY BY HAND!!!!
 */

using System;
using System.Collections.Generic;
using System.IO;
using LCM.LCM;
 
namespace quadrotor_msgs
{
    public sealed class quadrotor_state : LCM.LCM.LCMEncodable
    {
        public double timestamp;
        public double pos_x;
        public double pos_y;
        public double pos_z;
        public double vel_x;
        public double vel_y;
        public double vel_z;
        public double acc_x;
        public double acc_y;
        public double acc_z;
        public double roll;
        public double pitch;
        public double yaw;
        public double vel_roll;
        public double vel_pitch;
        public double vel_yaw;
        public double acc_roll;
        public double acc_pitch;
        public double acc_yaw;
        public double omega_x;
        public double omega_y;
        public double omega_z;
        public double omega_acc_x;
        public double omega_acc_y;
        public double omega_acc_z;
 
        public quadrotor_state()
        {
        }
 
        public static readonly ulong LCM_FINGERPRINT;
        public static readonly ulong LCM_FINGERPRINT_BASE = 0xb5fb6c294a42f5c2L;
 
        static quadrotor_state()
        {
            LCM_FINGERPRINT = _hashRecursive(new List<String>());
        }
 
        public static ulong _hashRecursive(List<String> classes)
        {
            if (classes.Contains("quadrotor_msgs.quadrotor_state"))
                return 0L;
 
            classes.Add("quadrotor_msgs.quadrotor_state");
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
 
            outs.Write(this.pos_x); 
 
            outs.Write(this.pos_y); 
 
            outs.Write(this.pos_z); 
 
            outs.Write(this.vel_x); 
 
            outs.Write(this.vel_y); 
 
            outs.Write(this.vel_z); 
 
            outs.Write(this.acc_x); 
 
            outs.Write(this.acc_y); 
 
            outs.Write(this.acc_z); 
 
            outs.Write(this.roll); 
 
            outs.Write(this.pitch); 
 
            outs.Write(this.yaw); 
 
            outs.Write(this.vel_roll); 
 
            outs.Write(this.vel_pitch); 
 
            outs.Write(this.vel_yaw); 
 
            outs.Write(this.acc_roll); 
 
            outs.Write(this.acc_pitch); 
 
            outs.Write(this.acc_yaw); 
 
            outs.Write(this.omega_x); 
 
            outs.Write(this.omega_y); 
 
            outs.Write(this.omega_z); 
 
            outs.Write(this.omega_acc_x); 
 
            outs.Write(this.omega_acc_y); 
 
            outs.Write(this.omega_acc_z); 
 
        }
 
        public quadrotor_state(byte[] data) : this(new LCMDataInputStream(data))
        {
        }
 
        public quadrotor_state(LCMDataInputStream ins)
        {
            if ((ulong) ins.ReadInt64() != LCM_FINGERPRINT)
                throw new System.IO.IOException("LCM Decode error: bad fingerprint");
 
            _decodeRecursive(ins);
        }
 
        public static quadrotor_msgs.quadrotor_state _decodeRecursiveFactory(LCMDataInputStream ins)
        {
            quadrotor_msgs.quadrotor_state o = new quadrotor_msgs.quadrotor_state();
            o._decodeRecursive(ins);
            return o;
        }
 
        public void _decodeRecursive(LCMDataInputStream ins)
        {
            this.timestamp = ins.ReadDouble();
 
            this.pos_x = ins.ReadDouble();
 
            this.pos_y = ins.ReadDouble();
 
            this.pos_z = ins.ReadDouble();
 
            this.vel_x = ins.ReadDouble();
 
            this.vel_y = ins.ReadDouble();
 
            this.vel_z = ins.ReadDouble();
 
            this.acc_x = ins.ReadDouble();
 
            this.acc_y = ins.ReadDouble();
 
            this.acc_z = ins.ReadDouble();
 
            this.roll = ins.ReadDouble();
 
            this.pitch = ins.ReadDouble();
 
            this.yaw = ins.ReadDouble();
 
            this.vel_roll = ins.ReadDouble();
 
            this.vel_pitch = ins.ReadDouble();
 
            this.vel_yaw = ins.ReadDouble();
 
            this.acc_roll = ins.ReadDouble();
 
            this.acc_pitch = ins.ReadDouble();
 
            this.acc_yaw = ins.ReadDouble();
 
            this.omega_x = ins.ReadDouble();
 
            this.omega_y = ins.ReadDouble();
 
            this.omega_z = ins.ReadDouble();
 
            this.omega_acc_x = ins.ReadDouble();
 
            this.omega_acc_y = ins.ReadDouble();
 
            this.omega_acc_z = ins.ReadDouble();
 
        }
 
        public quadrotor_msgs.quadrotor_state Copy()
        {
            quadrotor_msgs.quadrotor_state outobj = new quadrotor_msgs.quadrotor_state();
            outobj.timestamp = this.timestamp;
 
            outobj.pos_x = this.pos_x;
 
            outobj.pos_y = this.pos_y;
 
            outobj.pos_z = this.pos_z;
 
            outobj.vel_x = this.vel_x;
 
            outobj.vel_y = this.vel_y;
 
            outobj.vel_z = this.vel_z;
 
            outobj.acc_x = this.acc_x;
 
            outobj.acc_y = this.acc_y;
 
            outobj.acc_z = this.acc_z;
 
            outobj.roll = this.roll;
 
            outobj.pitch = this.pitch;
 
            outobj.yaw = this.yaw;
 
            outobj.vel_roll = this.vel_roll;
 
            outobj.vel_pitch = this.vel_pitch;
 
            outobj.vel_yaw = this.vel_yaw;
 
            outobj.acc_roll = this.acc_roll;
 
            outobj.acc_pitch = this.acc_pitch;
 
            outobj.acc_yaw = this.acc_yaw;
 
            outobj.omega_x = this.omega_x;
 
            outobj.omega_y = this.omega_y;
 
            outobj.omega_z = this.omega_z;
 
            outobj.omega_acc_x = this.omega_acc_x;
 
            outobj.omega_acc_y = this.omega_acc_y;
 
            outobj.omega_acc_z = this.omega_acc_z;
 
            return outobj;
        }
    }
}

