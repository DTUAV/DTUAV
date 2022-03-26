#ifndef ROS_MSG_COMMON_H
#define ROS_MSG_COMMON_H
#include <iostream>
#include <x2struct/x2struct.hpp>
using namespace std;
typedef unsigned char byte ;
namespace DTUAVCARS_ROS {
struct Bool
{
    bool data;
    XTOSTRUCT(O(data));
};

struct Byte
{
   byte data;
   XTOSTRUCT(O(data));
};

struct MultiArrayDimension
{
    string label;
    uint32_t size;
    uint32_t stride;
    XTOSTRUCT(O(label,size,stride));
};

struct MultiArrayLayout
{
    vector<MultiArrayDimension> dim;
    uint32_t data_offset;
    XTOSTRUCT(O(dim,data_offset));
};

struct ByteMultiArray
{
    vector<MultiArrayLayout> layout;
    vector<byte> data;
    XTOSTRUCT(O(layout,data));
};

struct Char
{
    char data;
    XTOSTRUCT(O(data));
};

struct ColorRGBA
{
    float r;
    float g;
    float b;
    float a;
    XTOSTRUCT(O(r,g,b,a));
};

struct duration
{
    int32_t sec;
    int32_t nsec;
    XTOSTRUCT(O(sec,nsec));
};

struct Duration
{
    duration data;
    XTOSTRUCT(O(data));
};

struct Float32
{
    float data;
    XTOSTRUCT(O(data));
};

struct Float32MultiArray
{
    MultiArrayLayout layout;
    vector<float> data;
    XTOSTRUCT(O(layout,data));
};
struct Empty
{
   //XTOSTRUCT(O(NULL));
};

struct Float64
{
    double data;
    XTOSTRUCT(O(data));
};
struct Float64MultiArray
{
    MultiArrayLayout layout;
    vector<double> data;
    XTOSTRUCT(O(layout,data));
};

struct time
{
    int64_t sec;
    int64_t nsec;
    XTOSTRUCT(O(sec,nsec));
};

struct Header
{
   uint32_t seq;
   time stamp;
   string frame_id;
   XTOSTRUCT(O(seq,stamp,frame_id));
};

struct Int16
{
    int16_t data;
    XTOSTRUCT(O(data));
};

struct Int16MultiArray
{
    MultiArrayLayout layout;
    vector<int16_t> data;
    XTOSTRUCT(O(layout,data));
};

struct Int32
{
    int32_t data;
    XTOSTRUCT(O(data));
};

struct Int32MultiArray
{
    MultiArrayLayout layout;
    vector<int32_t> data;
    XTOSTRUCT(O(layout,data));
};
struct Int64
{
    int64_t data;
    XTOSTRUCT(O(data));
};

struct Int64MultiArray
{
    MultiArrayLayout layout;
    vector<int64_t> data;
    XTOSTRUCT(O(layout,data));
};
struct Int8
{
    int8_t data;
    XTOSTRUCT(O(data));
};

struct Int8MultiArray
{
    MultiArrayLayout layout;
    vector<int8_t> data;
    XTOSTRUCT(O(layout,data));
};

struct String
{
    string data;
    XTOSTRUCT(O(data));
};

struct Time
{
    time data;
    XTOSTRUCT(O(data));
};
struct UInt16
{
    uint16_t data;
    XTOSTRUCT(O(data));
};

struct UInt16MultiArray
{
    MultiArrayLayout layout;
    vector<uint16_t> data;
    XTOSTRUCT(O(layout,data));
};
struct UInt32
{
    uint32_t data;
    XTOSTRUCT(O(data));
};

struct UInt32MultiArray
{
    MultiArrayLayout layout;
    vector<uint32_t> data;
    XTOSTRUCT(O(layout,data));
};
struct UInt64
{
    uint64_t data;
    XTOSTRUCT(O(data));
};

struct UInt64MultiArray
{
    MultiArrayLayout layout;
    vector<uint64_t> data;
    XTOSTRUCT(O(layout,data));
};

struct UInt8
{
    uint8_t data;
    XTOSTRUCT(O(data));
};

struct UInt8MultiArray
{
    MultiArrayLayout layout;
    vector<uint8_t> data;
    XTOSTRUCT(O(layout,data));
};

struct Vector3
{
    double x;
    double y;
    double z;
    XTOSTRUCT(O(x,y,z));
};

struct Vector3Stamped
{
    Header header;
    Vector3 vector3;
    XTOSTRUCT(O(header,vector3));
};

struct Accel
{
    Vector3 linear;
    Vector3 angular;
    XTOSTRUCT(O(linear,angular));
};

struct AccelStamped
{
    Header header;
    Accel accel;
    XTOSTRUCT(O(header,accel));
};
struct AccelWithCovariance
{
    Accel accel;
    vector<double> covariance;
    XTOSTRUCT(O(accel,covariance));
};

struct AccelWithCovarianceStamped
{
    Header header;
    AccelWithCovariance accel;
    XTOSTRUCT(O(header,accel));
};

struct Inertia
{
    double m;
    Vector3 com;
    double ixx;
    double ixy;
    double ixz;
    double iyy;
    double iyz;
    double izz;
    XTOSTRUCT(O(m,com,ixx,ixy,ixz,iyy,iyz,izz));
};

struct InertiaStamped
{
    Header header;
    Inertia inertia;
    XTOSTRUCT(O(header,inertia));
};

struct Point
{
    double x;
    double y;
    double z;
    XTOSTRUCT(O(x,y,z));
};

struct Point32
{
    float x;
    float y;
    float z;
    XTOSTRUCT(O(x,y,z));
};

struct PointStamped
{
    Header header;
    Point point;
    XTOSTRUCT(O(header,point));
};

struct Polygon
{
    vector<Point32> points;
    XTOSTRUCT(O(points));
};

struct PolygonStamped
{
    Header header;
    Polygon polygon;
    XTOSTRUCT(O(header,polygon));
};

struct Quaternion
{
    double x;
    double y;
    double z;
    double w;
    XTOSTRUCT(O(x,y,z,w));
};

struct QuaternionStamped
{
    Header header;
    Quaternion quaternion;
    XTOSTRUCT(O(header,quaternion));
};

struct Pose
{
    Point position;
    Quaternion orientation;
    XTOSTRUCT(O(position,orientation));
};

struct Pose2D
{
    double x;
    double y;
    double theta;
    XTOSTRUCT(O(x,y,theta));
};

struct PoseArray
{
    Header header;
    vector<Pose> poses;
    XTOSTRUCT(O(header,poses));
};

struct PoseStamped
{
    Header header;
    Pose pose;
    XTOSTRUCT(O(header,pose));
};

struct PoseWithCovariance
{
    Pose pose;
    vector<double> covariance;
    XTOSTRUCT(O(pose,covariance));
};

struct PoseWithCovarianceStamped
{
    Header header;
    PoseWithCovariance pose;
    XTOSTRUCT(O(header,pose));
};

struct Transform
{
    Vector3 translation;
    Quaternion rotation;
    XTOSTRUCT(O(translation,rotation));
};

struct TransformStamped
{
    Header header;
    string child_frame_id;
    Transform transform;
    XTOSTRUCT(O(header,child_frame_id,transform));
};

struct Twist
{
    Vector3 linear;
    Vector3 angular;
    XTOSTRUCT(O(linear,angular));
};

struct TwistStamped
{
    Header header;
    Twist twist;
    XTOSTRUCT(O(header,twist));
};

struct TwistWithCovariance
{
    Twist twist;
    vector<double> covariance;
    XTOSTRUCT(O(twist,covariance));
};

struct TwistWithCovarianceStamped
{
    Header header;
    TwistWithCovariance twist;
    XTOSTRUCT(O(header,twist));
};

struct Wrench
{
    Vector3 force;
    Vector3 torque;
    XTOSTRUCT(O(force,torque));
};

struct WrenchStamped
{
    Header header;
    Wrench wrench;
    XTOSTRUCT(O(header,wrench));
};

struct GridCells
{
    Header header;
    float cell_width;
    float cell_height;
    vector<Point> cells;
    XTOSTRUCT(O(header,cell_width,cell_height,cells));
};

struct MapMetaData
{
    time map_load_time;
    float resolution;
    uint32_t width;
    uint32_t height;
    Pose origin;
    XTOSTRUCT(O(map_load_time,resolution,width,height,origin));
};

struct OccupancyGrid
{
    Header header;
    MapMetaData info;
    vector<int8_t> data;
    XTOSTRUCT(O(header,info,data));
};

struct Odometry
{
    Header header;
    string child_frame_id;
    PoseWithCovariance pose;
    TwistWithCovariance twist;
    XTOSTRUCT(O(header,child_frame_id,pose,twist));
};

struct Path
{
    Header header;
    vector<PoseStamped> poses;
    XTOSTRUCT(O(header,poses));
};
struct BatteryState
{
    //# Power supply status constants
    uint8_t POWER_SUPPLY_STATUS_UNKNOWN = 0;
    uint8_t POWER_SUPPLY_STATUS_CHARGING = 1;
    uint8_t POWER_SUPPLY_STATUS_DISCHARGING = 2;
    uint8_t POWER_SUPPLY_STATUS_NOT_CHARGING = 3;
    uint8_t POWER_SUPPLY_STATUS_FULL = 4;

