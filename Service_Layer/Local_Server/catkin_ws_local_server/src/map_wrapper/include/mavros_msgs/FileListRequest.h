// Generated by gencpp from file mavros_msgs/FileListRequest.msg
// DO NOT EDIT!


#ifndef MAVROS_MSGS_MESSAGE_FILELISTREQUEST_H
#define MAVROS_MSGS_MESSAGE_FILELISTREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace mavros_msgs
{
template <class ContainerAllocator>
struct FileListRequest_
{
  typedef FileListRequest_<ContainerAllocator> Type;

  FileListRequest_()
    : dir_path()  {
    }
  FileListRequest_(const ContainerAllocator& _alloc)
    : dir_path(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _dir_path_type;
  _dir_path_type dir_path;





  typedef boost::shared_ptr< ::mavros_msgs::FileListRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::mavros_msgs::FileListRequest_<ContainerAllocator> const> ConstPtr;

}; // struct FileListRequest_

typedef ::mavros_msgs::FileListRequest_<std::allocator<void> > FileListRequest;

typedef boost::shared_ptr< ::mavros_msgs::FileListRequest > FileListRequestPtr;
typedef boost::shared_ptr< ::mavros_msgs::FileListRequest const> FileListRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::mavros_msgs::FileListRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::mavros_msgs::FileListRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace mavros_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'geographic_msgs': ['/opt/ros/kinetic/share/geographic_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'mavros_msgs': ['/home/map/catkin_ws/src/mavros/mavros_msgs/msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'uuid_msgs': ['/opt/ros/kinetic/share/uuid_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::mavros_msgs::FileListRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mavros_msgs::FileListRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mavros_msgs::FileListRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mavros_msgs::FileListRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mavros_msgs::FileListRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mavros_msgs::FileListRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::mavros_msgs::FileListRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "401d5cf5f836aaa9ebdc0897f75da874";
  }

  static const char* value(const ::mavros_msgs::FileListRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x401d5cf5f836aaa9ULL;
  static const uint64_t static_value2 = 0xebdc0897f75da874ULL;
};

template<class ContainerAllocator>
struct DataType< ::mavros_msgs::FileListRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mavros_msgs/FileListRequest";
  }

  static const char* value(const ::mavros_msgs::FileListRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::mavros_msgs::FileListRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n\
\n\
\n\
\n\
\n\
string dir_path\n\
";
  }

  static const char* value(const ::mavros_msgs::FileListRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::mavros_msgs::FileListRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.dir_path);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct FileListRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::mavros_msgs::FileListRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::mavros_msgs::FileListRequest_<ContainerAllocator>& v)
  {
    s << indent << "dir_path: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.dir_path);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MAVROS_MSGS_MESSAGE_FILELISTREQUEST_H
