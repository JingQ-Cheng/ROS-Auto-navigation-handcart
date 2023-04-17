#include <vector>
#include "uartset/mbot.h"

#define Protocol_length 12 //真实数据包长度
#define length 7 // 定义串口缓冲区的长度

namespace mbot
{

    const unsigned char ender = 0XA0;
    const unsigned char header = 0XB0;
    static uint16_t CRC_Check(uint8_t *, uint8_t); // CRC校验
    CRC_16_t CRC_16 = {0, 0, 0, CRC_Check};

    // const int SPEED_INFO = 0xa55a; //消息类型检验
    // const int GET_SPEED  = 0xaaaa;

    float wheel_L_R = 0.48; // 两前轮轮距，动力轮
    float wheel_F_B = 0.52; // 前后轮轴距离

    boost::asio::io_service iosev;
    boost::asio::serial_port sp(iosev, "/dev/ttyUSB1"); // uar2使用/dev/ttyAMA1；USB使用ttyUSB1

    // 协方差矩阵
    boost::array<double, 36> odom_pose_covariance = {
        {1e-9, 0, 0, 0, 0, 0,
         0, 1e-3, 1e-9, 0, 0, 0,
         0, 0, 1e6, 0, 0, 0,
         0, 0, 0, 1e6, 0, 0,
         0, 0, 0, 0, 1e6, 0,
         0, 0, 0, 0, 0, 1e-9}};
    boost::array<double, 36> odom_twist_covariance = {
        {1e-9, 0, 0, 0, 0, 0,
         0, 1e-3, 1e-9, 0, 0, 0,
         0, 0, 1e6, 0, 0, 0,
         0, 0, 0, 1e6, 0, 0,
         0, 0, 0, 0, 1e6, 0,
         0, 0, 0, 0, 0, 1e-9}};

    union floatData // union的作用为实现char数组和float之间的转换
    {
        float float_dat = 0;
        unsigned char byte_data[4];
    } left_write, right_write, Vx_receive, Vw_receive;

    mbot::mbot() : x_(0.0), y_(0.0), th_(0.0),
                   vx_(0.0), vy_(0.0), vth_(0.0)
    {
    }

    mbot::~mbot()
    {
    }

    float Vz_to_Akm_Angle(float Vx, float Vz) // 计算转弯半径
    {
        float R, AngleR, Min_Turn_Radius;
        // float AngleL;

        // 如果目标速度要求的转弯半径小于最小转弯半径，会导致摩擦力提高，影响控制效果
        Min_Turn_Radius = 0.65; // 阿克曼小车需要设置最小转弯半径
        if (Vz != 0 && Vx != 0)
        {
            // 如果目标速度要求的转弯半径小于最小转弯半径
            if ((Vx / Vz) <= Min_Turn_Radius)
            {
                // 降低目标角速度，配合前进速度，提高转弯半径到最小转弯半径
                Vz = Vx / (Min_Turn_Radius);
            }
            R = Vx / Vz;
            AngleR = atan(wheel_F_B / (R + 0.5 * wheel_L_R));
        }
        else
        {
            AngleR = 0;
        }
        return AngleR;
    }

    int Drive_Motor(float Vx, float Vz) // 功能：逆解出左右轮目标线速度和舵机角度
    {
        // 阿克曼小车专用相关变量
        float R;
        float Ratio = 636.56;
        float AngleR;      // 右前轮转角
        float Angle_Servo; // 舵盘转角
        int Servo;         // 舵机转角

        AngleR = Vz_to_Akm_Angle(Vx, Vz);
        R = Vx / Vz;
        // 运动学逆解
        if (AngleR != 0)
        {
            left_write.float_dat = Vx * (R - 0.5 * wheel_L_R) / R;
            right_write.float_dat = Vx * (R + 0.5 * wheel_L_R) / R;
        }
        else
        {
            left_write.float_dat = Vx;
            right_write.float_dat = Vx;
        }
        ROS_INFO("left_target:%f  right_target:%f", left_write.float_dat, right_write.float_dat);

        // 舵机 PWM 值，舵机控制前轮转向角度
        Angle_Servo = -7.054 * pow(AngleR, 3) + 2.063 * pow(AngleR, 3) +
                      2.199 * pow(AngleR, 2) - 1.973 * AngleR + 1.554;

        // 这里需要进行拟合，得出舵盘和舵机角度的关系！
        Servo = (Angle_Servo - 1.554) * Ratio;
        return Servo;
    }