   // # Power supply health constants
    uint8_t POWER_SUPPLY_HEALTH_UNKNOWN = 0;
    uint8_t POWER_SUPPLY_HEALTH_GOOD = 1;
    uint8_t POWER_SUPPLY_HEALTH_OVERHEAT = 2;
    uint8_t POWER_SUPPLY_HEALTH_DEAD = 3;
    uint8_t POWER_SUPPLY_HEALTH_OVERVOLTAGE = 4;
    uint8_t POWER_SUPPLY_HEALTH_UNSPEC_FAILURE = 5;
    uint8_t POWER_SUPPLY_HEALTH_COLD = 6;
    uint8_t POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE = 7;
    uint8_t POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE = 8;

   // # Power supply technology (chemistry) constants
    uint8_t POWER_SUPPLY_TECHNOLOGY_UNKNOWN = 0;
    uint8_t POWER_SUPPLY_TECHNOLOGY_NIMH = 1;
    uint8_t POWER_SUPPLY_TECHNOLOGY_LION = 2;
    uint8_t POWER_SUPPLY_TECHNOLOGY_LIPO = 3;
    uint8_t POWER_SUPPLY_TECHNOLOGY_LIFE = 4;
    uint8_t POWER_SUPPLY_TECHNOLOGY_NICD = 5;
    uint8_t POWER_SUPPLY_TECHNOLOGY_LIMN = 6;

