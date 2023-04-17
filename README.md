# Auto_navigation_handcart
  本项目是一辆ROS的自主导航小推车。该ROS机器人将小推车作为底盘，并为它装了两个直流电机以产生动力。传感器方面采用激光雷达、IMU、编码器、摄像头。实现了自主定位，导航，slam，opencv等功能。
  该项目成本低廉，代码风格简单易懂，老少咸宜，作为ROS入门学习非常合适。您既可以在PC直接放在小推车上作为主控，也可以通过多机通信的方式控制小推车上的树莓派或其他卡片电脑，并把计算负载放在PC上以减小卡片电脑的负担。

  This project is a ROS autonomous navigation trolley. The ROS robot uses a trolley as a chassis and is equipped with two DC motors to generate power. Sensor using laser radar, IMU, encoder, camera. Autonomous positioning, navigation, slam, opencv and other functions are realized.

  The project's low cost and easy-to-understand code style make it a perfect introduction to ROS for young and old. You can either put the PC directly on the cart as the main control, or you can control the Raspberry PI or other card computers on the cart through multi-machine communication, and put the computing load on the PC to reduce the burden of the card computer.

![51e53cd47f8c3b0a53b34c64501e69c](https://user-images.githubusercontent.com/84019859/232469754-c3c7c19c-d5f9-486c-8619-1b0e48ae8898.jpg)

![0b6064588cbba641626c8b15550335d](https://user-images.githubusercontent.com/84019859/232471225-f9c6c752-f861-4264-8d00-b0f86028b281.png)
  我在本项目中使用了NanoPi neo4作为小推车的ROS主控，并用笔记本电脑和rk3399进行多机通信。




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
