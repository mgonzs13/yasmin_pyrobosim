
#include <memory>
#include <string>

#include "yasmin/state.hpp"

class CheckSameLocationState : public yasmin::State {

public:
  CheckSameLocationState() : yasmin::State({"yes", "no"}) {
    this->set_description(
        "Check if the robot is at the target location and return 'yes' if it "
        "is and 'no' if it isn't.");
    this->set_outcome_description("yes",
                                  "The robot is at the target location.");
    this->set_outcome_description("no",
                                  "The robot is not at the target location.");
    this->add_input_key("location", "Current location of the robot");
    this->add_input_key("target_location", "Target location to compare to");
  };

  std::string execute(yasmin::Blackboard::SharedPtr blackboard) override {
    auto location = blackboard->get<std::string>("location");
    auto target_location = blackboard->get<std::string>("target_location");

    if (location == target_location) {
      return "yes";
    } else {
      return "no";
    }
  };
};

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(CheckSameLocationState, yasmin::State)