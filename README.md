# RFIDTOOLS2
RFID 读写小工具

# 使用说明

## 界面
![图1](http://github.com/rocuku/RFIDTOOLS2/blob/v1.0/images/1.png)

### 串口通信设置
下图红框为串口设置位置，每次改变参数后需要点击一下Serial单选框更新串口状态
![图2](http://github.com/rocuku/RFIDTOOLS2/blob/v1.0/images/2.png)

### TCP/UDP通信设置
下图红框为TCP/UDP参数设置位置，需要根据WiFi模块的工作模式，IP，端口等参数设置，改变之后需要重新点击最右的按钮（根据模式不同按钮名称不同）更新状态。
![图3](http://github.com/rocuku/RFIDTOOLS2/blob/v1.0/images/3.png)

### 命令直发窗口
下图红框为命令直发窗口，输入命令后按回车键即可发送。最右HEX选框作为判断命令直发窗口中的输入作为HEX还是一般字符发送，鉴于手册上的命令都是以HEX格式说明的，所以该选框在正常情况下都应该处于勾选状态。 
![图4](http://github.com/rocuku/RFIDTOOLS2/blob/v1.0/images/4.png)


### 选择命令发送窗口
下图红框中为选择命令发送窗口，直接选择所需命令根据提示填充内容最后点击按钮即可。该窗口中的所有项目都是在程序同级目录下的setting.xml中定义的。
![图5](http://github.com/rocuku/RFIDTOOLS2/blob/v1.0/images/5.png)
setting.xml部分截图如下图。现在已经添加了SSRFID V3.0 Manual中所有命令。
![图6](http://github.com/rocuku/RFIDTOOLS2/blob/v1.0/images/6.png)

### Log窗口
下图红框位置为Log窗口。Hex选框切换输出的Log格式，CLEAR按钮清楚Log历史记录。
![图7](http://github.com/rocuku/RFIDTOOLS2/blob/v1.0/images/7.png)
