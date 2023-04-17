#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include<iostream>
using namespace std;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
    ros::init(argc, argv, "send_goals_node");
    MoveBaseClient ac("move_base", true);
    uint8_t total = 4; //toatal goal nunmber
    uint8_t goal_number = 0;
    

    while(!ac.waitForServer( ros::Duration( 5.0 ) )){
        ROS_INFO("Waiting for the move_base action server to come up");
    }
    move_base_msgs::MoveBaseGoal goal[total];

    // 第一个待发送的 目标点 在 map 坐标系下的坐标位置
    goal[0].target_pose.pose.position.x = 1.84500110149; 
    goal[0].target_pose.pose.position.y =  -0.883078575134;
    goal[0].target_pose.pose.orientation.z =  -0.306595935327;  
    goal[0].target_pose.pose.orientation.w = 0.951839761956;  

    // 第二个待发送的 目标点 在 map 坐标系下的坐标位置
    goal[1].target_pose.pose.position.x = 3.24358606339;
    goal[1].target_pose.pose.position.y = 0.977679371834;
    goal[1].target_pose.pose.orientation.z = 0.647871240469;  
    goal[1].target_pose.pose.orientation.w = 0.761749864308;  
  
    // 第三个待发送的 目标点 在 map 坐标系下的坐标位置
    goal[2].target_pose.pose.position.x = 2.41693687439;
    goal[2].target_pose.pose.position.y = 1.64631867409;
    goal[2].target_pose.pose.orientation.z = 0.988149484601;  
    goal[2].target_pose.pose.orientation.w = 0.153494612555;  

    // 第四个待发送的 目标点 在 map 坐标系下的坐标位置
    goal[3].target_pose.pose.position.x =-0.970185279846;
    goal[3].target_pose.pose.position.y = 0.453477025032;
    goal[3].target_pose.pose.orientation.z = 0.946238058267;  
    goal[3].target_pose.pose.orientation.w = -0.323471076121;  
    
    ROS_INFO(" Init success!!! ");
    while(total-goal_number-1 )    // total is 4 goals
    {
        goal[goal_number].target_pose.header.frame_id = "map";
        goal[goal_number].target_pose.header.stamp = ros::Time::now();
        ac.sendGoal(goal[goal_number]);
        ROS_INFO("Send NO. %d Goal !!!", goal_number );
                
        ac.waitForResult();
        if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
            ROS_INFO("The NO. %d Goal achieved success !!!", goal_number );
            goal_number ++ ;
        }else{
            ROS_WARN("The NO. %d Goal Planning Failed", goal_number); }
    }
    return 0;
  }