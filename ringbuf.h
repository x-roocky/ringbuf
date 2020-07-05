#ifndef __RINGBUF_H__
#define __RINGBUF_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RINGBUF_CONCAT2(s1, s2) s1##s2
#define RINGBUF_CONCAT(s1, s2)  RINGBUF_CONCAT2(s1, s2)

/**
 * @brief 环形缓冲结构(最大支持64KB)
 * 
 */
struct ringbuf {
    unsigned short head;
    unsigned short tail;
    unsigned char *data;
    unsigned short mask;
};

/**
 * 静态定义并初始化ringbuf
 * 
 * @name: 定义的变量名
 * @size_power_of_two: 缓冲区大小（字节数），必须是2的倍数
 *
 */
#define RINGBUF_DEFINE(name, size_power_of_two) \
    static unsigned char RINGBUF_CONCAT(name, _buffer4ringbuf_)[size_power_of_two]; \
    static struct ringbuf name = { \
        .head = 0, \
        .tail = 0, \
        .data = RINGBUF_CONCAT(name, _buffer4ringbuf_), \
        .mask = size_power_of_two - 1, \
    }

/**
 * @brief 初始化ringbuf
 * 
 * @param p 
 * @param data 
 * @param size_power_of_two 
 */
void ringbuf_init(struct ringbuf *p, void *data, size_t size_power_of_two);

/**
 * @brief 向ringbuf放入数据
 * 
 * @param p 
 * @param data 
 * @param length 
 * @return size_t 
 */
size_t ringbuf_put(struct ringbuf *p, const void *data, size_t length);

/**
 * @brief 从ringbuf获取数据
 * 
 * @param p 
 * @param buffer 
 * @param size 
 * @return size_t 
 */
size_t ringbuf_get(struct ringbuf *p, void *buffer, size_t size);

/**
 * @brief 从ringbuf获取数据，但不清空
 * 
 * @param p 
 * @param buffer 
 * @param size 
 * @return size_t 
 */
size_t ringbuf_peek(const struct ringbuf *p, void *buffer, size_t size);

/**
 * @brief 从ringbuf头部跳过(丢弃)数据
 * 
 * @param p 
 * @param length 
 * @return size_t 
 */
size_t ringbuf_skip(struct ringbuf *p, size_t length);

/**
 * @brief 返回ringbuf总容量(字节数)
 * 
 * @param p 
 * @return size_t 
 */
static inline size_t ringbuf_capacity(const struct ringbuf *p) {
    return p->mask;
}

/**
 * @brief 返回ringbuf已占用空间（字节数）
 * 
 * @param p 
 * @return size_t
 */
static inline size_t ringbuf_length(const struct ringbuf *p) {
    return (p->tail - p->head) & p->mask;
}

/**
 * @brief 返回ringbuf剩余可用空间（字节数）
 * 
 * @param p 
 * @return size_t 
 */
static inline size_t ringbuf_avail(const struct ringbuf *p) {
    return ringbuf_capacity(p) - ringbuf_length(p);
}

#ifdef __cplusplus
}
#endif

#endif /* __RINGBUF_H__ */
