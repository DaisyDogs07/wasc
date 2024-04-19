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
  if (last_slash && last_slash != path && last_slash[1] == '\0') {
    char* runp = last_slash;
    for (;runp != path; --runp)
      if (runp[-1] != '/')
        break;
    if (runp != path)
      last_slash = memrchr(path, '/', runp - path);
  }
  if (last_slash) {
    char* runp = last_slash;
    for (;runp != path; --runp)
      if (runp[-1] != '/')
        break;
    if (runp == path) {
      if (last_slash == path + 1)
        ++last_slash;
      else last_slash = (char*)path + 1;
    } else last_slash = runp;
    last_slash[0] = '\0';
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
  while (*str) {
    if (*str == c)
      return (char*)str;
    ++str;
  }
  return NULL;
}
__attribute__((visibility("default")))
char* strrchr(const char* str, char c) {
  char* ret = NULL;
  while (*str) {
    if (*str == c)
      ret = (char*)str;
    ++str;
  }
  return ret;
}
__attribute__((visibility("default")))
int strcmp(const char* s1, const char* s2) {
  while (1) {
    char c1 = *s1++;
    char c2 = *s2++;
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
    char c1 = *s1++;
    char c2 = *s2++;
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
    char c1 = tolower(*s1++);
    char c2 = tolower(*s2++);
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
    char c1 = tolower(*s1++);
    char c2 = tolower(*s2++);
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
  while ((*dest++ = *src++));
  return ret;
}
__attribute__((visibility("default")))
char* strncpy(char* dest, const char* src, uint32_t n) {
  char* ret = dest;
  while (n-- && (*dest++ = *src++));
  return ret;
}
__attribute__((visibility("default")))
char* strdup(const char* str) {
  uint32_t len = strlen(str);
  char* ret = (char*)malloc(len + 1);
  memcpy(ret, str, len);
  ret[len] = '\0';
  return ret;
}
__attribute__((visibility("default")))
char* strndup(const char* str, uint32_t n) {
  uint32_t len = strnlen(str, n);
  char* ret = (char*)malloc(len + 1);
  memcpy(ret, str, len);
  ret[len] = '\0';
  return ret;
}
__attribute__((visibility("default")))
uint32_t strlen(const char* str) {
  uint32_t i = 0;
  while (*str++) ++i;
  return i;
}
__attribute__((visibility("default")))
uint32_t strnlen(const char* str, uint32_t n) {
  uint32_t i = 0;
  while (i != n && *str++) ++i;
  return i;
}
__attribute__((visibility("default")))
char* strpbrk(const char* str, const char* accept) {
  str += strcspn(str, accept);
  return *str ? (char*)str : NULL;
}
__attribute__((visibility("default")))
char* strsep(char** str, const char* dilem) {
  char* ret = *str;
  if (!ret)
    return NULL;
  uint32_t len = strcspn(ret, dilem);
  if (ret[len] == '\0')
    *str = NULL;
  else {
    ret[len] = '\0';
    *str = ret + len + 1;
  }
  return ret;
}
__attribute__((visibility("default")))
uint32_t strspn(const char* str, const char* accept) {
  uint32_t ret = 0;
  while (*str && strchr(accept, *str++))
    ++ret;
  return ret;
}
__attribute__((visibility("default")))
uint32_t strcspn(const char* str, const char* reject) {
  uint32_t ret = 0;
  while (*str && !strchr(reject, *str++))
    ++ret;
  return ret;
}
__attribute__((visibility("default")))
char* strstr(const char* str, const char* substr) {
  uint32_t len = strlen(substr);
  while (*str) {
    if (strncmp(str, substr, len) == 0)
      return (char*)str;
    ++str;
  }
  return NULL;
}
__attribute__((visibility("default")))
char* strtok_r(char* str, const char* delim, char** saveptr) {
  if (!str)
    str = *saveptr;
  str += strspn(str, delim);
  if (*str == '\0')
    return NULL;
  char* ret = str;
  str += strcspn(str, delim);
  if (*str == '\0')
    *saveptr = str;
  else {
    *str = '\0';
    *saveptr = str + 1;
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
  int32_t sign = 1;
  while (isblank(*str))
    ++str;
  if (*str == '-') {
    sign = -1;
    ++str;
  } else if (*str == '+')
    ++str;
  if (tolower(*str) == 'i') {
    char* tmp = strndup(str, 3);
    for (int32_t i = 0; tmp[i]; ++i)
      tmp[i] = tolower(tmp[i]);
    if (strncmp(tmp, "inf", 3) == 0) {
      free(tmp);
      return (1.0 * sign) / 0.0;
    }
    free(tmp);
  } else if (tolower(*str) == 'n') {
    char* tmp = strndup(str, 3);
    for (int32_t i = 0; tmp[i]; ++i)
      tmp[i] = tolower(tmp[i]);
    if (strncmp(tmp, "nan", 3) == 0) {
      free(tmp);
      return (0.0 * sign) / 0.0;
    }
    free(tmp);
  }
  while (isdigit(*str))
    ret = (ret * 10.0) + (*str++ - '0');
  if (*str == '.') {
    ++str;
    uint32_t fracLen = 0;
    while (isdigit(*str)) {
      ++str;
      ++fracLen;
    }
    str -= fracLen;
    double frac = 0.0;
    for (uint32_t i = 0; i != fracLen; ++i)
      frac = (frac * 10.0) + (*str++ - '0');
    if (frac != 0.0) {
      while (fracLen--)
        frac /= 10.0;
      ret += frac;
    }
  }
  if (tolower(*str) == 'e') {
    ++str;
    int32_t exp_sign = 1;
    if (*str == '-') {
      exp_sign = -1;
      ++str;
    } else if (*str == '+')
      ++str;
    int32_t exp = 0;
    while (isdigit(*str))
      exp = (exp * 10) + (*str++ - '0');
    if (exp_sign == 1) {
      while (exp--)
        ret *= 10.0;
    } else {
      while (exp--)
        ret /= 10.0;
    }
  }
  if (endptr)
    *endptr = (char*)str;
  return ret * sign;
}
__attribute__((visibility("default")))
float strtof(const char* str, char** endptr) {
  float ret = 0.0f;
  int32_t sign = 1;
  while (isblank(*str))
    ++str;
  if (*str == '-') {
    sign = -1;
    ++str;
  } else if (*str == '+')
    ++str;
  if (tolower(*str) == 'i') {
    char* tmp = strndup(str, 3);
    for (int32_t i = 0; tmp[i]; ++i)
      tmp[i] = tolower(tmp[i]);
    if (strncmp(tmp, "inf", 3) == 0) {
      free(tmp);
      return (1.0f * sign) / 0.0f;
    }
    free(tmp);
  } else if (tolower(*str) == 'n') {
    char* tmp = strndup(str, 3);
    for (int32_t i = 0; tmp[i]; ++i)
      tmp[i] = tolower(tmp[i]);
    if (strncmp(tmp, "nan", 3) == 0) {
      free(tmp);
      return (0.0f * sign) / 0.0f;
    }
    free(tmp);
  }
  while (isdigit(*str))
    ret = (ret * 10.0f) + (*str++ - '0');
  if (*str == '.') {
    ++str;
    uint32_t fracLen = 0;
    while (isdigit(*str)) {
      ++str;
      ++fracLen;
    }
    str -= fracLen;
    float frac = 0.0f;
    for (uint32_t i = 0; i != fracLen; ++i)
      frac = (frac * 10.0f) + (*str++ - '0');
    if (frac != 0.0f) {
      while (fracLen--)
        frac /= 10.0f;
      ret += frac;
    }
  }
  if (tolower(*str) == 'e') {
    ++str;
    int32_t exp_sign = 1;
    if (*str == '-') {
      exp_sign = -1;
      ++str;
    } else if (*str == '+')
      ++str;
    int32_t exp = 0;
    while (isdigit(*str))
      exp = (exp * 10) + (*str++ - '0');
    if (exp_sign == 1) {
      while (exp--)
        ret *= 10.0f;
    } else {
      while (exp--)
        ret /= 10.0f;
    }
  }
  if (endptr)
    *endptr = (char*)str;
  return ret * sign;
}
__attribute__((visibility("default")))
long strtol(const char* str, char** endptr, int32_t base) {
  int32_t ret = 0;
  int32_t sign = 1;
  while (isblank(*str))
    ++str;
  if (*str == '-') {
    sign = -1;
    ++str;
  } else if (*str == '+')
    ++str;
  if (base == 0) {
    if (*str == '0') {
      ++str;
      if (tolower(*str) == 'x') {
        base = 16;
        ++str;
      } else base = 8;
    } else base = 10;
  } else if (base == 8) {
    if (*str == '0')
      ++str;
  } else if (base == 16) {
    if (*str == '0') {
      ++str;
      if (tolower(*str) == 'x')
        ++str;
    }
  }
  while (*str == '0')
    ++str;
  while (*str) {
    int32_t digit;
    if (*str >= '0' && *str <= '0' + base - 1)
      digit = *str - '0';
    else if (base > 10) {
      char lowc = tolower(*str);
      if (lowc >= 'a' && lowc <= 'a' + base - 11)
        digit = lowc - 'a' + 10;
      else break;
    } else break;
    ret = (ret * base) + digit;
    ++str;
  }
  if (endptr)
    *endptr = (char*)str;
  return ret * sign;
}
__attribute__((visibility("default")))
long long strtoll(const char* str, char** endptr, int32_t base) {
  int64_t ret = 0;
  int32_t sign = 1;
  while (isblank(*str))
    ++str;
  if (*str == '-') {
    sign = -1;
    ++str;
  } else if (*str == '+')
    ++str;
  if (base == 0) {
    if (*str == '0') {
      ++str;
      if (tolower(*str) == 'x') {
        base = 16;
        ++str;
      } else base = 8;
    } else base = 10;
  } else if (base == 8) {
    if (*str == '0')
      ++str;
  } else if (base == 16) {
    if (*str == '0') {
      ++str;
      if (tolower(*str) == 'x')
        ++str;
    }
  }
  while (*str == '0')
    ++str;
  while (*str) {
    int32_t digit;
    if (*str >= '0' && *str <= '0' + base - 1)
      digit = *str - '0';
    else if (base > 10) {
      char lowc = tolower(*str);
      if (lowc >= 'a' && lowc <= 'a' + base - 11)
        digit = lowc - 'a' + 10;
      else break;
    } else break;
    ret = (ret * base) + digit;
    ++str;
  }
  if (endptr)
    *endptr = (char*)str;
  return ret * sign;
}
__attribute__((visibility("default")))
unsigned long strtoul(const char* str, char** endptr, int32_t base) {
  uint32_t ret = 0;
  int32_t sign = 1;
  while (isblank(*str))
    ++str;
  if (*str == '-') {
    sign = -1;
    ++str;
  } else if (*str == '+')
    ++str;
  if (base == 0) {
    if (*str == '0') {
      ++str;
      if (tolower(*str) == 'x') {
        base = 16;
        ++str;
      } else base = 8;
    } else base = 10;
  } else if (base == 8) {
    if (*str == '0')
      ++str;
  } else if (base == 16) {
    if (*str == '0') {
      ++str;
      if (tolower(*str) == 'x')
        ++str;
    }
  }
  while (*str == '0')
    ++str;
  while (*str) {
    int32_t digit;
    if (*str >= '0' && *str <= '0' + base - 1)
      digit = *str - '0';
    else if (base > 10) {
      char lowc = tolower(*str);
      if (lowc >= 'a' && lowc <= 'a' + base - 11)
        digit = lowc - 'a' + 10;
      else break;
    } else break;
    ret = (ret * base) + digit;
    ++str;
  }
  if (endptr)
    *endptr = (char*)str;
  return ret * sign;
}
__attribute__((visibility("default")))
unsigned long long strtoull(const char* str, char** endptr, int32_t base) {
  uint64_t ret = 0;
  int32_t sign = 1;
  while (isblank(*str))
    ++str;
  if (*str == '-') {
    sign = -1;
    ++str;
  } else if (*str == '+')
    ++str;
  if (base == 0) {
    if (*str == '0') {
      ++str;
      if (tolower(*str) == 'x') {
        base = 16;
        ++str;
      } else base = 8;
    } else base = 10;
  } else if (base == 8) {
    if (*str == '0')
      ++str;
  } else if (base == 16) {
    if (*str == '0') {
      ++str;
      if (tolower(*str) == 'x')
        ++str;
    }
  }
  while (*str == '0')
    ++str;
  while (*str) {
    int32_t digit;
    if (*str >= '0' && *str <= '0' + base - 1)
      digit = *str - '0';
    else if (base > 10) {
      char lowc = tolower(*str);
      if (lowc >= 'a' && lowc <= 'a' + base - 11)
        digit = lowc - 'a' + 10;
      else break;
    } else break;
    ret = (ret * base) + digit;
    ++str;
  }
  if (endptr)
    *endptr = (char*)str;
  return ret * sign;
}
__attribute__((visibility("default")))
int strverscmp(const char* s1, const char* s2) {
  while (1) {
    char c1 = *s1++;
    char c2 = *s2++;
    if (c1 != c2) {
      if (c1 == '\0' || c2 == '\0')
        return c1 - c2;
      if (isdigit(c1) &&
          isdigit(c2)) {
        int32_t i1 = c1 - '0';
        int32_t i2 = c2 - '0';
        while (isdigit(*s1))
          i1 = (i1 * 10) + (*s1++ - '0');
        while (isdigit(*s2))
          i2 = (i2 * 10) + (*s2++ - '0');
        if (i1 != i2)
          return i1 - i2;
      } else return c1 - c2;
    } else if (c1 == '\0')
      break;
  }
  return 0;
}