# Design Documentation

This project serves as the foundational coding initiative for the S32K144 chip

------

> [!NOTE]
>
> The list of learning tasks:
>
> - [x] Basic inputs and outputs of IO ports
>   - [x] lighting on-board LED
>   - [x] KEY control LED
>
> - [x] Blocking delay
>
> - [ ] Non-blocking delay
>   - [x] Timers
>   - [x] Timer interrupt
>
> - [ ] Communication protocol
>   - [x] UART
>   - [ ] IIC
>
>   - [ ] DMA
>   - [ ] UART+DMA
>
> - [x] ADC

------

## Components Library 组件（库）介绍

### PinSettings

用于引脚复用和引脚功能/电气属性的 S32 SDK 外设驱动程序。

#### ADC

暂无

#### CAN

暂无

#### CMP

暂无

#### EWM

暂无

#### FLEXIO

暂无

#### FTM

暂无

#### GPIO

1. 文字
1. ![pin_mux(GPIO)](C:\Users\zy\AppData\Roaming\Typora\typora-user-images\image-20250423233633606.png)

#### JTAG

暂无

#### LPI2C

暂无

#### LPSPI

暂无

#### LPTMR

暂无

#### LPUART

暂无

#### Platform

暂无

#### PowerAndGround

暂无

#### RTC

暂无

#### SWD

暂无

#### TRGMUX

暂无

### osif

内含一个毫秒级阻塞式延迟函数 `OSIF_TimeDelay()`，可以用。不用自己写延迟函数。



### lpuart

串口库。



### dmaController

dma 库



### ftm



#### ftm_mc



------

## 外设配置方法

### GPIO配置

#### GPIO配置步骤

1. 双击左下角==pin_mux:PinSettings==打开图形配置工具Component Inspector
     ![GPIO配置步骤1](C:\Users\zy\AppData\Roaming\Typora\typora-user-images\image-20250424003942465.png)

------

## 问题笔记

### 串口打印不出浮点数

原因：选择的库不支持 print 打印输出浮点数。创建工程时选择 `NewLib nano` 库，`NewLib nano` 库更紧凑，但缺少一些功能 - 例如浮点打印

解决方法一：右键工程文件夹 → Target Processor → Libraries support，换成不带 `nano` 的库。

<img src="https://github.com/1Q08/S32K144_Project/blob/main/img_readme/%E8%A7%A3%E5%86%B3%E6%96%B9%E6%B3%95%E4%B8%80.png?raw=true" alt="修复一.png" style="zoom:50%;" />

解决方法二：右键工程文件夹 → Standard S32DS C Linker → Miscellaneous，勾选 `Support print float format for newlib_nano library (-u_printf float)` 选项。

<img src="https://github.com/1Q08/S32K144_Project/blob/main/img_readme/%E8%A7%A3%E5%86%B3%E6%96%B9%E6%B3%95%E4%BA%8C.png?raw=true" alt="修复二.png" style="zoom:50%;" />

### 项目文件图标右下角有问号、星号等图标是什么意思

原因：S32DS 自带版本控制工具，如果不需要可以关闭，也可以学习使用怎么使用。

### 如何生成二进制文件？

项目创建后默认编译不生成二进制文件，可通过右键工程文件夹 → C/C++ Build → Settings → Cross Settings，勾选Create flash image即可。

### 编译优化等级

右键工程文件夹 → C/C++ Build → Settings → Standard S32DS C Compiler → Optimization中Optimization Level选择None(-O0)

### S32DS汉化

Eclipse汉化后怎么改回英文版

------

## 指南版本管理

Typora 版本：Typora for Windows(Typora) V1.9.5

使用插件：[**Typora Plugin V1.13.10**](https://github.com/obgnail/typora_plugin)

推荐主题：Mdmdt Dark

推荐链接：[**Typora 官方中文站**](https://typoraio.cn/)

> ​                                                                                                **Prepared by 老张同志**