    Header  header;
    float voltage;        //  # Voltage in Volts (Mandatory)
    float current ;//         # Negative when discharging (A)  (If unmeasured NaN)
    float charge  ;//         # Current charge in Ah  (If unmeasured NaN)
    float capacity;//         # Capacity in Ah (last full capacity)  (If unmeasured NaN)
    float design_capacity;//  # Capacity in Ah (design capacity)  (If unmeasured NaN)
    float percentage;//       # Charge percentage on 0 to 1 range  (If unmeasured NaN)
    uint8_t   power_supply_status;//     # The charging status as reported. Values defined above
    uint8_t   power_supply_health;//     # The battery health metric. Values defined above
    uint8_t   power_supply_technology;// # The battery chemistry. Values defined above
    bool    present;//          # True if the battery is present

    vector<float> cell_voltage;//   # An array of individual cell voltages for each cell in the pack
                          //   # If individual voltages unknown but number of cells known set each to NaN
    string location; //         # The location into which the battery is inserted. (slot number or plug)
    string serial_number;//     # The best approximation of the battery serial number

    XTOSTRUCT(O(header,voltage,current,charge,capacity,design_capacity,percentage,power_supply_status,power_supply_health,power_supply_technology,present,cell_voltage,location,serial_number));
};
 struct RegionOfInterest
{
    uint32_t x_offset;//Leftmost pixel of the ROI
    uint32_t y_offset;//Topmost pixel of the ROI
    uint32_t height;//Height of ROI
    uint32_t width;//Width of ROI
    bool do_rectify;
    XTOSTRUCT(O(x_offset,y_offset,height,width,do_rectify));
};

