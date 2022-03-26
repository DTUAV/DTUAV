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

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using LCM;

namespace DTUAV.Network_Module.LCM_Network
{
    public class BasePub : MonoBehaviour
    {
        // Start is called before the first frame update
        public string MesageName;
        public float MessagePubHz;
        public LCM.LCM.LCM BaseLcm;

        public void BaseStart()
        {
            BaseLcm = LCM.LCM.LCM.Singleton;
        }



    }
}
