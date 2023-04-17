# Auto_navigation_handcart
本项目是一辆ROS的自主导航小推车，利用小推车改造，采用激光雷达、IMU、编码器电机进行自主定位和导航。成本低廉，老少咸宜，作为ROS入门学习非常合适。This is an autonomous navigation trolley built ROS, which uses Lidar, IMU and encoder motor for autonomous positioning and navigation. It is cheap and suitable for young and old, making it a perfect introduction to ROS.

![51e53cd47f8c3b0a53b34c64501e69c](https://user-images.githubusercontent.com/84019859/232469754-c3c7c19c-d5f9-486c-8619-1b0e48ae8898.jpg)

各package功能解释：

uart_set

通信层代码（重要），这部分代码负责上下位机通信，如果通信发生异常，请独立运行并检查该节点的信息是否有接收或者发送的错误。
roslaunch uart_set uart_set.launch 


keyboard

编写了键盘遥控小车的代码，执行keyboard_control.launch即可人工操控行驶。
遥控功能使用
roslaunch uart_set uart_set.launch
roslaunch keyboard keyboard_control.launch 
如果您中途重启了通信层，keyboard同样需要重新启动才能继续使用遥控功能。


car_navigation 

自主导航和建图，编写了自主导航和建图的launch脚本，算法本体由ros自带，不在本功能包中。
在使用本文件夹下任何建图或导航功能前，都需要先启动硬件。
roslaunch car_navigation hardware.launch 启动硬件层

建图功能使用

Gamping算法（ros经典算法，老少咸宜）

roslaunch car_navigation gmaping_mapping.launch 使用gmaping算法建图

rosrun map_server map_saver -f gmapping1 保存名为gmapping1的地图（在工程所在的文件中可以找到）

cartographer算法（谷歌商业化算法，成熟稳定，适合大图，笔记本建议用这个）

需要另开一个终端，在driveless_test0下的cartographer_ws中执行：

source install_isolated/setup.bash

roslaunch cartographer_ros carto_star.launch

然后在driveless_test0下执行：
roslaunch cartographer_ros carto_slam.launch

如果您想要调整参数(传感器融合)，需要在以下路径的文件中修改
cartographer_ws/src/cartographer_ros/cartographer_ros/launch/carto_star.launch
cartographer_ws/src/cartographer_ros/cartographer_ros/configuration_files/My_delta_lidar.lua
目前该算法的配置是同时使用imu和激光，实测融合编码器后反而效果变差。
如果你修改了该两个文件，都需要在cartographer_ws下执行catkin_make_isolated --install --use-ninja进行编译。


导航功能使用

在车上运行工控机/PC
roslaunch car_navigation slam_and_nav.launch 同时建图和导航（无地图下使用）

roslaunch car_navigation nav_pc.launch  pc或者工控机使用自主导航（有地图，需要在nav_star.launch中设置yaml来配置目标地图，默认是一张空地图）

多机通信，在车上运行单板机，我的单板机是nanopi neo4

同样需要在单板机上先运行 roslaunch car_navigation hardware.launch

单板机下独立运行导航：roslaunch car_navigation nav_neo.launch 适合在，用pc终端rviz即可查看

边缘计算模式：在PC上运行roslaunch car_navigation nav_edge.launch 进行算法运算。

![e282582e45058430a3ec91b5ef68e14](https://user-images.githubusercontent.com/84019859/232469930-fcb0ad56-5f2d-4548-8096-922f7cd20c88.png)
