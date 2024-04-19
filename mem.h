#include <stdint.h>

int bcmp(const void* s1, const void* s2, uint32_t n);
void* bcopy(const void* src, void* dest, uint32_t n);
void* bzero(void* s, uint32_t n);
void* memchr(const void* s, char c, uint32_t n);
void* memrchr(const void* s, char c, uint32_t n);
void* rawmemchr(const void* s, char c);
int memcmp(const void* s1, const void* s2, uint32_t count);
void* memcpy(void* dest, const void* src, uint32_t len);
void* memccpy(void* dest, const void* src, char c, uint32_t len);
void* mempcpy(void* dest, const void* src, uint32_t len);
void* memfrob(void* s, uint32_t n);
void* memmem(const void* haystack, uint32_t haystack_len, const void* needle, uint32_t needle_len);
void* memmove(void* dest, const void* src, uint32_t len);
void* memset(void* dst, char c, uint32_t len);
void swab(const void* src, void* dest, uint32_t n);