 struct CameraInfo
 {
     Header header;
     uint32_t height;
     uint32_t width;
     string distortion_model;
     vector<double> D;
     vector<double> K;
     vector<double> R;
     vector<double> P;
     uint32_t binning_x;
     uint32_t binning_y;
     RegionOfInterest roi;
     XTOSTRUCT(O(header,height,width,distortion_model,D,K,R,P,binning_x,binning_y,roi));
 };

 struct ChannelFloat32
 {
     string name;
     vector<float> value;
     XTOSTRUCT(O(name,value));
 };

 struct CompressedImage
 {
     Header header;
     string format;
     vector<uint8_t> data;
     XTOSTRUCT(O(header,format,data));
 };

 struct FluidPressure
 {
     Header header;
     double fluid_pressure;
     double variance;
     XTOSTRUCT(O(header,fluid_pressure,variance));
 };

 struct Illuminance
 {
     Header header;
     double illuminance;
     double variance;
     XTOSTRUCT(O(header,illuminance,variance));
 };

 struct Image
 {
     Header header;
     uint32_t height;
     uint32_t width;
     string encoding;
     uint8_t is_bigendian;
     uint32_t step;
     vector<uint8_t> data;
     XTOSTRUCT(O(header,height,width,encoding,is_bigendian,step,data));
 };

