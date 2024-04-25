#include "malloc.h"
#include "mem.h"
#include "str.h"
#include <stddef.h>

__attribute__((visibility("default")))
char* basename(const char* path) {
  char* p = strrchr(path, '/');
  return p ? p + 1 : (char*)path;
}
__attribute__((visibility("default")))
char* dirname(const char* path) {
  char* last_slash = path ? strrchr(path, '/') : NULL;
  if (last_slash && last_slash != path && readInt8(last_slash + 1) == '\0') {
    char* runp = last_slash;
    for (;runp != path; --runp)
      if (readInt8(runp - 1) != '/')
        break;
    if (runp != path)
      last_slash = memrchr(path, '/', runp - path);
  }
  if (last_slash) {
    char* runp = last_slash;
    for (;runp != path; --runp)
      if (readInt8(runp - 1) != '/')
        break;
    if (runp == path) {
      if (last_slash == path + 1)
        ++last_slash;
      else last_slash = (char*)path + 1;
    } else last_slash = runp;
    writeInt8(last_slash, '\0');
  } else path = ".";
  return (char*)path;
}
__attribute__((visibility("default")))
bool isalnum(char c) {
  return isdigit(c) || isalpha(c);
}
__attribute__((visibility("default")))
bool isalpha(char c) {
  return islower(c) || isupper(c);
}
__attribute__((visibility("default")))
bool isascii(char c) {
  return !(c & ~0x7F);
}
__attribute__((visibility("default")))
bool isblank(char c) {
  return c == ' ' || c == '\t';
}
__attribute__((visibility("default")))
bool iscntrl(char c) {
  return !(c & ~0x1F) || c == 0x7F;
}
__attribute__((visibility("default")))
bool isdigit(char c) {
  return c >= '0' && c <= '9';
}
__attribute__((visibility("default")))
bool isgraph(char c) {
  return c >= 0x21 && c <= 0x7E;
}
__attribute__((visibility("default")))
bool islower(char c) {
  return c >= 'a' && c <= 'z';
}
__attribute__((visibility("default")))
bool isupper(char c) {
  return c >= 'A' && c <= 'Z';
}
__attribute__((visibility("default")))
bool isprint(char c) {
  return c >= 0x20 && c <= 0x7E;
}
__attribute__((visibility("default")))
bool ispunct(char c) {
  return (c >= 0x21 && c <= 0x2F) ||
    (c >= 0x3A && c <= 0x40) ||
    (c >= 0x5B && c <= 0x60) ||
    (c >= 0x7B && c <= 0x7E);
}
__attribute__((visibility("default")))
bool isspace(char c) {
  return (c >= 0x09 && c <= 0x0D) || c == 0x20;
}
__attribute__((visibility("default")))
bool isxdigit(char c) {
  return isdigit(c) ||
    (c >= 'a' && c <= 'f') ||
    (c >= 'A' && c <= 'F');
}
__attribute__((visibility("default")))
char tolower(char c) {
  return isupper(c) ? c + 0x20 : c;
}
__attribute__((visibility("default")))
char toupper(char c) {
  return islower(c) ? c - 0x20 : c;
}
__attribute__((visibility("default")))
char toascii(char c) {
  return c & 0x7F;
}
__attribute__((visibility("default")))
char* strcat(char* dest, const char* src) {
  return strcpy(dest + strlen(dest), src);
}
__attribute__((visibility("default")))
char* strncat(char* dest, const char* src, uint32_t n) {
  return strncpy(dest + strlen(dest), src, n);
}
__attribute__((visibility("default")))
char* strchr(const char* str, char c) {
  char tmp;
  while ((tmp = readInt8((void*)str))) {
    if (tmp == c)
      return (char*)str;
    ++str;
  }
  return NULL;
}
__attribute__((visibility("default")))
char* strrchr(const char* str, char c) {
  char* ret = NULL;
  char tmp;
  while ((tmp = readInt8((void*)str))) {
    if (tmp == c)
      ret = (char*)str;
    ++str;
  }
  return ret;
}
__attribute__((visibility("default")))
int strcmp(const char* s1, const char* s2) {
  while (1) {
    char c1 = readInt8((void*)s1++);
    char c2 = readInt8((void*)s2++);
    if (c1 != c2)
      return c1 - c2;
    if (c1 == '\0')
      break;
  }
  return 0;
}
__attribute__((visibility("default")))
int strncmp(const char* s1, const char* s2, uint32_t n) {
  while (n--) {
    char c1 = readInt8((void*)s1++);
    char c2 = readInt8((void*)s2++);
    if (c1 != c2)
      return c1 - c2;
    if (c1 == '\0')
      break;
  }
  return 0;
}
__attribute__((visibility("default")))
int strcasecmp(const char* s1, const char* s2) {
  while (1) {
    char c1 = tolower(readInt8((void*)s1++));
    char c2 = tolower(readInt8((void*)s2++));
    if (c1 != c2)
      return c1 - c2;
    if (c1 == '\0')
      break;
  }
  return 0;
}
__attribute__((visibility("default")))
int strncasecmp(const char* s1, const char* s2, uint32_t n) {
  while (n--) {
    char c1 = tolower(readInt8((void*)s1++));
    char c2 = tolower(readInt8((void*)s2++));
    if (c1 != c2)
      return c1 - c2;
    if (c1 == '\0')
      break;
  }
  return 0;
}
__attribute__((visibility("default")))
char* strcpy(char* dest, const char* src) {
  char* ret = dest;
  while (writeInt8(dest++, readInt8((void*)src++)));
  return ret;
}
__attribute__((visibility("default")))
char* strncpy(char* dest, const char* src, uint32_t n) {
  char* ret = dest;
  while (n-- && writeInt8(dest++, readInt8((void*)src++)));
  return ret;
}
__attribute__((visibility("default")))
char* strdup(const char* str) {
  uint32_t len = strlen(str);
  char* ret = (char*)malloc(len + 1);
  if (!ret)
    return NULL;
  memcpy(ret, str, len);
  writeInt8(ret + len, '\0');
  return ret;
}
__attribute__((visibility("default")))
char* strndup(const char* str, uint32_t n) {
  uint32_t len = strnlen(str, n);
  char* ret = (char*)malloc(len + 1);
  if (!ret)
    return NULL;
  memcpy(ret, str, len);
  writeInt8(ret + len, '\0');
  return ret;
}
__attribute__((visibility("default")))
uint32_t strlen(const char* str) {
  const char* s = str;
  while (readInt8((void*)s)) ++s;
  return (uint32_t)(s - str);
}
__attribute__((visibility("default")))
uint32_t strnlen(const char* str, uint32_t n) {
  const char* s = str;
  while (n-- && readInt8((void*)s)) ++s;
  return (uint32_t)(s - str);
}
__attribute__((visibility("default")))
char* strpbrk(const char* str, const char* accept) {
  str += strcspn(str, accept);
  return readInt8((void*)str) ? (char*)str : NULL;
}
__attribute__((visibility("default")))
char* strsep(char** str, const char* dilem) {
  char* ret = (char*)readUint32(str);
  if (!ret)
    return NULL;
  uint32_t len = strcspn(ret, dilem);
  if (readInt8(ret + len) == '\0')
    writeUint32(str, (uint32_t)NULL);
  else {
    writeInt8(ret + len, '\0');
    writeUint32(str, (uint32_t)(ret + len + 1));
  }
  return ret;
}
__attribute__((visibility("default")))
uint32_t strspn(const char* str, const char* accept) {
  uint32_t ret = 0;
  while (readInt8((void*)str) && strchr(accept, readInt8((void*)str++)))
    ++ret;
  return ret;
}
__attribute__((visibility("default")))
uint32_t strcspn(const char* str, const char* reject) {
  uint32_t ret = 0;
  while (readInt8((void*)str) && !strchr(reject, readInt8((void*)str++)))
    ++ret;
  return ret;
}
__attribute__((visibility("default")))
char* strstr(const char* str, const char* substr) {
  return memmem(str, strlen(str), substr, strlen(substr));
}
__attribute__((visibility("default")))
char* strtok_r(char* str, const char* delim, char** saveptr) {
  if (!str)
    str = (char*)readUint32(saveptr);
  str += strspn(str, delim);
  if (readInt8(str) == '\0')
    return NULL;
  char* ret = str;
  str += strcspn(str, delim);
  if (readInt8(str) == '\0')
    writeUint32(saveptr, (uint32_t)str);
  else {
    writeInt8(str, '\0');
    writeUint32(saveptr, (uint32_t)(str + 1));
  }
  return ret;
}
__attribute__((visibility("default")))
char* strtok(char* str, const char* delim) {
  static char* last;
  return strtok_r(str, delim, &last);
}
__attribute__((visibility("default")))
double atof(const char* str) {
  return strtod(str, (char**)NULL);
}
__attribute__((visibility("default")))
int atoi(const char* str) {
  return strtol(str, (char**)NULL, 10);
}
__attribute__((visibility("default")))
long atol(const char* str) {
  return strtol(str, (char**)NULL, 10);
}
__attribute__((visibility("default")))
long long atoll(const char* str) {
  return strtoll(str, (char**)NULL, 10);
}
__attribute__((visibility("default")))
double strtod(const char* str, char** endptr) {
  double ret = 0.0;
  int sign = 1;
  while (isblank(readInt8((void*)str)))
    ++str;
  if (readInt8((void*)str) == '-') {
    sign = -1;
    ++str;
  } else if (readInt8((void*)str) == '+')
    ++str;
  if (tolower(readInt8((void*)str)) == 'i') {
    if (strncasecmp(str, "inf", 3) == 0)
      return (1.0 * sign) / 0.0;
  } else if (tolower(readInt8((void*)str)) == 'n') {
    if (strncasecmp(str, "nan", 3) == 0)
      return (0.0 * sign) / 0.0;
  }
  while (isdigit(readInt8((void*)str)))
    ret = (ret * 10.0) + (readInt8((void*)str++) - '0');
  if (readInt8((void*)str) == '.') {
    ++str;
    int fracLen = 0;
    while (isdigit(readInt8((void*)str))) {
      ++str;
      ++fracLen;
    }
    str -= fracLen;
    double frac = 0.0;
    for (int i = 0; i != fracLen; ++i)
      frac = (frac * 10.0) + (readInt8((void*)str++) - '0');
    if (frac != 0.0) {
      while (fracLen--)
        frac /= 10.0;
      ret += frac;
    }
  }
  if (tolower(readInt8((void*)str)) == 'e') {
    ++str;
    int exp_sign = 1;
    if (readInt8((void*)str) == '-') {
      exp_sign = -1;
      ++str;
    } else if (readInt8((void*)str) == '+')
      ++str;
    int exp = 0;
    while (isdigit(readInt8((void*)str)))
      exp = (exp * 10) + (readInt8((void*)str++) - '0');
    if (exp_sign == 1) {
      while (exp--)
        ret *= 10.0;
    } else {
      while (exp--)
        ret /= 10.0;
    }
  }
  if (endptr)
    writeUint32(endptr, (uint32_t)str);
  return ret * sign;
}
__attribute__((visibility("default")))
float strtof(const char* str, char** endptr) {
  float ret = 0.0f;
  int sign = 1;
  while (isblank(readInt8((void*)str)))
    ++str;
  if (readInt8((void*)str) == '-') {
    sign = -1;
    ++str;
  } else if (readInt8((void*)str) == '+')
    ++str;
  if (tolower(readInt8((void*)str)) == 'i') {
    if (strncasecmp(str, "inf", 3) == 0)
      return (1.0f * sign) / 0.0f;
  } else if (tolower(readInt8((void*)str)) == 'n') {
    if (strncasecmp(str, "nan", 3) == 0)
      return (0.0f * sign) / 0.0f;
  }
  while (isdigit(readInt8((void*)str)))
    ret = (ret * 10.0f) + (readInt8((void*)str++) - '0');
  if (readInt8((void*)str) == '.') {
    ++str;
    int fracLen = 0;
    while (isdigit(readInt8((void*)str))) {
      ++str;
      ++fracLen;
    }
    str -= fracLen;
    float frac = 0.0f;
    for (int i = 0; i != fracLen; ++i)
      frac = (frac * 10.0f) + (readInt8((void*)str++) - '0');
    if (frac != 0.0f) {
      while (fracLen--)
        frac /= 10.0f;
      ret += frac;
    }
  }
  if (tolower(readInt8((void*)str)) == 'e') {
    ++str;
    int exp_sign = 1;
    if (readInt8((void*)str) == '-') {
      exp_sign = -1;
      ++str;
    } else if (readInt8((void*)str) == '+')
      ++str;
    int exp = 0;
    while (isdigit(readInt8((void*)str)))
      exp = (exp * 10) + (readInt8((void*)str++) - '0');
    if (exp_sign == 1) {
      while (exp--)
        ret *= 10.0f;
    } else {
      while (exp--)
        ret /= 10.0f;
    }
  }
  if (endptr)
    writeUint32(endptr, (uint32_t)str);
  return ret * sign;
}
__attribute__((visibility("default")))
long strtol(const char* str, char** endptr, int base) {
  long ret = 0;
  int sign = 1;
  while (isblank(readInt8((void*)str)))
    ++str;
  if (readInt8((void*)str) == '-') {
    sign = -1;
    ++str;
  } else if (readInt8((void*)str) == '+')
    ++str;
  if (base == 0) {
    if (readInt8((void*)str) == '0') {
      ++str;
      if (tolower(readInt8((void*)str)) == 'x') {
        base = 16;
        ++str;
      } else base = 8;
    } else base = 10;
  } else if (base == 8) {
    if (readInt8((void*)str) == '0')
      ++str;
  } else if (base == 16) {
    if (readInt8((void*)str) == '0') {
      ++str;
      if (tolower(readInt8((void*)str)) == 'x')
        ++str;
    }
  }
  while (readInt8((void*)str) == '0')
    ++str;
  while (readInt8((void*)str)) {
    int digit;
    if (readInt8((void*)str) >= '0' && readInt8((void*)str) <= '0' + base - 1)
      digit = readInt8((void*)str) - '0';
    else if (base > 10) {
      char lowc = tolower(readInt8((void*)str));
      if (lowc >= 'a' && lowc <= 'a' + base - 11)
        digit = lowc - 'a' + 10;
      else break;
    } else break;
    ret = (ret * base) + digit;
    ++str;
  }
  if (endptr)
    writeUint32(endptr, (uint32_t)str);
  return ret * sign;
}
__attribute__((visibility("default")))
long long strtoll(const char* str, char** endptr, int base) {
  long long ret = 0;
  int sign = 1;
  while (isblank(readInt8((void*)str)))
    ++str;
  if (readInt8((void*)str) == '-') {
    sign = -1;
    ++str;
  } else if (readInt8((void*)str) == '+')
    ++str;
  if (base == 0) {
    if (readInt8((void*)str) == '0') {
      ++str;
      if (tolower(readInt8((void*)str)) == 'x') {
        base = 16;
        ++str;
      } else base = 8;
    } else base = 10;
  } else if (base == 8) {
    if (readInt8((void*)str) == '0')
      ++str;
  } else if (base == 16) {
    if (readInt8((void*)str) == '0') {
      ++str;
      if (tolower(readInt8((void*)str)) == 'x')
        ++str;
    }
  }
  while (readInt8((void*)str) == '0')
    ++str;
  while (readInt8((void*)str)) {
    int digit;
    if (readInt8((void*)str) >= '0' && readInt8((void*)str) <= '0' + base - 1)
      digit = readInt8((void*)str) - '0';
    else if (base > 10) {
      char lowc = tolower(readInt8((void*)str));
      if (lowc >= 'a' && lowc <= 'a' + base - 11)
        digit = lowc - 'a' + 10;
      else break;
    } else break;
    ret = (ret * base) + digit;
    ++str;
  }
  if (endptr)
    writeUint32(endptr, (uint32_t)str);
  return ret * sign;
}
__attribute__((visibility("default")))
unsigned long strtoul(const char* str, char** endptr, int base) {
  unsigned long ret = 0;
  int sign = 1;
  while (isblank(readInt8((void*)str)))
    ++str;
  if (readInt8((void*)str) == '-') {
    sign = -1;
    ++str;
  } else if (readInt8((void*)str) == '+')
    ++str;
  if (base == 0) {
    if (readInt8((void*)str) == '0') {
      ++str;
      if (tolower(readInt8((void*)str)) == 'x') {
        base = 16;
        ++str;
      } else base = 8;
    } else base = 10;
  } else if (base == 8) {
    if (readInt8((void*)str) == '0')
      ++str;
  } else if (base == 16) {
    if (readInt8((void*)str) == '0') {
      ++str;
      if (tolower(readInt8((void*)str)) == 'x')
        ++str;
    }
  }
  while (readInt8((void*)str) == '0')
    ++str;
  while (readInt8((void*)str)) {
    int digit;
    if (readInt8((void*)str) >= '0' && readInt8((void*)str) <= '0' + base - 1)
      digit = readInt8((void*)str) - '0';
    else if (base > 10) {
      char lowc = tolower(readInt8((void*)str));
      if (lowc >= 'a' && lowc <= 'a' + base - 11)
        digit = lowc - 'a' + 10;
      else break;
    } else break;
    ret = (ret * base) + digit;
    ++str;
  }
  if (endptr)
    writeUint32(endptr, (uint32_t)str);
  return ret * sign;
}
__attribute__((visibility("default")))
unsigned long long strtoull(const char* str, char** endptr, int base) {
  unsigned long long ret = 0;
  int sign = 1;
  while (isblank(readInt8((void*)str)))
    ++str;
  if (readInt8((void*)str) == '-') {
    sign = -1;
    ++str;
  } else if (readInt8((void*)str) == '+')
    ++str;
  if (base == 0) {
    if (readInt8((void*)str) == '0') {
      ++str;
      if (tolower(readInt8((void*)str)) == 'x') {
        base = 16;
        ++str;
      } else base = 8;
    } else base = 10;
  } else if (base == 8) {
    if (readInt8((void*)str) == '0')
      ++str;
  } else if (base == 16) {
    if (readInt8((void*)str) == '0') {
      ++str;
      if (tolower(readInt8((void*)str)) == 'x')
        ++str;
    }
  }
  while (readInt8((void*)str) == '0')
    ++str;
  while (readInt8((void*)str)) {
    int digit;
    if (readInt8((void*)str) >= '0' && readInt8((void*)str) <= '0' + base - 1)
      digit = readInt8((void*)str) - '0';
    else if (base > 10) {
      char lowc = tolower(readInt8((void*)str));
      if (lowc >= 'a' && lowc <= 'a' + base - 11)
        digit = lowc - 'a' + 10;
      else break;
    } else break;
    ret = (ret * base) + digit;
    ++str;
  }
  if (endptr)
    writeUint32(endptr, (uint32_t)str);
  return ret * sign;
}
__attribute__((visibility("default")))
int strverscmp(const char* s1, const char* s2) {
  while (1) {
    char c1 = readInt8((void*)s1++);
    char c2 = readInt8((void*)s2++);
    if (c1 != c2) {
      if (c1 == '\0' || c2 == '\0')
        return c1 - c2;
      if (isdigit(c1) &&
          isdigit(c2)) {
        int i1 = c1 - '0';
        int i2 = c2 - '0';
        while (isdigit(readInt8((void*)s1)))
          i1 = (i1 * 10) + (readInt8((void*)s1++) - '0');
        while (isdigit(readInt8((void*)s2)))
          i2 = (i2 * 10) + (readInt8((void*)s2++) - '0');
        if (i1 != i2)
          return i1 - i2;
      } else return c1 - c2;
    } else if (c1 == '\0')
      break;
  }
  return 0;
}