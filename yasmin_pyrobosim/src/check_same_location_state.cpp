
#include <memory>
#include <string>

#include "yasmin/state.hpp"

#include <pluginlib/class_list_macros.hpp>

class CheckSameLocationState : public yasmin::State {

public:
  CheckSameLocationState() : yasmin::State({"yes", "no"}){};

  std::string
  execute(std::shared_ptr<yasmin::blackboard::Blackboard> blackboard) override {
    auto location = blackboard->get<std::string>("location");
    auto target_location = blackboard->get<std::string>("target_location");

    if (location == target_location) {
      return "yes";
    } else {
      return "no";
    }
  };
};

PLUGINLIB_EXPORT_CLASS(CheckSameLocationState, yasmin::State)