#include "rclcpp/rclcpp.hpp"
#include "practice_interfaces/srv/AddTwoInts.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("AddTwoInts_client");
    rclcpp::Client<practice_interfaces::srv::AddTwoInts>::SharedPtr client = 
        node->create_client<practice_interfaces::srv::AddTwoInts>("add_two_ints");

    auto request = std::make_shared<practice_interfaces::srv::AddTwoInts::Request>();
    request->a = atoll(argv[1]);
    request->b = atoll(argv[2]);

    // Tells the client to look for the service and then wait if it can't find it
    while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    auto result = client-> async_send_request(request);

    // Wait for the result.
    if (rclcpp::spin_until_future_complete(node, result) ==
        rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sum: %ld", result.get()->sum);
    } else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_two_ints");
    }

    rclcpp::shutdown();
    return 0;

}