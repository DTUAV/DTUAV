using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace DigitalTwin.UavCarProject
{
    public class message_id
    {
        //The packet_id for all uavs(0-100)

        //The packet_id for all cars(101-200)

        //The packet_id for all servers(201-300)

        //The packet_id for all simulators(301-400)

        //The packet_id for others(401-500)

        //The packet_id for vr and ar(501-600)
        public static int VR_REF_UAV_POSITION_ID = 501;
        public static int VR_REF_CAR_POSITION_ID = 502;
        public static int VR_REF_CAR_POSITIONDIR_ID = 503;
    }
}
