cmake_minimum_required(VERSION 3.5)
project(yasmin_pyrobosim_bringup)

find_package(ament_cmake REQUIRED)

install(
  DIRECTORY launch worlds
  DESTINATION share/${PROJECT_NAME}
)

ament_package()