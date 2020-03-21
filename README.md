# 电脑远程开机卡

#### 未获作者允许禁止商用
#### 未获作者允许禁止商用
#### 未获作者允许禁止商用

#### 介绍
使用arduino编写代码，实现电脑远程开机，支持接入小爱同学。
### Bilibili教程 [av97705138](https://www.bilibili.com/video/av97705138)

#### 软件架构
软件架构说明
GITHUB:[GitHub点这里](https://github.com/dreamcmi/computer_remote_power_on_card)


| 功能     | 数据键名（大写） | 默认针脚（ESP8266） | 位置  |
| -------- | ---------------- | ------------------- | ----- |
| 开机     | PWR              | D5(GPIO14)          | 插孔1 |
| 重启     | RST              | D7(GPIO13)          | 插孔2 |
| 强制关机 | QPWR             | D5(GPIO14)          | 插孔3 |



#### 使用说明

1.  Arduino 1.8.12
2.  esp8266 开发板 2.6.3 选用（nodemcu0.9）
3.  Blinker库 [Blinker Github](https://github.com/blinker-iot/blinker-library)
4.  默认功能为高电平触发，须使用三极管，光耦，继电器之类进行触发，如想直接插在主板使用，把源码电平拉高和拉低倒置即可。

#### 参与贡献

作者：
梦程MI 【bilibili up主 UID： 88809897】
QQ群 866522149

### 2020-03-20 V1.1发布
1.更新版本号至V1.1  
2.修改接入模式为MULTI_OUTLET（V1.0.4那个灯的太沙雕了，必须换）  
3.新增强制关机功能（功能键名 QPWR    ）  
4.新增天猫精灵版源码  
5.新增ESPHome配置文件  

### 2020-02-28
重新上传，继续更新中。

### 2020-02-20
上传 Beta V1.0.4 ino代码