echo  'KERNEL=="ttyUSB*", ATTRS{idVendor}=="10c4", ATTRS{idProduct}=="ea60",ATTRS{serial}=="0003", MODE:="0777", GROUP:="dialout", SYMLINK+="fdilink_ahrs"' >/etc/udev/rules.d/fdilink_ahrs.rules


echo 'KERNEL=="ttyCH343USB*", ATTRS{idVendor}=="1a86", ATTRS{idProduct}=="55d4", MODE:="0777", GROUP:="dialout", SYMLINK+="wheeltec_ch340"' >/etc/udev/rules.d/wheeltec_fdcontroller.rules

echo  'KERNEL=="ttyACM*", ATTRS{idVendor}=="1a86", ATTRS{idProduct}=="55d4",ATTRS{serial}=="0003", MODE:="0777", GROUP:="dialout", SYMLINK+="fdilink_ahrs"' >/etc/udev/rules.d/wheeltec_fdilink.rules

echo 'KERNEL=="ttyUSB*", ATTRS{idVendor}=="1a86", ATTRS{idProduct}=="7523", MODE:="0777", GROUP:="dialout", SYMLINK+="wheeltec_ch340"' >/etc/udev/rules.d/wheeltec_fdcontroller_340.rules

service udev reload
sleep 2
service udev restart


