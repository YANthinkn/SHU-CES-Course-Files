# Socket 通信 用户手册

| Course Name  | 计算机网络A 	|
| ------------ | ----------- |
| Course ID    | 08305142    |
| Teacher Name | 曹晨红      |
| Teacher ID   | 1005        |
| Student Name | 严昕宇 |
| Student ID   | 20121802 |

## 1 环境设置

**Operating System:** Windows 11 x64

**Program Language:** Python 3.9.13

**Libs/Modules:** PyQt5, socket, pyqt5, hashlib, threading, sys

## 2 界面介绍

## 2.1 Client Login Window

<img src="images\Main.png" alt="Main" style="zoom:50%;" />

<center> <b>Fig1. Server Login Window</b></center>

​	如图所示，为通信程序的登录界面。本项目使用了SQLite数据库存储用户数据为了信息安全，且在进行验证时采用SHA256加密验证。

​	若成功，则弹出Login!弹窗，并跳转到下一页面；否则根据不同的异常情况，弹出相应的Recheck弹窗。

<img src="images\Login.png" alt="Login" style="zoom:50%;" />

<img src="images\Psw.png" alt="Login" style="zoom:50%;" />

<img src="images\Usr.png" alt="Login" style="zoom:50%;" />

<center> <b>Fig2. Login Succeed/Failed</b></center>



## 2.2 Client Chat Window

​	在跳转后，在输入Host和Port后，服务器会创建socket，并等待客户端连接。

<img src="images\Client.png" alt="Client" style="zoom:50%;" />

<center> <b>Fig3. Server Chat Window</b></center>



## 2.3 Clinet Chat Window

​	显示连接成功信息，在下方消息框输入文字后按Send按钮，可发送信息。

<img src="images\ClientSend.png" alt="ClientSend" style="zoom:50%;" />

<center> <b>Fig4. Client Chat Window</b></center>

## 2.3 Server Chat Window

服务端省去了登录注册功能，其余功能与客户端相同。

<img src="images\Server.png" alt="Server" style="zoom:50%;" />