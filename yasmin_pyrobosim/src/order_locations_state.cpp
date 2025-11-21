
#include <cmath>
#include <memory>
#include <string>

#include "geometry_msgs/msg/pose.hpp"
#include "pyrobosim_msgs/msg/world_state.hpp"
#include "yasmin/state.hpp"
#include "yasmin_ros/basic_outcomes.hpp"

class OrderLocationsState : public yasmin::State {

public:
  OrderLocationsState()
      : yasmin::State({yasmin_ros::basic_outcomes::SUCCEED}) {};

  std::string
  execute(std::shared_ptr<yasmin::blackboard::Blackboard> blackboard) override {
    auto world_state =
        blackboard->get<pyrobosim_msgs::msg::WorldState>("world_state");

    // Get robot position
    geometry_msgs::msg::Pose robot_pose;
    for (auto robots : world_state.robots) {
      if (robots.name == blackboard->get<std::string>("robot_name")) {
        robot_pose = robots.pose;
      }
    }

    // Sort locations by distance to robot and consecutive locations
    auto locations = world_state.locations;
    std::vector<std::string> location_names;
    geometry_msgs::msg::Pose current_pose = robot_pose;
    std::vector<std::string> ordered_location_names;

    for (auto &location : locations) {
      location_names.push_back(location.name);
    }

    while (location_names.size() > 0) {
      double min_distance = std::numeric_limits<double>::max();
      std::string closest_location_name;
      geometry_msgs::msg::Pose closest_location_pose;

      for (auto &location : locations) {

        // Check if location is in the remaining names location_names
        if (std::find(location_names.begin(), location_names.end(),
                      location.name) == location_names.end()) {
          continue;
        }

        double distance = std::sqrt(
            std::pow(current_pose.position.x - location.pose.position.x, 2) +
            std::pow(current_pose.position.y - location.pose.position.y, 2));

        if (distance < min_distance) {
          min_distance = distance;
          closest_location_name = location.name;
          closest_location_pose = location.pose;
        }
      }

      current_pose = closest_location_pose;
      ordered_location_names.push_back(closest_location_name);
      location_names.erase(std::remove(location_names.begin(),
                                       location_names.end(),
                                       closest_location_name),
                           location_names.end());
    }

    blackboard->set<std::vector<std::string>>("ordered_locations",
                                              ordered_location_names);

    return yasmin_ros::basic_outcomes::SUCCEED;
  };
};

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(OrderLocationsState, yasmin::State)