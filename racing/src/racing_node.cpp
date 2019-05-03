#include "ros/ros.h"
#include "move_base_msgs/MoveBaseAction.h"  //Здесь лежит тип MoveBaseAction
#include "actionlib/client/simple_action_client.h"    //Здесь лежит SimpleActionClient<T>
#include "MazeRunner.h"

using MoveBaseClient = actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>;


int main(int argc, char** argv)
{
    //Инициализация системы сообщений ros
	ros::init(argc, argv, "racing_control_node");

	//Создание приватного узла
	ros::NodeHandle node("~");

	//Создание бегущего по лабиринту
    MazeRunner mr;

    //Прохождение лабиринта в параллельном потоке
    mr.GoToPointAsync(node);

	return 0;
}