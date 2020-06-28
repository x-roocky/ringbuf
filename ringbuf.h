#ifndef __RINGBUF_H__
#define __RINGBUF_H__

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
void ringbuf_init(struct ringbuf *p, void *data, int size_power_of_two);

/**
 * @brief 向ringbuf放入数据
 * 
 * @param p 
 * @param data 
 * @param length 
 * @return int 
 */
int ringbuf_put(struct ringbuf *p, const void *data, int length);

/**
 * @brief 从ringbuf获取数据
 * 
 * @param p 
 * @param buffer 
 * @param size 
 * @return int 
 */
int ringbuf_get(struct ringbuf *p, void *buffer, int size);

/**
 * @brief 从ringbuf获取数据，但不清空
 * 
 * @param p 
 * @param buffer 
 * @param size 
 * @return int 
 */
int ringbuf_peek(const struct ringbuf *p, void *buffer, int size);

/**
 * @brief 获取ringbuf总计可用空间(字节数)
 * 
 * @param p 
 * @return int 
 */
static inline int ringbuf_size(const struct ringbuf *p) {
    return p->mask;
}

/**
 * @brief 获取ringbuf已用长度(字节数)
 * 
 * @param p 
 * @return int 
 */
static inline int ringbuf_length(const struct ringbuf *p) {
    return (p->tail - p->head) & p->mask;
}

#endif /* __RINGBUF_H__ */
