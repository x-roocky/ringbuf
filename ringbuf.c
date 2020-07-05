#include "ringbuf.h"
#include <string.h>

static inline size_t min(size_t a, size_t b) {
    return a > b ? b : a; 
}

static inline size_t skip(struct ringbuf *p, size_t length) {
    p->head = (p->head + length) & p->mask;
	return length;
}

void ringbuf_init(struct ringbuf *p, void *data, size_t size) {
    p->head = 0;
    p->tail = 0;
    p->data = data;
    p->mask = (unsigned short)(size - 1);
}

size_t ringbuf_put(struct ringbuf *p, const void *data, size_t length) {
	if (length <= (ringbuf_capacity(p) - ringbuf_length(p))) {
		size_t first = min(length, p->mask - p->tail + 1);
		memcpy(p->data + p->tail, data, first);
		memcpy(p->data, data + first, length - first);
		p->tail = (p->tail + length) & p->mask;
		return length;
	} else {
		return 0;
	}
}

size_t ringbuf_peek(const struct ringbuf *p, void *buffer, size_t size) {
    size_t first;

	size = min(size, ringbuf_length(p));
	first = min(size, p->mask - p->head + 1);
	memcpy(buffer, p->data + p->head, first);
	memcpy(buffer + first, p->data, size - first);

    return size;
}

size_t ringbuf_get(struct ringbuf *p, void *buffer, size_t size) {
	return skip(p, ringbuf_peek(p, buffer, size));
}

size_t ringbuf_skip(struct ringbuf *p, size_t length) {
	return skip(p, min(length, ringbuf_length(p)));
}
