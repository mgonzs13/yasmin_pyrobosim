#include <memory>
#include <string>

#include "yasmin/state.hpp"
#include "yasmin_ros/basic_outcomes.hpp"

class SetBlackboardStringState : public yasmin::State {

public:
  SetBlackboardStringState() : yasmin::State({"succeeded"}) {
    this->set_description(
        "Set a string value on the blackboard from declared parameters.");
    this->declare_parameter("key", "Blackboard key to set", std::string("key"));
    this->declare_parameter("value", "Value to set", std::string("value"));
  };

  std::string execute(yasmin::Blackboard::SharedPtr blackboard) override {
    auto key = this->get_parameter<std::string>("key");
    auto value = this->get_parameter<std::string>("value");

    blackboard->set<std::string>(key, value);

    return yasmin_ros::basic_outcomes::SUCCEED;
  }
};

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(SetBlackboardStringState, yasmin::State)