 struct Imu
 {
    Header header;
    Quaternion orientation;
    vector<double> orientation_covariance;
    Vector3 angular_velocity;
    vector<double> angular_velocity_covariance;
    Vector3 linear_acceleration;
   vector<double> linear_acceleration_covariance;
    XTOSTRUCT(O(header,orientation,orientation_covariance,angular_velocity,angular_velocity_covariance,linear_acceleration,linear_acceleration_covariance));
 };

struct JointState
{
    Header header;
    vector<string> name;
    vector<double> position;
    vector<double> velocity;
    vector<double> effort;
    XTOSTRUCT(O(header,name,position,velocity,effort));

};

struct Joy
{
    Header header;
    vector<float> axes;
    vector<int32_t> buttons;
    XTOSTRUCT(O(header,axes,buttons));
};

struct JoyFeedback
{
    uint8_t TYPE_LED=0;
    uint8_t TYPE_RUMBLE=1;
    uint8_t TYPE_BUZZER=2;
    uint8_t type;
    uint8_t id;
    float intensity;
    XTOSTRUCT(O(type,id,intensity));
};

struct JoyFeedbackArray
{
    vector<JoyFeedback> array;
    XTOSTRUCT(O(array));
};

struct LaserEcho
{
    vector<float> echoes;
    XTOSTRUCT(O(echoes));
};

struct LaserScan
{
    Header header;
    float angle_min;
    float angle_max;
    float angle_increment;
    float time_increment;
    float scan_time;
    float range_min;
    float range_max;
    vector<float> ranges;
    vector<float> intensities;
    XTOSTRUCT(O(header,angle_min,angle_max,angle_increment,time_increment,scan_time,range_min,range_max,ranges,intensities));
};

struct MagneticField
{
    Header header;
    Vector3 magnetic_field;
    vector<double> magnetic_field_covariance;
    XTOSTRUCT(O(header,magnetic_field,magnetic_field_covariance));
};

struct MultiDOFJointState
{
    Header header;
    vector<string> joint_names;
    vector<Transform> transforms;
    vector<Twist> twist;
    vector<Wrench> wrench;
    XTOSTRUCT(O(header,joint_names,transforms,twist,wrench));
};

struct MultiEchoLaserScan
{
    Header header;
    float angle_min;
    float angle_max;
    float angle_increment;
    float time_increment;
    float scan_time;
    float range_min;
    float range_max;
    vector<LaserEcho> ranges;
    vector<LaserEcho> intensities;
    XTOSTRUCT(O(header,angle_min,angle_max,angle_increment,time_increment,scan_time,range_min,range_max,ranges,intensities));
};

struct NavSatStatus
{
    int8_t STATUS_NO_FIX=-1;
    int8_t STATUS_FIX=0;
    int8_t STATUS_SBAS_FIX=1;
    int8_t STATUS_GBAS_FIX=2;
    uint16_t SERVICE_GPS=1;
    uint16_t SERVICE_GLONASS=2;
    uint16_t SERVICE_COMPASS=4;
    uint16_t SERVICE_GALILEO=8;
    int8_t status;
    uint16_t service;
    XTOSTRUCT(O(status,service));
};

struct NavSatFix
{
    uint8_t COVARIANCE_TYPE_UNKNOWN=0;
    uint8_t COVARIANCE_TYPE_APPROXIMATED=1;
    uint8_t COVARIANCE_TYPE_DIAGONAL_KNOWN=2;
    uint8_t COVARIANCE_TYPE_KNOWN=3;
    Header header;
    NavSatStatus status;
    double latitude;
    double longitude;
    double altitude;
    vector<double> position_covariance;
    uint8_t position_covariance_type;
    XTOSTRUCT(O(header,status,latitude,longitude,altitude,position_covariance,position_covariance_type));
};

struct PointCloud
{
    Header header;
    vector<Point32> points;
    vector<ChannelFloat32> channels;
    XTOSTRUCT(O(header,points,channels));
};

struct PointField
{
    uint8_t INT8=1;
    uint8_t UINT8=2;
    uint8_t INT16=3;
    uint8_t UINT16=4;
    uint8_t INT32=5;
    uint8_t UINT32=6;
    uint8_t FLOAT32=7;
    uint8_t FLOAT64=8;
    string name;
    uint32_t offset;
    uint8_t datatype;
    uint32_t count;
    XTOSTRUCT(O(name,offset,datatype,count));
};

struct PointCloud2
{
    Header header;
    uint32_t height;
    uint32_t width;
    vector<PointField> fields;
    bool is_bigendian;
    uint32_t point_step;
    uint32_t row_step;
    vector<uint8_t> data;
    bool is_dense;
    XTOSTRUCT(O(header,height,width,fields,is_bigendian,point_step,row_step,data,is_dense));
};

struct Range
{
    uint8_t ULTRASOUND=0;
    uint8_t INFRARED=1;
    Header header;
    uint8_t radiation_type;
    float field_of_view;
    float min_range;
    float max_range;
    float range;
    XTOSTRUCT(O(header,radiation_type,field_of_view,min_range,max_range,range));
};

struct RelativeHumidity
{
    Header header;
    double relative_humidity;
    double variance;
    XTOSTRUCT(O(header,relative_humidity,variance));
};

struct Temperature
{
    Header header;
    double temperature;
    double variance;
    XTOSTRUCT(O(header,temperature,variance));
};

struct TimeReference
{
    Header header;
    time time_ref;
    string source;
    XTOSTRUCT(O(header,time_ref,source));
};

struct GoalID
{
    time stamp;
    string id;
    XTOSTRUCT(O(stamp,id));
};

struct GoalStatus
{
    uint8_t PENDING=0;
    uint8_t ACTIVE=1;
    uint8_t PREEMPTED=2;
    uint8_t SUCCEEDED=3;
    uint8_t ABORTED=4;
    uint8_t REJECTED=5;
    uint8_t PREEMPTING=6;
    uint8_t RECALLING=7;
    uint8_t RECALLED=8;
    uint8_t LOST=9;
    GoalID goal_id;
    uint8_t status;
    string text;
    XTOSTRUCT(O(goal_id,status,text));
};

struct GoalStatusArray
{
    Header header;
    vector<GoalStatus> status_list;
    XTOSTRUCT(O(header,status_list));
};

struct KeyValue
{
    string key;
    string value;
    XTOSTRUCT(O(key,value));
};

struct DiagnosticStatus
{
    byte OK=0;
    byte WARN=1;
    byte ERROR=2;
    byte STALE=3;
    byte level;
    string name;
    string message;
    string hardware_id;
    vector<KeyValue> values;
    XTOSTRUCT(O(level,name,message,hardware_id,values));
};

struct DiagnosticArray
{
    Header header;
    vector<DiagnosticStatus> status;
    XTOSTRUCT(O(header,status));
};
}
#endif // ROS_MSG_COMMON_H
