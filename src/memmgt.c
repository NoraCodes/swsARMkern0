/* memmgt.c
	Manage us some memory.
*/

#include "include/memmgt.h"

void *memcpy(void *dest, const void *src, size_t n) {
	char *d = dest;
	const char *s = src;
	size_t i;
	for(i = 0; i < n; i++) {
		d[i] = s[i];
	}
	return d;
}
