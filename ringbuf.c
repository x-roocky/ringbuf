#include "ringbuf.h"
#include <memory.h>

static inline int unused(const struct ringbuf *p) {
    return p->mask - ((p->tail - p->head) & p->mask);
}

static inline int min(int a, int b) {
    return a > b ? b : a; 
}

void ringbuf_init(struct ringbuf *p, void *data, int size) {
    p->head = 0;
    p->tail = 0;
    p->data = data;
    p->mask = (unsigned short)(size - 1);
}

int ringbuf_put(struct ringbuf *p, const void *data, int length) {
    int tmp = unused(p);
	if (length > tmp)
		length = tmp;

	tmp = min(length, p->mask - p->tail + 1);
	memcpy(&p->data[p->tail], data, tmp);
	memcpy(p->data, data + tmp, length - tmp);

	p->tail = (p->tail + length) & p->mask;
	return length;
}

int ringbuf_peek(const struct ringbuf *p, void *buffer, int size) {
    int tmp = ringbuf_length(p);
	if (size > tmp)
		size = tmp;

	tmp = min(size, p->mask - p->head + 1);
	memcpy(buffer, p->data + p->head, tmp);
	memcpy(buffer + tmp, p->data, size - tmp);
    return size;
}

int ringbuf_get(struct ringbuf *p, void *buffer, int size) {
    size = ringbuf_peek(p, buffer, size);
    p->head = (p->head + size) & p->mask;
	return size;
}
