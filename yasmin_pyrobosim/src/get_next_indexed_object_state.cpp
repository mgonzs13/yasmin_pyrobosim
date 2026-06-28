#include <memory>
#include <string>

#include "pyrobosim_msgs/msg/object_state.hpp"

#include "yasmin/state.hpp"

class GetNextIndexedObjectState : public yasmin::State {

public:
  GetNextIndexedObjectState() : yasmin::State({"next", "end"}) {
    this->set_description(
        "Get the next object from accumulated objects using an index counter "
        "without mutating the list. If no more unprocessed objects exist, "
        "return 'end'.");
    this->set_outcome_description(
        "next", "A next object to pick was found and set as an output key.");
    this->set_outcome_description("end", "No more objects to pick were found.");
    this->add_input_key("accumulated_objects",
                        "List of accumulated detected objects to pick from");
    this->add_output_key("next_object", "Name of the next object to pick");
    this->add_output_key("object_location",
                         "Location of the next object to pick");
  };

  std::string execute(yasmin::Blackboard::SharedPtr blackboard) override {

    if (!blackboard->contains("accumulated_objects")) {
      return "end";
    }

    auto objects =
        blackboard->get<std::vector<pyrobosim_msgs::msg::ObjectState>>(
            "accumulated_objects");

    size_t index = 0;
    if (blackboard->contains("cleanup_index")) {
      index = static_cast<size_t>(blackboard->get<int>("cleanup_index"));
    }

    if (index >= objects.size()) {
      return "end";
    }

    blackboard->set<std::string>("next_object", objects[index].name);
    blackboard->set<std::string>("object_location", objects[index].parent);
    blackboard->set<int>("cleanup_index", static_cast<int>(index + 1));

    return "next";
  };
};

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(GetNextIndexedObjectState, yasmin::State)
