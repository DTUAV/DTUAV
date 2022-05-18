cmake_minimum_required(VERSION 3.0.2)
project(dt_global_network_client)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  cloud_common
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a exec_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a exec_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs  # Or other packages containing msgs
# )

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a exec_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES iot_connection
  CATKIN_DEPENDS roscpp
  #DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
    include
     ${catkin_INCLUDE_DIRS}
     include/dt_global_network_client/*.h

     src/LinkSDK/components/bootstrap/*.h
     src/LinkSDK/components/das/inc/das/*.h
     src/LinkSDK/components/das/inc/*.h
     src/LinkSDK/components/das/*.h
     src/LinkSDK/components/das/src/board/linux/*.h
     src/LinkSDK/components/das/src/core/proto/*.h
     src/LinkSDK/components/das/src/service/compat/netinet/*.h
     src/LinkSDK/components/data-model/*.h
     src/LinkSDK/components/devinfo/*.h
     src/LinkSDK/components/diag/*.h
     src/LinkSDK/components/logpost/*.h
     src/LinkSDK/components/ntp/*.h
     src/LinkSDK/components/ota/*.h
     src/LinkSDK/components/shadow/*.h
     src/LinkSDK/components/subdev/*.h
     src/LinkSDK/core/*.h
     src/LinkSDK/core/sysdep/*.h
     src/LinkSDK/core/utils/*.h
     src/LinkSDK/external/mbedtls/include/mbedtls/*.h
)

## Declare a C++ library
 add_library(iot SHARED
            src/LinkSDK/components/bootstrap/aiot_bootstrap_api.c
            src/LinkSDK/components/das/aiot_das_api.c
            src/LinkSDK/components/das/src/board/linux/das_board.c
            src/LinkSDK/components/das/src/core/das_attest.c
            src/LinkSDK/components/das/src/core/das_core.c
            src/LinkSDK/components/das/src/core/sha1.c
            src/LinkSDK/components/das/src/core/utils.c
            src/LinkSDK/components/das/src/core/proto/lsoc.pb.c
            src/LinkSDK/components/das/src/core/proto/pb_common.c
            src/LinkSDK/components/das/src/core/proto/pb_decode.c
            src/LinkSDK/components/das/src/core/proto/pb_encode.c
            src/LinkSDK/components/das/src/service/service.c
            src/LinkSDK/components/das/src/service/service_fscan.c
            src/LinkSDK/components/das/src/service/service_rom.c
            src/LinkSDK/components/das/src/service/service_sys.c
            src/LinkSDK/components/das/src/service/netfilter/domain_parser.c
            src/LinkSDK/components/das/src/service/netfilter/icmp_ignore.c
            src/LinkSDK/components/das/src/service/netfilter/service_netfilter.c
            src/LinkSDK/components/data-model/aiot_dm_api.c
            src/LinkSDK/components/devinfo/aiot_devinfo_api.c
            src/LinkSDK/components/diag/aiot_diag_api.c
            src/LinkSDK/components/logpost/aiot_logpost_api.c
            src/LinkSDK/components/ntp/aiot_ntp_api.c
            src/LinkSDK/components/ota/aiot_ota_api.c
            src/LinkSDK/components/ota/ota_md5.c
            src/LinkSDK/components/shadow/aiot_shadow_api.c
            src/LinkSDK/components/subdev/aiot_subdev_api.c
            src/LinkSDK/components/subdev/cJSON.c
            src/LinkSDK/core/aiot_mqtt_api.c
            src/LinkSDK/core/aiot_state_api.c
            src/LinkSDK/core/sysdep/core_sysdep.c
            src/LinkSDK/core/utils/core_auth.c
            src/LinkSDK/core/utils/core_diag.c
            src/LinkSDK/core/utils/core_global.c
            src/LinkSDK/core/utils/core_http.c
            src/LinkSDK/core/utils/core_log.c
            src/LinkSDK/core/utils/core_sha256.c
            src/LinkSDK/core/utils/core_string.c
            src/LinkSDK/external/ali_ca_cert.c
            src/LinkSDK/external/mbedtls/library/aes.c
            src/LinkSDK/external/mbedtls/library/asn1parse.c
            src/LinkSDK/external/mbedtls/library/base64.c
            src/LinkSDK/external/mbedtls/library/bignum.c
            src/LinkSDK/external/mbedtls/library/cipher.c
            src/LinkSDK/external/mbedtls/library/cipher_wrap.c
            src/LinkSDK/external/mbedtls/library/ctr_drbg.c
            src/LinkSDK/external/mbedtls/library/debug.c
            src/LinkSDK/external/mbedtls/library/entropy.c
            src/LinkSDK/external/mbedtls/library/entropy_poll.c
            src/LinkSDK/external/mbedtls/library/error.c
            src/LinkSDK/external/mbedtls/library/md.c
            src/LinkSDK/external/mbedtls/library/md_wrap.c
            src/LinkSDK/external/mbedtls/library/net_sockets.c
            src/LinkSDK/external/mbedtls/library/oid.c
            src/LinkSDK/external/mbedtls/library/pem.c
            src/LinkSDK/external/mbedtls/library/pk.c
            src/LinkSDK/external/mbedtls/library/pk_wrap.c
            src/LinkSDK/external/mbedtls/library/pkparse.c
            src/LinkSDK/external/mbedtls/library/platform.c
            src/LinkSDK/external/mbedtls/library/rsa.c
            src/LinkSDK/external/mbedtls/library/sha1.c
            src/LinkSDK/external/mbedtls/library/sha256.c
            src/LinkSDK/external/mbedtls/library/ssl_ciphersuites.c
            src/LinkSDK/external/mbedtls/library/ssl_cli.c
            src/LinkSDK/external/mbedtls/library/ssl_cookie.c
            src/LinkSDK/external/mbedtls/library/ssl_tls.c
            src/LinkSDK/external/mbedtls/library/timing.c
            src/LinkSDK/external/mbedtls/library/x509.c
            src/LinkSDK/external/mbedtls/library/x509_crt.c
            src/LinkSDK/portfiles/aiot_port/posix_port.c
 )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(${PROJECT_NAME}_node src/cloud_connection.cpp)

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
 target_link_libraries(${PROJECT_NAME}_node
   ${catkin_LIBRARIES}
   iot
   function_common
 )

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# catkin_install_python(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_executables.html
# install(TARGETS ${PROJECT_NAME}_node
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark libraries for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_libraries.html
# install(TARGETS ${PROJECT_NAME}
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_iot_connection.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
