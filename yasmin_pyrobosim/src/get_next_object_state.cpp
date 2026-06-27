#include <memory>
#include <string>

#include "pyrobosim_msgs/msg/object_state.hpp"
#include "yasmin/state.hpp"

class GetNextObjectState : public yasmin::State {

public:
  GetNextObjectState() : yasmin::State({"next", "end"}) {
    this->set_description(
        "Get the next object to pick from the detected objects and set it as "
        "an output key. If there are no more objects, return 'end'.");
    this->set_outcome_description(
        "next", "A next object to pick was found and set as an output key.");
    this->set_outcome_description("end", "No more objects to pick were found.");
    this->add_input_key("detected_objects", "List of detected objects to pick");
    this->add_output_key("next_object", "Name of the next object to pick");
    this->add_output_key("object_location",
                         "Location of the next object to pick");
  };

  std::string execute(yasmin::Blackboard::SharedPtr blackboard) override {
    auto objects =
        blackboard->get<std::vector<pyrobosim_msgs::msg::ObjectState>>(
            "detected_objects");

    if (objects.empty()) {
      return "end";
    } else {
      blackboard->set<std::string>("next_object", objects[0].name);
      blackboard->set<std::string>("object_location", objects[0].parent);
      objects.erase(objects.begin());
      blackboard->set<std::vector<pyrobosim_msgs::msg::ObjectState>>(
          "detected_objects", objects);
      return "next";
    }
  };
};

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(GetNextObjectState, yasmin::State)