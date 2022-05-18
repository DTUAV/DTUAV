// Generated by gencpp from file mavros_msgs/MountControl.msg
// DO NOT EDIT!


#ifndef MAVROS_MSGS_MESSAGE_MOUNTCONTROL_H
#define MAVROS_MSGS_MESSAGE_MOUNTCONTROL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace mavros_msgs
{
template <class ContainerAllocator>
struct MountControl_
{
  typedef MountControl_<ContainerAllocator> Type;

  MountControl_()
    : header()
    , mode(0)
    , pitch(0.0)
    , roll(0.0)
    , yaw(0.0)
    , altitude(0.0)
    , latitude(0.0)
    , longitude(0.0)  {
    }
  MountControl_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , mode(0)
    , pitch(0.0)
    , roll(0.0)
    , yaw(0.0)
    , altitude(0.0)
    , latitude(0.0)
    , longitude(0.0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef uint8_t _mode_type;
  _mode_type mode;

   typedef float _pitch_type;
  _pitch_type pitch;

   typedef float _roll_type;
  _roll_type roll;

   typedef float _yaw_type;
  _yaw_type yaw;

   typedef float _altitude_type;
  _altitude_type altitude;

   typedef float _latitude_type;
  _latitude_type latitude;

   typedef float _longitude_type;
  _longitude_type longitude;



  enum {
    MAV_MOUNT_MODE_RETRACT = 0u,
    MAV_MOUNT_MODE_NEUTRAL = 1u,
    MAV_MOUNT_MODE_MAVLINK_TARGETING = 2u,
    MAV_MOUNT_MODE_RC_TARGETING = 3u,
    MAV_MOUNT_MODE_GPS_POINT = 4u,
  };


  typedef boost::shared_ptr< ::mavros_msgs::MountControl_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::mavros_msgs::MountControl_<ContainerAllocator> const> ConstPtr;

}; // struct MountControl_

typedef ::mavros_msgs::MountControl_<std::allocator<void> > MountControl;

typedef boost::shared_ptr< ::mavros_msgs::MountControl > MountControlPtr;
typedef boost::shared_ptr< ::mavros_msgs::MountControl const> MountControlConstPtr;

// constants requiring out of line definition

   

   

   

   

   



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::mavros_msgs::MountControl_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::mavros_msgs::MountControl_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace mavros_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'geographic_msgs': ['/opt/ros/kinetic/share/geographic_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'mavros_msgs': ['/home/map/catkin_ws/src/mavros/mavros_msgs/msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'uuid_msgs': ['/opt/ros/kinetic/share/uuid_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::mavros_msgs::MountControl_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mavros_msgs::MountControl_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mavros_msgs::MountControl_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mavros_msgs::MountControl_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mavros_msgs::MountControl_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mavros_msgs::MountControl_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::mavros_msgs::MountControl_<ContainerAllocator> >
{
  static const char* value()
  {
    return "214cf13a68b4fed9e2a77b1b436f144e";
  }

  static const char* value(const ::mavros_msgs::MountControl_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x214cf13a68b4fed9ULL;
  static const uint64_t static_value2 = 0xe2a77b1b436f144eULL;
};

template<class ContainerAllocator>
struct DataType< ::mavros_msgs::MountControl_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mavros_msgs/MountControl";
  }

  static const char* value(const ::mavros_msgs::MountControl_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::mavros_msgs::MountControl_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# MAVLink message: DO_MOUNT_CONTROL\n\
# https://mavlink.io/en/messages/common.html#MAV_CMD_DO_MOUNT_CONTROL\n\
\n\
std_msgs/Header header\n\
\n\
uint8 mode # See enum MAV_MOUNT_MODE.\n\
uint8 MAV_MOUNT_MODE_RETRACT = 0\n\
uint8 MAV_MOUNT_MODE_NEUTRAL = 1\n\
uint8 MAV_MOUNT_MODE_MAVLINK_TARGETING = 2\n\
uint8 MAV_MOUNT_MODE_RC_TARGETING = 3\n\
uint8 MAV_MOUNT_MODE_GPS_POINT = 4\n\
\n\
float32 pitch # roll degrees or degrees/second depending on mount mode.\n\
float32 roll # roll degrees or degrees/second depending on mount mode.\n\
float32 yaw # roll degrees or degrees/second depending on mount mode.\n\
float32 altitude  # altitude depending on mount mode.\n\
float32 latitude # latitude in degrees * 1E7, set if appropriate mount mode.\n\
float32 longitude # longitude in degrees * 1E7, set if appropriate mount mode.\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
";
  }

  static const char* value(const ::mavros_msgs::MountControl_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::mavros_msgs::MountControl_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.mode);
      stream.next(m.pitch);
      stream.next(m.roll);
      stream.next(m.yaw);
      stream.next(m.altitude);
      stream.next(m.latitude);
      stream.next(m.longitude);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct MountControl_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::mavros_msgs::MountControl_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::mavros_msgs::MountControl_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "mode: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.mode);
    s << indent << "pitch: ";
    Printer<float>::stream(s, indent + "  ", v.pitch);
    s << indent << "roll: ";
    Printer<float>::stream(s, indent + "  ", v.roll);
    s << indent << "yaw: ";
    Printer<float>::stream(s, indent + "  ", v.yaw);
    s << indent << "altitude: ";
    Printer<float>::stream(s, indent + "  ", v.altitude);
    s << indent << "latitude: ";
    Printer<float>::stream(s, indent + "  ", v.latitude);
    s << indent << "longitude: ";
    Printer<float>::stream(s, indent + "  ", v.longitude);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MAVROS_MSGS_MESSAGE_MOUNTCONTROL_H