    bool mbot::init()
    {
        // 串口连接
        sp.set_option(boost::asio::serial_port::baud_rate(115200));
        sp.set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::none));
        sp.set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::none));
        sp.set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::one));
        sp.set_option(boost::asio::serial_port::character_size(8));

        ros::Time::init();
        current_time_ = ros::Time::now();
        last_time_ = ros::Time::now();

        // 定义发布消息的名称
        pub_ = nh.advertise<nav_msgs::Odometry>("odom", 50);

        return true;
    }

bool mbot::readSpeed()
{
	int i = 0;    
    unsigned char buf[50];//read buf的内容：信息头 线速度 转弯角速度 信息尾
    ROS_INFO("read...");
    // 读取串口数据
	boost::asio::read(sp, boost::asio::buffer(buf));
	ros::Time curr_time;
	
    for(i=0;i<43;i++){
    /*ROS_INFO("read buffer check now...");
    for(int j=0;j<20;j++){
            ROS_INFO("RXbuf[%d]: %x",j,buf[j]); //打印buf内容需要用16进制才能正常显示
            }  
    */        
	    if ((buf[i] == header)&&(buf[i+9] == ender))// 检查信息头
	    {
            ROS_INFO("mbot speed receive successful.");
            //读取直行速度
            for(int j=0;j<4;j++){
                Vx_receive.byte_data[j] = buf[i+j+1];
            }
            //读取转弯线速度
            for(int j=0;j<4;j++){
                Vw_receive.byte_data[j] = buf[i+j+5];
            }
            goto Caculate;
              
        }
        else if(i==42)
        {
            ROS_ERROR("readSpeed failed.");
        }
    }
    Caculate:
    memset(buf,0,sizeof(buf));
    vx_  = Vx_receive.float_dat;
    vth_ = Vw_receive.float_dat; //角速度
    ROS_INFO("Vx:%f Vz:%f",vx_,vth_);
    
    curr_time = ros::Time::now();
    
    // 积分计算里程计信息
    double dt = (curr_time - last_time_).toSec();
    double delta_x = (vx_ * cos(th_) - vy_ * sin(th_)) * dt;
    double delta_y = (vx_ * sin(th_) + vy_ * cos(th_)) * dt;
    double delta_th = vth_ * dt;

    x_ += delta_x;
    y_ += delta_y;
    th_ += delta_th;    //积分得偏转角
    last_time_ = curr_time;               

	return true;

}

    void mbot::writeSpeed(float RobotV, float YawRateF)
    {
        ROS_INFO("target speed send begin!");
        int i = 0;
        unsigned char buf[13]; // write buf：信息头,左轮线速度,右轮线速度,舵机角度,信息尾,CRC两位校验
        buf[0] = header;
        buf[10] = ender;
        buf[9] = Drive_Motor(RobotV, YawRateF); // 推算左右轮目标线速度，存储舵机角度

        // 计算CRC-16
        CRC_16.CRC_Value = CRC_16.CRC_Check(buf, 11); // 计算CRC值
        CRC_16.CRC_H = (uint8_t)(CRC_16.CRC_Value >> 8);
        CRC_16.CRC_L = (uint8_t)CRC_16.CRC_Value;
        
        buf[11] = CRC_16.CRC_H;
        buf[12] = CRC_16.CRC_L;

        for (i = 0; i < 4; i++)
        {
            buf[i + 1] = left_write.byte_data[i];
        }
        for (i = 0; i < 4; i++)
        {
            buf[i + 5] = right_write.byte_data[i];
        }
        buf[9] = 0XC0;

        boost::asio::write(sp, boost::asio::buffer(buf)); // 通过串口下发数据
        ROS_INFO("target speed send successful.");

        ros::Duration(0.01).sleep(); // 秒
    }

    bool mbot::spinOnce(float RobotV, float YawRate) // double RobotV, double YawRate
    {
        writeSpeed(RobotV, YawRate); // 下发无人车的线速度和角速度
        readSpeed();                 // 读取测量速度

        // writeSpeed(1.66, 10.5); // 此行仅用于串口测试，使用时注释掉

        geometry_msgs::TransformStamped odom_trans; // 创建一个tf发布需要使用的TransformStamped类型消息
        current_time_ = ros::Time::now();
        odom_trans.header.stamp = current_time_; // 载入里程计时间戳

        // 发布坐标变换的父子坐标系
        odom_trans.header.frame_id = "odom";
        odom_trans.child_frame_id = "base_footprint";

        // tf位置数据：x,y,z,方向
        geometry_msgs::Quaternion odom_quat; // 定义四元数变量
        odom_quat = tf::createQuaternionMsgFromYaw(th_);
        odom_trans.transform.translation.x = x_;
        odom_trans.transform.translation.y = y_;
        odom_trans.transform.translation.z = 0.0;
        odom_trans.transform.rotation = odom_quat;

        // odom_broadcaster_.sendTransform(odom_trans); //发布tf坐标变化；但使用ekf时候不需要发布该tf

        // 发布里程计消息
        nav_msgs::Odometry msgl; // 定义里程计对象
        msgl.header.stamp = current_time_;
        msgl.header.frame_id = "odom";

        msgl.pose.pose.position.x = x_;
        msgl.pose.pose.position.y = y_;
        msgl.pose.pose.position.z = 0.0;
        msgl.pose.pose.orientation = odom_quat;
        msgl.pose.covariance = odom_pose_covariance; // 载入协方差矩阵
        // 载入线速度和角速度
        msgl.child_frame_id = "base_footprint";
        msgl.twist.twist.linear.x = vx_;
        msgl.twist.twist.linear.y = vy_;
        msgl.twist.twist.angular.z = vth_;
        msgl.twist.covariance = odom_twist_covariance;
        // 发布里程计
        pub_.publish(msgl);
        return true;
    }

    /*******************************************************
    说明：CRC添加到消息中时，低字节先加入，然后高字

    CRC计算方法：
     1.预置1个16位的寄存器为十六进制FFFF(即全为1);称此寄存器为CRC寄存器;
     2.把第一个8位二进制数据(既通讯信息帧的第一个字节)与16位的CRC寄存器的低
     8位相异或，把结果放于CRC寄存器;
     3.把CRC寄存器的内容右移一位(朝低位)用0填补最高位，并检查右移后的移出位;
     4.如果移出位为0:重复第3步(再次右移一位);
     如果移出位为1:CRC寄存器与多项式A001(1010 0000 0000 0001)进行异或;
     5.重复步骤3和4，直到右移8次，这样整个8位数据全部进行了处理;
     6.重复步骤2到步骤5，进行通讯信息帧下一个字节的处理;
     7.将该通讯信息帧所有字节按上述步骤计算完成后，得到的16位CRC寄存器的高、低
     字节进行交换;
    ********************************************************/

    /*
     * @name   CRC_Check
     * @brief  CRC校验
     * @param  CRC_Ptr->数组指针，LEN->长度
     * @retval CRC校验值
     */
    uint16_t CRC_Check(uint8_t *CRC_Ptr, uint8_t LEN)
    {
        uint16_t CRC_Value = 0;
        uint8_t i = 0;
        uint8_t j = 0;

        CRC_Value = 0xffff;
        for (i = 0; i < LEN; i++)
        {
            CRC_Value ^= *(CRC_Ptr + i);
            for (j = 0; j < 8; j++)
            {
                if (CRC_Value & 0x00001)
                    CRC_Value = (CRC_Value >> 1) ^ 0xA001;
                else
                    CRC_Value = (CRC_Value >> 1);
            }
        }
        CRC_Value = ((CRC_Value >> 8) + (CRC_Value << 8)); // 交换高低字节

        return CRC_Value;
    }

}
