#include <memory>
#include <string>

#include "pyrobosim_msgs/msg/world_state.hpp"
#include "pyrobosim_msgs/srv/request_world_state.hpp"

#include "yasmin/state.hpp"
#include "yasmin_ros/basic_outcomes.hpp"
#include "yasmin_ros/service_state.hpp"

using RequestWorldState = pyrobosim_msgs::srv::RequestWorldState;
using namespace std::placeholders;

class GetWorldStateState : public yasmin_ros::ServiceState<RequestWorldState> {
public:
  GetWorldStateState()
      : yasmin_ros::ServiceState<RequestWorldState>(
            "/request_world_state",
            std::bind(&GetWorldStateState::create_request_handler, this, _1),
            std::bind(&GetWorldStateState::response_handler, this, _1, _2)) {
    this->set_description(
        "Request the current world state from the service and "
        "set it as an output key.");
    this->add_output_key("world_state", "Current world state");
  }

  RequestWorldState::Request::SharedPtr
  create_request_handler(yasmin::Blackboard::SharedPtr blackboard) {
    (void)blackboard; // No inputs needed for this request
    return std::make_shared<RequestWorldState::Request>();
  }

  std::string
  response_handler(yasmin::Blackboard::SharedPtr blackboard,
                   RequestWorldState::Response::SharedPtr response) {
    blackboard->set<pyrobosim_msgs::msg::WorldState>("world_state",
                                                     response->state);
    return yasmin_ros::basic_outcomes::SUCCEED;
  }
};

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(GetWorldStateState, yasmin::State)