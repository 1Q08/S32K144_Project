# Design Documentation

This project serves as the foundational coding initiative for the S32K144 chip

------

>   [!NOTE]
>
>   The list of learning tasks:
>
>   - [x] Basic inputs and outputs of IO ports
>     - [x] lighting on-board LED
>     - [x] KEY control LED
>   - [x] Blocking delay
>   - [ ] Non-blocking delay
>     - [ ] Timers
>   - [ ] Communication protocol
>     - [x] UART
>     - [ ] IIC
>   - [ ] DMA
>     - [ ] UART+DMA
>   - [x] ADC
>   - [ ] 

------

## Components Library组件（库）介绍

### osif

内含一个毫秒级阻塞式延迟函数`OSIF_TimeDelay()`，可以用。不用自己写延迟函数。



### lpuart

串口库。



### dmaController

dma库



------

## 问题笔记

### 1. 串口打印不出浮点数

选择的库不支持print输出浮点数。创建工程时选择`NewLib nano`库，`NewLib nano`库更紧凑，但缺少一些功能 - 例如浮点打印。右键工程文件夹->Target Processor->Libraries support，换成不带`nano`的库。

![image-20250220020327331.png](https://github.com/1Q08/S32K144_Project/blob/main/img_readme/image-20250220020327331.png?raw=true)



### 2.
