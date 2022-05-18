// Generated by gencpp from file mavros_msgs/Param.msg
// DO NOT EDIT!


#ifndef MAVROS_MSGS_MESSAGE_PARAM_H
#define MAVROS_MSGS_MESSAGE_PARAM_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <mavros_msgs/ParamValue.h>

namespace mavros_msgs
{
template <class ContainerAllocator>
struct Param_
{
  typedef Param_<ContainerAllocator> Type;

  Param_()
    : header()
    , param_id()
    , value()
    , param_index(0)
    , param_count(0)  {
    }
  Param_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , param_id(_alloc)
    , value(_alloc)
    , param_index(0)
    , param_count(0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _param_id_type;
  _param_id_type param_id;

   typedef  ::mavros_msgs::ParamValue_<ContainerAllocator>  _value_type;
  _value_type value;

   typedef uint16_t _param_index_type;
  _param_index_type param_index;

   typedef uint16_t _param_count_type;
  _param_count_type param_count;





  typedef boost::shared_ptr< ::mavros_msgs::Param_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::mavros_msgs::Param_<ContainerAllocator> const> ConstPtr;

}; // struct Param_

typedef ::mavros_msgs::Param_<std::allocator<void> > Param;

typedef boost::shared_ptr< ::mavros_msgs::Param > ParamPtr;
typedef boost::shared_ptr< ::mavros_msgs::Param const> ParamConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::mavros_msgs::Param_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::mavros_msgs::Param_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::mavros_msgs::Param_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mavros_msgs::Param_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mavros_msgs::Param_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mavros_msgs::Param_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mavros_msgs::Param_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mavros_msgs::Param_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::mavros_msgs::Param_<ContainerAllocator> >
{
  static const char* value()
  {
    return "62165a8f212050223dda9583b0f22c3c";
  }

  static const char* value(const ::mavros_msgs::Param_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x62165a8f21205022ULL;
  static const uint64_t static_value2 = 0x3dda9583b0f22c3cULL;
};

template<class ContainerAllocator>
struct DataType< ::mavros_msgs::Param_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mavros_msgs/Param";
  }

  static const char* value(const ::mavros_msgs::Param_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::mavros_msgs::Param_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# Parameter msg.\n\
\n\
std_msgs/Header header\n\
\n\
string param_id\n\
mavros_msgs/ParamValue value\n\
\n\
uint16 param_index\n\
uint16 param_count\n\
\n\
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
\n\
================================================================================\n\
MSG: mavros_msgs/ParamValue\n\
# Parameter value storage type.\n\
#\n\
# Integer and float fields:\n\
#\n\
# if integer != 0: it is integer value\n\
# else if real != 0.0: it is float value\n\
# else: it is zero.\n\
\n\
int64 integer\n\
float64 real\n\
";
  }

  static const char* value(const ::mavros_msgs::Param_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::mavros_msgs::Param_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.param_id);
      stream.next(m.value);
      stream.next(m.param_index);
      stream.next(m.param_count);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Param_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::mavros_msgs::Param_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::mavros_msgs::Param_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "param_id: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.param_id);
    s << indent << "value: ";
    s << std::endl;
    Printer< ::mavros_msgs::ParamValue_<ContainerAllocator> >::stream(s, indent + "  ", v.value);
    s << indent << "param_index: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.param_index);
    s << indent << "param_count: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.param_count);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MAVROS_MSGS_MESSAGE_PARAM_H
