# Design Documentation

This project serves as the foundational coding initiative for the S32K144 chip

------

>   [!NOTE]
>
>   The list of learning tasks:
>
>   - [x] Basic inputs and outputs of IO ports (lighting on-board LEDs,KEY control LED,)
>   - [x] Blocking delay
>   - [x] Communication protocol(UART,)
>   - [ ] DMA(UART+DMA,)

------

## Components Library组件库介绍

### osif

内含一个毫秒级阻塞式延迟函数`OSIF_TimeDelay()`，可以用。不用自己写延迟函数。



### lpuart

串口库。



### dmaController

dma库
