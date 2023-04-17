#ifndef MBOT_H
#define MBOT_H

#include <ros/ros.h>
#include <ros/time.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <boost/asio.hpp>  //asio
#include <serial/serial.h> //serial
#include <cmath> //数学库
#include <geometry_msgs/Twist.h>

namespace mbot
{

class mbot
{
public:
    mbot();
    ~mbot();
    bool init();
    bool spinOnce(float RobotV, float YawRate); //float RobotV, float YawRate
   
private:
    bool readSpeed();
    void writeSpeed(float RobotV, float YawRate);
    unsigned char getCrc8(unsigned char *ptr, unsigned short len);
   
private:
    ros::Time current_time_, last_time_;

    double x_;
    double y_;
    double th_;

    double vx_;
    double vy_;
    double vth_;

    ros::NodeHandle nh;
    ros::Publisher pub_;
    tf::TransformBroadcaster odom_broadcaster_;
};

//定义结构体类型
typedef struct
{
	uint16_t CRC_Value; //CRC校验值
	uint8_t  CRC_H;     //高位
	uint8_t  CRC_L;     //低位
	uint16_t (*CRC_Check)(uint8_t*,uint8_t);  //CRC校验
} CRC_16_t;

/* extern variables-----------------------------------------------------------*/
extern CRC_16_t CRC_16;

}



/* extern function prototypes-------------------------------------------------*/

#endif /* mbot_H */
