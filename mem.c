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
void* memchr(const void* s, uint8_t c, uint32_t n) {
  const uint8_t* str = (const uint8_t*)s;
  uint32_t i = 0;
  {
    uint32_t pattern = 0x01010101;
    uint32_t targetChunk = pattern * c;
    uint32_t mask = 0x80808080;
    while (n - i >= sizeof(uint32_t)) {
      uint32_t chunk = *(uint32_t*)&str[i];
      uint32_t comparison = chunk ^ targetChunk;
      if (((comparison - pattern) & ~comparison) & mask)
        break;
      i += sizeof(uint32_t);
    }
  }
  {
    uint16_t pattern = 0x0101;
    uint16_t targetChunk = pattern * c;
    uint16_t mask = 0x8080;
    while (n - i >= sizeof(uint16_t)) {
      uint16_t chunk = *(uint16_t*)&str[i];
      uint16_t comparison = chunk ^ targetChunk;
      if (((comparison - pattern) & ~comparison) & mask)
        break;
      i += sizeof(uint16_t);
    }
  }
  while (n - i >= sizeof(uint8_t)) {
    if (str[i] == c)
      return (void*)&str[i];
    i += sizeof(uint8_t);
  }
  return NULL;
}
__attribute__((visibility("default")))
void* memrchr(const void* s, uint8_t c, uint32_t n) {
  const uint8_t* str = (const uint8_t*)s;
  {
    uint32_t pattern = 0x01010101;
    uint32_t targetChunk = pattern * c;
    uint32_t mask = 0x80808080;
    while (n >= sizeof(uint32_t)) {
      uint32_t chunk = *(uint32_t*)&str[n - sizeof(uint32_t)];
      uint32_t comparison = chunk ^ targetChunk;
      if (((comparison - pattern) & ~comparison) & mask)
        break;
      n -= sizeof(uint32_t);
    }
  }
  {
    uint16_t pattern = 0x0101;
    uint16_t targetChunk = pattern * c;
    uint16_t mask = 0x8080;
    while (n >= sizeof(uint16_t)) {
      uint16_t chunk = *(uint16_t*)&str[n - sizeof(uint16_t)];
      uint16_t comparison = chunk ^ targetChunk;
      if (((comparison - pattern) & ~comparison) & mask)
        break;
      n -= sizeof(uint16_t);
    }
  }
  while (n >= sizeof(uint8_t)) {
    if (str[n - sizeof(uint8_t)] == c)
      return (void*)&str[n - sizeof(uint8_t)];
    n -= sizeof(uint8_t);
  }
  return NULL;
}
__attribute__((visibility("default")))
int memcmp(const void* s1, const void* s2, uint32_t count) {
  const uint8_t* str1 = (const uint8_t*)s1;
  const uint8_t* str2 = (const uint8_t*)s2;
  uint32_t i = 0;
  while (count - i >= sizeof(uint32_t)) {
    uint32_t c1 = *(uint32_t*)&str1[i];
    uint32_t c2 = *(uint32_t*)&str2[i];
    if (c1 != c2)
      break;
    i += sizeof(uint32_t);
  }
  while (count - i >= sizeof(uint16_t)) {
    uint16_t c1 = *(uint16_t*)&str1[i];
    uint16_t c2 = *(uint16_t*)&str2[i];
    if (c1 != c2)
      break;
    i += sizeof(uint16_t);
  }
  while (count - i >= sizeof(uint8_t)) {
    uint8_t c1 = *(uint8_t*)&str1[i];
    uint8_t c2 = *(uint8_t*)&str2[i];
    if (c1 != c2)
      return c1 - c2;
    i += sizeof(uint8_t);
  }
  return 0;
}
__attribute__((visibility("default")))
void* memcpy(void* dest, const void* src, uint32_t len) {
  uint8_t* d = (uint8_t*)dest;
  const uint8_t* s = (const uint8_t*)src;
  uint32_t i = 0;
  while (len - i >= sizeof(uint32_t)) {
    *(uint32_t*)&d[i] = *(uint32_t*)&s[i];
    i += sizeof(uint32_t);
  }
  while (len - i >= sizeof(uint16_t)) {
    *(uint16_t*)&d[i] = *(uint16_t*)&s[i];
    i += sizeof(uint16_t);
  }
  while (len - i >= sizeof(uint8_t)) {
    *(uint8_t*)&d[i] = *(uint8_t*)&s[i];
    i += sizeof(uint8_t);
  }
  return dest;
}
__attribute__((visibility("default")))
void* memccpy(void* dest, const void* src, uint8_t c, uint32_t len) {
  void* ch = memchr(src, c, len);
  if (!ch) {
    memcpy(dest, src, len);
    return NULL;
  }
  len = (uint32_t)(ch - src);
  memcpy(dest, src, len);
  return dest + len;
}
__attribute__((visibility("default")))
void* mempcpy(void* dest, const void* src, uint32_t len) {
  return memcpy(dest, src, len) + len;
}
__attribute__((visibility("default")))
void* memfrob(void* s, uint32_t n) {
  uint8_t* str = (uint8_t*)s;
  uint32_t i = 0;
  while (n - i >= sizeof(uint32_t)) {
    *(uint32_t*)&str[i] ^= 0x2a2a2a2a;
    i += sizeof(uint32_t);
  }
  while (n - i >= sizeof(uint16_t)) {
    *(uint16_t*)&str[i] ^= 0x2a2a;
    i += sizeof(uint16_t);
  }
  while (n - i >= sizeof(uint8_t)) {
    *(uint8_t*)&str[i] ^= 0x2a;
    i += sizeof(uint8_t);
  }
  return s;
}
__attribute__((visibility("default")))
void* memmem(const void* haystack, uint32_t haystack_len, const void* needle, uint32_t needle_len) {
  const uint8_t* h = (const uint8_t*)haystack;
  const uint8_t* n = (const uint8_t*)needle;
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
  if (dest < src)
    memcpy(dest, src, len);
  else {
    uint8_t* d = (uint8_t*)dest;
    const uint8_t* s = (const uint8_t*)src;
    while (len >= sizeof(uint32_t)) {
      *(uint32_t*)&d[len - sizeof(uint32_t)] = *(uint32_t*)&s[len - sizeof(uint32_t)];
      len -= sizeof(uint32_t);
    }
    while (len >= sizeof(uint16_t)) {
      *(uint16_t*)&d[len - sizeof(uint16_t)] = *(uint16_t*)&s[len - sizeof(uint16_t)];
      len -= sizeof(uint16_t);
    }
    while (len >= sizeof(uint8_t)) {
      *(uint8_t*)&d[len - sizeof(uint8_t)] = *(uint8_t*)&s[len - sizeof(uint8_t)];
      len -= sizeof(uint8_t);
    }
  }
  return dest;
}
__attribute__((visibility("default")))
void* memset(void* dst, uint8_t c, uint32_t len) {
  uint8_t* p = (uint8_t*)dst;
  uint32_t i = 0;
  {
    uint32_t cpatt = 0x01010101 * c;
    while (len - i >= sizeof(uint32_t)) {
      *(uint32_t*)&p[i] = cpatt;
      i += sizeof(uint32_t);
    }
  }
  {
    uint16_t cpatt = 0x0101 * c;
    while (len - i >= sizeof(uint16_t)) {
      *(uint16_t*)&p[i] = cpatt;
      i += sizeof(uint16_t);
    }
  }
  while (len - i >= sizeof(uint8_t)) {
    *(uint8_t*)&p[i] = c;
    i += sizeof(uint8_t);
  }
  return dst;
}
__attribute__((visibility("default")))
void swab(const void* src, void* dest, uint32_t n) {
  const uint8_t* s = (const uint8_t*)src;
  uint8_t* d = (uint8_t*)dest;
  n &= ~1;
  while (n > 1) {
    uint8_t c = *s++;
    *d++ = *s++;
    *d++ = c;
    n -= 2;
  }
}