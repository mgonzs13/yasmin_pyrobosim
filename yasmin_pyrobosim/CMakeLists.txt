cmake_minimum_required(VERSION 3.5)
project(yasmin_pyrobosim)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rclpy REQUIRED)
find_package(pluginlib REQUIRED)
find_package(yasmin REQUIRED)
find_package(yasmin_ros REQUIRED)
find_package(yasmin_viewer REQUIRED)
find_package(yasmin_factory REQUIRED)
find_package(pyrobosim_msgs REQUIRED)

# C++
include_directories(src)
include_directories(include)

set(DEPENDENCIES
  rclcpp::rclcpp
  rclcpp_action::rclcpp_action
  pluginlib::pluginlib
  yasmin::yasmin
  yasmin_ros::yasmin_ros
  yasmin_viewer::yasmin_viewer
  yasmin_factory::yasmin_factory
  ${pyrobosim_msgs_TARGETS}
)
set(DEPENDENCIES_PACKAGE
  rclcpp
  rclcpp_action
  pluginlib
  yasmin
  yasmin_ros
  yasmin_viewer
  yasmin_factory
  pyrobosim_msgs
)

# plugins
add_library(navigate_state SHARED src/navigate_state.cpp)
target_link_libraries(navigate_state PUBLIC ${DEPENDENCIES})
pluginlib_export_plugin_description_file(yasmin resource/plugins.xml)
install(TARGETS navigate_state
  LIBRARY DESTINATION lib
)

add_library(get_robot_params_state SHARED src/get_robot_params_state.cpp)
target_link_libraries(get_robot_params_state PUBLIC ${DEPENDENCIES})
install(TARGETS get_robot_params_state
  LIBRARY DESTINATION lib
)

add_library(get_world_state_state SHARED src/get_world_state_state.cpp)
target_link_libraries(get_world_state_state PUBLIC ${DEPENDENCIES})
install(TARGETS get_world_state_state
  LIBRARY DESTINATION lib
)

add_library(pick_random_location SHARED src/pick_random_location.cpp)
target_link_libraries(pick_random_location PUBLIC ${DEPENDENCIES})
install(TARGETS pick_random_location
  LIBRARY DESTINATION lib
)

add_library(get_next_location_state SHARED src/get_next_location_state.cpp)
target_link_libraries(get_next_location_state PUBLIC ${DEPENDENCIES})
install(TARGETS get_next_location_state
  LIBRARY DESTINATION lib
)

add_library(order_locations_state SHARED src/order_locations_state.cpp)
target_link_libraries(order_locations_state PUBLIC ${DEPENDENCIES})
install(TARGETS order_locations_state
  LIBRARY DESTINATION lib
)

add_library(detect_objects_state SHARED src/detect_objects_state.cpp)
target_link_libraries(detect_objects_state PUBLIC ${DEPENDENCIES})
install(TARGETS detect_objects_state
  LIBRARY DESTINATION lib
)

add_library(pick_object_state SHARED src/pick_object_state.cpp)
target_link_libraries(pick_object_state PUBLIC ${DEPENDENCIES})
install(TARGETS pick_object_state
  LIBRARY DESTINATION lib
)

add_library(place_object_state SHARED src/place_object_state.cpp)
target_link_libraries(place_object_state PUBLIC ${DEPENDENCIES})
install(TARGETS place_object_state
  LIBRARY DESTINATION lib
)

# Install state_machines directory
install(DIRECTORY state_machines
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()