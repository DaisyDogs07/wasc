#include "mem.h"
#include <stddef.h>

__attribute__((visibility("default")))
int bcmp(const void* s1, const void* s2, uint32_t n) {
  return memcmp(s1, s2, n);
}
__attribute__((visibility("default")))
void* bcopy(const void* src, void* dest, uint32_t n) {
  return memmove(dest, src, n);
}
__attribute__((visibility("default")))
void* bzero(void* s, uint32_t n) {
  return memset(s, '\0', n);
};
__attribute__((visibility("default")))
void* memchr(const void* s, char c, uint32_t n) {
  const char* str = (const char*)s;
  while (n--) {
    if (*str == c)
      return (void*)str;
    ++str;
  }
  return NULL;
}
__attribute__((visibility("default")))
void* memrchr(const void* s, char c, uint32_t n) {
  const char* str = (const char*)s;
  str += n - 1;
  while (n--) {
    if (*str == c)
      return (void*)str;
    --str;
  }
  return NULL;
}
__attribute__((visibility("default")))
void* rawmemchr(const void* s, char c) {
  const char* str = (const char*)s;
  while (1) {
    if (*str == c)
      return (void*)str;
    ++str;
  }
  return NULL;
}
__attribute__((visibility("default")))
int memcmp(const void* s1, const void* s2, uint32_t count) {
  const char* str1 = (const char*)s1;
  const char* str2 = (const char*)s2;
  while (--count) {
    char c1 = *str1++;
    char c2 = *str2++;
    if (c1 != c2)
      return c1 - c2;
  }
  return 0;
}
__attribute__((visibility("default")))
void* memcpy(void* dest, const void* src, uint32_t len) {
  char* d = (char*)dest;
  const char* s = (const char*)src;
  while (len--)
    *d++ = *s++;
  return dest;
}
__attribute__((visibility("default")))
void* memccpy(void* dest, const void* src, char c, uint32_t len) {
  char* d = (char*)dest;
  const char* s = (const char*)src;
  while (len--) {
    *d++ = *s;
    if (*s++ == c)
      return d;
  }
  return NULL;
}
__attribute__((visibility("default")))
void* mempcpy(void* dest, const void* src, uint32_t len) {
  char* d = (char*)dest;
  const char* s = (const char*)src;
  while (len--)
    *d++ = *s++;
  return d;
}
__attribute__((visibility("default")))
void* memfrob(void* s, uint32_t n) {
  char* str = (char*)s;
  while (n--)
    *str++ ^= 42;
  return s;
}
__attribute__((visibility("default")))
void* memmem(const void* haystack, uint32_t haystack_len, const void* needle, uint32_t needle_len) {
  const char* h = (const char*)haystack;
  const char* n = (const char*)needle;
  if (needle_len == 0)
    return (void*)h;
  while (haystack_len-- >= needle_len) {
    if (*h == *n && memcmp(h, n, needle_len) == 0)
      return (void*)h;
    ++h;
  }
  return NULL;
}
__attribute__((visibility("default")))
void* memmove(void* dest, const void* src, uint32_t len) {
  char* d = (char*)dest;
  const char* s = (const char*)src;
  if (d < s)
    while (len--)
      *d++ = *s++;
  else {
    char* lastd = d + (len - 1);
    const char* lasts = s + (len - 1);
    while (len--)
      *lastd-- = *lasts--;
  }
  return dest;
}
__attribute__((visibility("default")))
void* memset(void* dst, char c, uint32_t len) {
  char* p = (char*)dst;
  while (len--)
    *p++ = c;
  return dst;
}
__attribute__((visibility("default")))
void swab(const void* src, void* dest, uint32_t n) {
  const char* s = (const char*)src;
  char* d = (char*)dest;
  n &= ~1;
  while (n > 1) {
    char c = *s++;
    *d++ = *s++;
    *d++ = c;
    n -= 2;
  }
}