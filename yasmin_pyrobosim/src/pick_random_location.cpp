
#include <cmath>
#include <memory>
#include <string>

#include "geometry_msgs/msg/pose.hpp"
#include "pyrobosim_msgs/msg/world_state.hpp"
#include "yasmin/state.hpp"
#include "yasmin_ros/basic_outcomes.hpp"

class PickRandomLocationState : public yasmin::State {

public:
  PickRandomLocationState()
      : yasmin::State({yasmin_ros::basic_outcomes::SUCCEED}) {};

  std::string
  execute(std::shared_ptr<yasmin::blackboard::Blackboard> blackboard) override {
    auto world_state =
        blackboard->get<pyrobosim_msgs::msg::WorldState>("world_state");

    // Pick a random location from world_state.locations
    auto locations = world_state.locations;
    if (locations.size() == 0) {
      return yasmin_ros::basic_outcomes::SUCCEED;
      ;
    }

    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Pick a random location
    std::string random_location =
        locations[std::rand() % locations.size()].name;
    blackboard->set<std::string>("random_location", random_location);

    YASMIN_LOG_INFO("Picked random location: %s", random_location.c_str());

    return yasmin_ros::basic_outcomes::SUCCEED;
  };
};

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(PickRandomLocationState, yasmin::State)