# Auto_navigation_handcart
  本项目是一辆ROS自主导航小推车。该ROS机器人将小推车作为底盘，并装载了两个直流电机以产生动力，实现了自主定位，导航，slam，opencv等功能。
  
  它以stm32F407作为运动控制中心，传感器方面采用激光雷达、IMU、编码器、摄像头。您既可以将笔记本电脑直接放置在小推车上作为ROS主控，也可以通过多机通信的方式控制小推车上的树莓派或其他卡片电脑，采用分布式计算的方式来减小卡片电脑的负担。 
  
  该项目成本低廉，代码风格简单易懂，老少咸宜，适合ROS入门学习。
  
  什么选择使用小推车？因为购买一辆小推车的价格是非常便宜的，大约10-50￥（约6$）就可以买到。(虽然我们是从废品站捡来的[doge]) 这比去网上购买的定制小车底盘更便宜，体积更大，运输能力更强大，你甚至可以将你的笔记本电脑放在上面。
  
  更详细的说明文档和教程在 自主推车操作指南及教程.pdf中，目前只有中文版的pdf.

联系邮箱：2548383742@qq.com

  This project is an ROS autonomous navigation trolley. The ROS robot uses a trolley as a chassis and is loaded with two DC motors to generate power, realizing autonomous positioning, navigation, slam, opencv and other functions.
  
  It takes stm32F407 as the motion control center, and uses laser radar, IMU, encoder and camera as the sensor. You can either place the laptop directly on the trolley as the ROS master, or you can control the Raspberry PI or other card computers on the trolley through multi-machine communication, and put the computing load on the PC to reduce the load on the card computer.
  The project's low cost and easy-to-understand code style make it suitable for young and old to get started with ROS.
  
  Why do I use a cart? Because the price of buying a cart is very cheap, about 10-50￥(about $6) can be bought. It is larger, more powerful transport, cheaper than going online to buy a custom car chassis,you can even put your laptop on it.

My E-mail: 2548383742@qq.com

演示视频地址/demo video： https://www.bilibili.com/video/BV1fj411D7Xz/?share_source=copy_web&vd_source=ba09f5329ccbdf0cbc6d31f78a69ca93

![car](https://user-images.githubusercontent.com/84019859/232475787-6a4f2c0c-a1a9-41a1-a8b0-fea47ad15463.jpg)

# **package introduce**

- uart_set

  The function of this part of the code is to establish communication between the PC and the MCU by UART. 
  
  use Command 
   ```roslaunch uart_set uart_set.launch``` 
  If the communication is abnormal, please run it independently and check whether the information of the node is received or sent incorrectly.

  通信层代码，这部分代码负责上下位机通信，如果通信发生异常，请独立运行并检查该节点的信息是否有接收或者发送的错误。
  

- keyboard

  The package provides the function to control the car using the keyboard

  Command：
  ```roslaunch uart_set uart_set.launch```
  ```roslaunch keyboard keyboard_control.launch```

- car_description
  
  There's an urdf to describe the model of the car.

- lsn10
  
  This is the Lidar feature pack, you can replace it with your radar SDK.

- imu_package
  
  This is the imu feature pack, you can replace it with your imu SDK.

- car_navigation 
  
  The launch script of autonomous navigation and mapping is written. The algorithm ontology is delivered by ros and is not included in this function package.
  Before you can use any of the mapping or navigation features in this folder, you need to enable the hardware.

   Command：
    ```roslaunch car_navigation hardware.launch```
  
  自主导航和建图，编写了自主导航和建图的launch脚本，算法本体由ros自带，不在本功能包中。
  在使用本文件夹下任何建图或导航功能前，都需要先启动硬件。

## use slam
  建图功能使用

- Gamping

  ```roslaunch car_navigation gmaping_mapping.launch ```

  ```rosrun map_server map_saver -f gmapping1```

  Save the map named gmapping1 (found in the file where the project is located)

- cartographer（谷歌商业化算法，成熟稳定，适合大图，笔记本建议用这个）

  cartographer is not included in this project and needs to be installed independently,and put two folders in the cartographer_set in github into corresponding positions after installation.

    *cartographer_ws/src/cartographer_ros/cartographer_ros/launch/carto_star.launch*

   *cartographer_ws/src/cartographer_ros/cartographer_ros/configuration_files/My_delta_lidar.lua*

  （cartographer_ws refers to the named folder name of the catographer installation）
  
  command in cartographer_ws to compile：
  ```source install_isolated/setup.bash```

  command for carto slam：
  ```roslaunch cartographer_ros carto_star.launch```
  
  and then command in your ros workspace：
  ```roslaunch car_navigation carto_slam.launch```

   If you modify these two files, they need to be command in cartographer_ws
  ```catkin_make_isolated --install --use-ninja```


## use Navigation

- put the pc on the car
  ```roslaunch car_navigation slam_and_nav.launch```
  slam and navigaton，no map

  If you want to use a map , you need to set yaml in nav_star.launch to configure the target map, which defaults to an open space map
  ```roslaunch car_navigation nav_pc.launch```

- Multicomputer communication，put the Single board computer(such as RaspberryPI) on the car. you must confige Multicomputer communication for Single board computer and PC
  The project file needs to be installed and compiled on both devices

   ```roslaunch car_navigation hardware.launch```

  Independent navigation on a single board computer：
  ```roslaunch car_navigation nav_neo.launch```
  and open the rviz on the PC



  


![0b6064588cbba641626c8b15550335d](https://user-images.githubusercontent.com/84019859/232471225-f9c6c752-f861-4264-8d00-b0f86028b281.png)
 

 
 我在本项目中使用了NanoPi neo4作为小推车的ROS主控，并用笔记本电脑和rk3399进行多机通信。
 
![框架-工控机](https://user-images.githubusercontent.com/84019859/232474935-23d2e88b-83c4-454b-883f-deb010c8c711.png)




![e282582e45058430a3ec91b5ef68e14](https://user-images.githubusercontent.com/84019859/232469930-fcb0ad56-5f2d-4548-8096-922f7cd20c88.png)
![实验室建图2](https://user-images.githubusercontent.com/84019859/232491840-a10bdd55-4861-425c-8440-fc6eb494074b.png)
![大车车](https://user-images.githubusercontent.com/84019859/232491934-4603a3b0-c42d-4d78-842c-0e429c220e17.jpg)

