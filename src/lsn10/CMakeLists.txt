cmake_minimum_required(VERSION 2.8.3)
project(lsn10)

add_compile_options(-std=c++14)
set( CMAKE_CXX_STANDARD 14)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs 
  std_srvs
  sensor_msgs
  message_generation
)
find_package(Boost REQUIRED)

generate_messages(DEPENDENCIES std_msgs)

catkin_package(CATKIN_DEPENDS roscpp std_srvs
rospy std_msgs message_runtime dynamic_reconfigure)


include_directories(include)
include_directories(${catkin_INCLUDE_DIRS})

add_executable(lsn10
                src/lsiosr.cpp
                src/lsn10.cpp)
add_dependencies(lsn10 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(lsn10 ${Boost_LIBRARIES} ${catkin_LIBRARIES})

install(TARGETS lsn10
    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY launch
    DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
