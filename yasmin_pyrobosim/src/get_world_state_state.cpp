
#include <memory>
#include <string>

#include "pyrobosim_msgs/msg/world_state.hpp"
#include "pyrobosim_msgs/srv/request_world_state.hpp"
#include "yasmin/state.hpp"
#include "yasmin_ros/basic_outcomes.hpp"
#include "yasmin_ros/service_state.hpp"

#include <pluginlib/class_list_macros.hpp>

using RequestWorldState = pyrobosim_msgs::srv::RequestWorldState;
using namespace std::placeholders;

class GetWorldStateState : public yasmin_ros::ServiceState<RequestWorldState> {
public:
  GetWorldStateState()
      : yasmin_ros::ServiceState<RequestWorldState>(
            "/request_world_state",
            std::bind(&GetWorldStateState::create_request_handler, this, _1),
            std::bind(&GetWorldStateState::response_handler, this, _1, _2)) {}

  std::shared_ptr<RequestWorldState::Request> create_request_handler(
      std::shared_ptr<yasmin::blackboard::Blackboard> blackboard) {
    (void)blackboard; // No inputs needed for this request
    return std::make_shared<RequestWorldState::Request>();
  }

  std::string
  response_handler(std::shared_ptr<yasmin::blackboard::Blackboard> blackboard,
                   RequestWorldState::Response::SharedPtr response) {
    blackboard->set<pyrobosim_msgs::msg::WorldState>("world_state",
                                                     response->state);
    return yasmin_ros::basic_outcomes::SUCCEED;
  }
};

PLUGINLIB_EXPORT_CLASS(GetWorldStateState, yasmin::State)