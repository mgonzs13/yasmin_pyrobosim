
#include <memory>
#include <string>

#include "pyrobosim_msgs/msg/world_state.hpp"
#include "yasmin/state.hpp"

#include <pluginlib/class_list_macros.hpp>

class GetNextLocationState : public yasmin::State {

public:
  GetNextLocationState() : yasmin::State({"next", "end"}){};

  std::string
  execute(std::shared_ptr<yasmin::blackboard::Blackboard> blackboard) override {
    auto world_state =
        blackboard->get<pyrobosim_msgs::msg::WorldState>("world_state");

    if (world_state.locations.empty()) {
      return "end";
    } else {
      blackboard->set<std::string>("next_location",
                                   world_state.locations[0].name);
      world_state.locations.erase(world_state.locations.begin());
      blackboard->set<pyrobosim_msgs::msg::WorldState>("world_state",
                                                       world_state);
      return "next";
    }
  };
};

PLUGINLIB_EXPORT_CLASS(GetNextLocationState, yasmin::State)