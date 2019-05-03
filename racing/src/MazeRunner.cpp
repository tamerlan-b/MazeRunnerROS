#include "MazeRunner.h"


void MazeRunner::GoToPointAsync(ros::NodeHandle &node)
{
    MoveBaseClient ac("/move_base", false);

    //Ждем пока сервер не будет подключен
    while(!ac.isServerConnected())
        ros::spinOnce();

    auto targetPt = readPoint(node);

    //Запускаем ros в другом потоке
    boost::thread spin_thread = boost::thread(boost::bind(&MazeRunner::spinThread, *this));
    //Отправляем точку на исполнение
    SendGoal(ac, targetPt);

    //Ожидаем результата
    ac.waitForResult();

    //Выводим сообщения о достижении точки
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_ERROR("Target is reached");
    else
        ROS_ERROR("Can't reach target");

}

/**
 * Считывает координаты целевой точки из launch файла
 * @param node
 * @return
 */
geometry_msgs::Point MazeRunner::readPoint(ros::NodeHandle &node)
{
    //Точка, которая находится в зоне финиша
    geometry_msgs::Point targetPt;

    //Считываем координаты точки финиша
    targetPt.x = node.param("x_finish", -7.0);
    targetPt.y = node.param("y_finish", 6.0);
    targetPt.z = node.param("z_finish", 0.0);
    return targetPt;
}

/**
 * Функция для запуска ros в другом потоке
 */
void MazeRunner::spinThread()
{
    ros::spin();
}

/**
 * Конфигурирует параметры целевой точки
 * @param point Координаты точки
 * @return
 */
move_base_msgs::MoveBaseGoal MazeRunner::ConfigureGoal(const geometry_msgs::Point &point)
{
    //Создаем целевую точку
    move_base_msgs::MoveBaseGoal goal;

    //Задаем параметры целевой точки
    goal.target_pose.pose.position = point;
    double targetAngle = M_PI / 2;
    goal.target_pose.pose.orientation.z = sin(targetAngle/2);
    goal.target_pose.pose.orientation.w = cos(targetAngle/2);
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();
    return goal;
}

/**
 * Отправляет робота двигаться к целевой точке
 * @param point точка, в которую должен приехать робот
 */
void MazeRunner::SendGoal(MoveBaseClient &ac, const geometry_msgs::Point &point)
{
    //Создаем целевую точку
    move_base_msgs::MoveBaseGoal goal = ConfigureGoal(point);
    //Отправляем целевую точку на исполнение
    ac.sendGoal(goal);
    ROS_ERROR_STREAM("Robot move to point: " << point.x <<"; " << point.y << "; " << point.z);
}