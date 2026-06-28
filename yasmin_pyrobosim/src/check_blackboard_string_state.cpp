#include <memory>
#include <string>

#include "yasmin/state.hpp"

class CheckBlackboardStringState : public yasmin::State {

public:
  CheckBlackboardStringState() : yasmin::State({"yes", "no"}) {
    this->set_description(
        "Check if a blackboard string value equals the expected value.");
    this->set_outcome_description(
        "yes", "The blackboard value matches the expected value.");
    this->set_outcome_description(
        "no", "The blackboard value does not match the expected value.");
    this->declare_parameter("key", "Blackboard key to check",
                            std::string("key"));
    this->declare_parameter("value", "Expected value to compare",
                            std::string("value"));
  };

  std::string execute(yasmin::Blackboard::SharedPtr blackboard) override {
    auto key = this->get_parameter<std::string>("key");
    auto expected = this->get_parameter<std::string>("value");

    if (!blackboard->contains(key)) {
      return "no";
    }

    auto actual = blackboard->get<std::string>(key);

    if (actual == expected) {
      return "yes";
    } else {
      return "no";
    }
  };
};

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(CheckBlackboardStringState, yasmin::State)
