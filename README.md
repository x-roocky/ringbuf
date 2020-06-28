## 背景

- 环形缓冲(RingBuffer)是常用结构，都会用到；
- 可每到用时，无法即刻找到顺手的。需求无非：无依赖、接口简单、消耗小；
- 由此，实现一套拿来即用的RingBuffer。

## 特性

- 无环境依赖，ringbuf.h/ringbuf.c拷贝即用；
- API简单而不单一，可看名字就用，也能扩展至DMA缓冲；
- 资源消耗小，入/出操作快，结构仅10字节。

## 参考

不是凭空造轮，参照以下实现：
- [linux/kfifo](https://github.com/torvalds/linux/blob/master/include/linux/kfifo.h): 设计够好，但依赖kernel
- [contiki/ringbuf](https://github.com/contiki-ng/contiki-ng/blob/develop/os/lib/ringbuf.h): 简洁优雅，功能非通用
