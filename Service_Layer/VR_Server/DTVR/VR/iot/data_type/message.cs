using System;


namespace DigitalTwin.UavCarProject
{
    //The message for all objects
    [Serializable]
    public class IOT_MSG
    {
        public int packet_object_to;//The packet object for communication like R_UAV_0(target_object)
        public int packet_object_from;//The packet object for communication like R_UAV_0(source_object)
        public int packet_id;//The packet id for communication like UAV_STATE_ID
        public string packet_data;//The packet data for communication (must othe msg like msg for all uavs and json format)
    }

    //The message for vr and ar 
    [Serializable]
    public class REF_UAV_POSITION_MSG
    {
        public float ref_position_x;
        public float ref_position_y;
        public float ref_position_z;
    }

    [Serializable]
    public class REF_CAR_POSITION_MSG
    {
        public float ref_position_x;
        public float ref_position_y;
    }

    [Serializable]
    public class REF_CAR_POSITIONDIR_MSG
    {
        public float distance;
        public float direction;
    }


}
