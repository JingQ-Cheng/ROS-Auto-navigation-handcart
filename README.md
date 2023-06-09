# Auto_navigation_handcart
  本项目是一辆ROS自主导航小推车。该ROS机器人将小推车作为底盘，并装载了两个直流电机以产生动力，实现了自主定位，导航，slam，opencv等功能。
  它以stm32F407作为运动控制中心，传感器方面采用激光雷达、IMU、编码器、摄像头。您既可以将笔记本电脑直接放置在小推车上作为ROS主控，也可以通过多机通信的方式控制小推车上的树莓派或其他卡片电脑，采用分布式计算的方式来减小卡片电脑的负担。 
  该项目成本低廉，代码风格简单易懂，老少咸宜，适合ROS入门学习。

This project is an ROS autonomous navigation trolley. The ROS robot uses a trolley as a chassis and is loaded with two DC motors to generate power, realizing autonomous positioning, navigation, slam, opencv and other functions.

It takes stm32F407 as the motion control center, and uses laser radar, IMU, encoder and camera as the sensor. You can either place the laptop directly on the trolley as the ROS master, or you can control the Raspberry PI or other card computers on the trolley through multi-machine communication, and put the computing load on the PC to reduce the load on the card computer.

The project's low cost and easy-to-understand code style make it suitable for young and old to get started with ROS.

演示视频地址： https://www.bilibili.com/video/BV1fj411D7Xz/?share_source=copy_web&vd_source=ba09f5329ccbdf0cbc6d31f78a69ca93

![car](https://user-images.githubusercontent.com/84019859/232475787-6a4f2c0c-a1a9-41a1-a8b0-fea47ad15463.jpg)

![0b6064588cbba641626c8b15550335d](https://user-images.githubusercontent.com/84019859/232471225-f9c6c752-f861-4264-8d00-b0f86028b281.png)
 
 我在本项目中使用了NanoPi neo4作为小推车的ROS主控，并用笔记本电脑和rk3399进行多机通信。
 
![框架-工控机](https://user-images.githubusercontent.com/84019859/232474935-23d2e88b-83c4-454b-883f-deb010c8c711.png)




各package功能解释：

- uart_set

  通信层代码（重要），这部分代码负责上下位机通信，如果通信发生异常，请独立运行并检查该节点的信息是否有接收或者发送的错误。
roslaunch uart_set uart_set.launch 


- keyboard

  编写了键盘遥控小车的代码，执行keyboard_control.launch即可人工操控行驶。
遥控功能使用
roslaunch uart_set uart_set.launch
roslaunch keyboard keyboard_control.launch 
如果您中途重启了通信层，keyboard同样需要重新启动才能继续使用遥控功能。


- car_navigation 
  
  自主导航和建图，编写了自主导航和建图的launch脚本，算法本体由ros自带，不在本功能包中。
在使用本文件夹下任何建图或导航功能前，都需要先启动硬件。
roslaunch car_navigation hardware.launch 启动硬件层

建图功能使用

- Gamping算法（slam经典算法）

  roslaunch car_navigation gmaping_mapping.launch 使用gmaping算法建图

  rosrun map_server map_saver -f gmapping1 保存名为gmapping1的地图（在工程所在的文件中可以找到）

- cartographer算法（谷歌商业化算法，成熟稳定，适合大图，笔记本建议用这个）

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


- 导航功能使用

  在车上运行工控机/PC
  roslaunch car_navigation slam_and_nav.launch 同时建图和导航（无地图下使用）

  roslaunch car_navigation nav_pc.launch  pc或者工控机使用自主导航（有地图，需要在nav_star.launch中设置yaml来配置目标地图，默认是一张空地图）

- 多机通信，在车上运行卡片电脑。

  同样需要在单板机上先运行 roslaunch car_navigation hardware.launch

  单板机下独立运行导航：roslaunch car_navigation nav_neo.launch 适合在，用pc终端rviz即可查看

  边缘计算模式：在PC上运行roslaunch car_navigation nav_edge.launch 进行算法运算。

![e282582e45058430a3ec91b5ef68e14](https://user-images.githubusercontent.com/84019859/232469930-fcb0ad56-5f2d-4548-8096-922f7cd20c88.png)
![实验室建图2](https://user-images.githubusercontent.com/84019859/232491840-a10bdd55-4861-425c-8440-fc6eb494074b.png)
![大车车](https://user-images.githubusercontent.com/84019859/232491934-4603a3b0-c42d-4d78-842c-0e429c220e17.jpg)

