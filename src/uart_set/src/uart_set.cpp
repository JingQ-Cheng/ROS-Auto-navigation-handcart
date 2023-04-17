/******************************
 ROS UART通信层
 此模块适用于阿克曼结构/两轮差速
 ******************************/

#include "uartset/mbot.h"

float RobotV_ = 0;
float YawRate_ = 0;

// 回调 从twist中获取线角速度
void cmdCallback(const geometry_msgs::Twist& msg)
{
    ROS_INFO("callback success!");
	RobotV_ = msg.linear.x;
	YawRate_ = msg.angular.z;
}
    
int main(int argc, char** argv)
{
    //初始化ROS节点
	ros::init(argc, argv, "uart_entry");									
    ros::NodeHandle nh;
    
    //初始化mbot
	mbot::mbot robot;
    if(!robot.init())
        ROS_ERROR("mbot initialized failed.");
	ROS_INFO("mbot initialized successful.");


    ros::Subscriber sub = nh.subscribe("cmd_vel", 50, cmdCallback);

    ros::Rate loop_rate(50); //频率
	while (ros::ok()) 
    {
		ros::spinOnce();
        
        // 将速度数据传给串口
        robot.spinOnce(RobotV_,YawRate_);
        
		loop_rate.sleep();
	}

	return 0;
}

//
//               _oo0oo_
//              o8888888o
//              88" . "88
//              (| -_- |)
//               0\ = /0
//            ___/`---'\___
//             .' \\| |// '.
//          / \\||| : |||// \
//         / _||||| -:- |||||- \
//           | | \\\ - /// | |
//         | \_| ''\---/'' |_/ |
//         \ .-\__ '-' ___/-. /
//       ___'. .' /--.--\ `. .'___
//     ."" '< `.___\_<|>_/___.' >' "".
//  | | : `- \`.;`\ _ /`;.`/ - ` : | |
//      \ \ `_. \_ __\ /__ _/ .-` / /
//  =====`-.____`.___ \_____/___.-`___.-'=====
// `=---='
//
// 我佛慈悲，超度bug
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// 