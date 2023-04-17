/*******************************************************
@company: Copyright (C) 2021, Leishen Intelligent System
@product: LSN10
@filename: lsn10.h
@brief:
@version:       date:       author:     comments:
@v1.0           21-8-21     fu          new
*******************************************************/
#ifndef LSN10_H
#define LSN10_H
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
#include <string>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include "lsn10/lsiosr.h"

namespace ls {

typedef struct {
    double degree;
    double range;
    int intensity;
} ScanPoint;

class LSN10
{
public:
  LSN10();
  ~LSN10();
    /**
    * 实例化雷达
    * port: 串口号，
    * baud_rate: 波特率 460800
    */
    static LSN10* instance();

    /**
    * 获取雷达数据
    * poins: 雷达点的数据。类型为ScanPoint数组
    */
    int getScan(std::vector<ScanPoint> &points, ros::Time &scan_time, float &scan_duration);

    /**
    * 获取软件版本号
    * version: 返回版本号
    */
    int getVersion(std::string &version);

    uint8_t CalCRC8(unsigned char * p, int len);

    int getRate();
	
  private:
    void initParam();
    void recvThread();
    void pubScanThread();

    std::vector<ScanPoint> scan_points_;
    std::vector<ScanPoint> scan_points_bak_;

    LSIOSR * serial_;
    boost::thread *recv_thread_;
    boost::thread *pubscan_thread_;
    boost::mutex pubscan_mutex_;
    boost::mutex mutex_;
    boost::condition_variable pubscan_cond_;

    bool is_shutdown_;    // shutdown recvthread
    int data_len_;
    int points_size_;
    int count_sum;

    ros::Time pre_time_;
    ros::Time time_;
	  ros::Publisher device_pub;
	
    std::string serial_port_;
    int baud_rate_;
    std::string scan_topic_;
    std::string frame_id_;
	
    ros::NodeHandle n_;
    ros::Publisher pub_;
    int truncated_mode_;
    double min_distance,max_distance;
    std::vector<int> disable_angle_min_range, disable_angle_max_range, disable_angle_range_default;
};

}
#endif
