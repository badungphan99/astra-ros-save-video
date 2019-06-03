cmake_minimum_required(VERSION 2.8.3)
project(video_save)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
)

set(OpenCV_STATIC OFF)
find_package(  OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES lane_detect
#  CATKIN_DEPENDS cv_bridge image_transport roscpp sensor_msgs
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(video_depth src/video_depth.cpp)
add_executable(video_color src/video_color.cpp)
add_executable(video_save src/main.cpp)

add_dependencies(video_depth ${catkin_EXPORTED_TARGETS})
add_dependencies(video_color ${catkin_EXPORTED_TARGETS})
add_dependencies(video_save ${catkin_EXPORTED_TARGETS})

target_link_libraries( video_depth ${catkin_LIBRARIES} ${OpenCV_LIBS} ${Boost_LIBRARIES})
target_link_libraries( video_color ${catkin_LIBRARIES} ${OpenCV_LIBS} ${Boost_LIBRARIES})
target_link_libraries( video_save ${catkin_LIBRARIES} ${OpenCV_LIBS} ${Boost_LIBRARIES})

