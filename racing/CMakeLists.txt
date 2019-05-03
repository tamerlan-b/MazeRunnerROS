cmake_minimum_required(VERSION 2.8.3)
project(racing)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  actionlib
  geometry_msgs
  move_base_msgs
  tf
)

catkin_package(
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node src/racing_node.cpp src/MazeRunner.cpp src/MazeRunner.h)

 target_link_libraries(${PROJECT_NAME}_node
   ${catkin_LIBRARIES}
 )
