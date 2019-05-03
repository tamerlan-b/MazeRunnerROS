#ifndef RACING_MAZERUNNER_H
#define RACING_MAZERUNNER_H


#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "move_base_msgs/MoveBaseAction.h"
#include "actionlib/client/simple_action_client.h"
#include "geometry_msgs/PointStamped.h"

using MoveBaseClient = actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>;

class MazeRunner {
public:
    void GoToPointAsync(ros::NodeHandle &node);
private:
    void SendGoal(MoveBaseClient &ac, const geometry_msgs::Point &point);
    move_base_msgs::MoveBaseGoal ConfigureGoal(const geometry_msgs::Point &point);
    void spinThread();
    geometry_msgs::Point readPoint(ros::NodeHandle &node);
};


#endif //RACING_MAZERUNNER_H
