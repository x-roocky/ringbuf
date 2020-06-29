#ifndef __RINGBUF_H__
#define __RINGBUF_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

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
 * @brief 获取ringbuf总计可用空间(字节数)
 * 
 * @param p 
 * @return size_t 
 */
static inline size_t ringbuf_size(const struct ringbuf *p) {
    return p->mask;
}

/**
 * @brief 获取ringbuf已用长度(字节数)
 * 
 * @param p 
 * @return size_t 
 */
static inline size_t ringbuf_length(const struct ringbuf *p) {
    return (p->tail - p->head) & p->mask;
}

#ifdef __cplusplus
}
#endif

#endif /* __RINGBUF_H__ */
