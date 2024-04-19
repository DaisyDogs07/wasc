#include <stdint.h>

void* malloc(uint32_t size);
void* calloc(uint32_t size, uint32_t nmemb);
void free(void* ptr);
void* realloc(void* ptr, uint32_t size);