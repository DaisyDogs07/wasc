#include "malloc.h"
#include "math.h"

__attribute__((visibility("default")))
int abs(int x) {
  return __builtin_abs(x);
}
__attribute__((visibility("default")))
long labs(long x) {
  return __builtin_labs(x);
}
__attribute__((visibility("default")))
long long llabs(long long x) {
  return __builtin_llabs(x);
}
__attribute__((visibility("default")))
double fabs(double x) {
  return __builtin_fabs(x);
}
__attribute__((visibility("default")))
float fabsf(float x) {
  return __builtin_fabsf(x);
}
__attribute__((visibility("default")))
double copysign(double x, double y) {
  return __builtin_copysign(x, y);
}
__attribute__((visibility("default")))
float copysignf(float x, float y) {
  return __builtin_copysignf(x, y);
}
__attribute__((visibility("default")))
double fdim(double x, double y) {
  return fmax(x - y, 0.0);
}
__attribute__((visibility("default")))
float fdimf(float x, float y) {
  return fmaxf(x - y, 0.0);
}
__attribute__((visibility("default")))
double floor(double x) {
  return __builtin_floor(x);
}
__attribute__((visibility("default")))
float floorf(float x) {
  return __builtin_floorf(x);
}
__attribute__((visibility("default")))
double ceil(double x) {
  return __builtin_ceil(x);
}
__attribute__((visibility("default")))
float ceilf(float x) {
  return __builtin_ceilf(x);
}
__attribute__((visibility("default")))
double remainder(double x, double y) {
  double n = round(x / y);
  double result = x - (n * y);
  if (fabs(result) == 0.5 &&
      fmod(n, 2.0) != 0.0) {
    if (result < 0.0)
      result += y;
    else result -= y;
  }
  return result;
}
__attribute__((visibility("default")))
float remainderf(float x, float y) {
  float n = roundf(x / y);
  float result = x - (n * y);
  if (fabsf(result) == 0.5f &&
      fmodf(n, 2.0f) != 0.0f) {
    if (result < 0.0f)
      result += y;
    else result -= y;
  }
  return result;
}
__attribute__((visibility("default")))
double round(double x) {
  if (x >= 0.0)
    return floor(x + 0.5);
  return ceil(x - 0.5);
}
__attribute__((visibility("default")))
float roundf(float x) {
  if (x >= 0.0f)
    return floorf(x + 0.5f);
  return ceilf(x - 0.5f);
}
__attribute__((visibility("default")))
long lround(double x) {
  if (x >= 0.0)
    return floor(x + 0.5);
  return ceil(x - 0.5);
}
__attribute__((visibility("default")))
long lroundf(float x) {
  if (x >= 0.0f)
    return floorf(x + 0.5f);
  return ceilf(x - 0.5f);
}
__attribute__((visibility("default")))
long long llround(double x) {
  if (x >= 0.0)
    return floor(x + 0.5);
  return ceil(x - 0.5);
}
__attribute__((visibility("default")))
long long llroundf(float x) {
  if (x >= 0.0f)
    return floorf(x + 0.5f);
  return ceilf(x - 0.5f);
}
__attribute__((visibility("default")))
double trunc(double x) {
  return __builtin_trunc(x);
}
__attribute__((visibility("default")))
float truncf(float x) {
  return __builtin_truncf(x);
}
__attribute__((visibility("default")))
double fma(double x, double y, double z) {
  return (x * y) + z;
}
__attribute__((visibility("default")))
double fmod(double x, double y) {
  return x - (y * floor(x / y));
}
__attribute__((visibility("default")))
float fmodf(float x, float y) {
  return x - (y * floorf(x / y));
}
__attribute__((visibility("default")))
double modf(double x, double* i) {
  double t = trunc(x);
  writeDouble((void*)i, t);
  return x - t;
}
__attribute__((visibility("default")))
float modff(float x, float* i) {
  float t = truncf(x);
  writeFloat((void*)i, t);
  return x - t;
}
__attribute__((visibility("default")))
double frexp(double x, int* exp) {
  writeInt32(exp, 0);
  if (x == 0.0)
    return 0.0;
  if (x < 0.5) {
    do {
      x *= 2.0;
      writeInt32(exp, readInt32(exp) - 1);
    } while (x < 0.5);
  } else if (x >= 1.0) {
    do {
      x /= 2.0;
      writeInt32(exp, readInt32(exp) + 1);
    } while (x >= 1.0);
  }
  return x;
}
__attribute__((visibility("default")))
float frexpf(float x, int* exp) {
  writeInt32(exp, 0);
  if (x == 0.0f)
    return 0.0f;
  if (x < 0.5f) {
    do {
      x *= 2.0f;
      writeInt32(exp, readInt32(exp) - 1);
    } while (x < 0.5f);
  } else if (x >= 1.0f) {
    do {
      x /= 2.0f;
      writeInt32(exp, readInt32(exp) + 1);
    } while (x >= 1.0f);
  }
  return x;
}
__attribute__((visibility("default")))
double fmax(double x, double y) {
  if (x < y)
    return y;
  return x;
}
__attribute__((visibility("default")))
float fmaxf(float x, float y) {
  if (x < y)
    return y;
  return x;
}
__attribute__((visibility("default")))
double fmin(double x, double y) {
  if (x < y)
    return x;
  return y;
}
__attribute__((visibility("default")))
float fminf(float x, float y) {
  if (x < y)
    return x;
  return y;
}
__attribute__((visibility("default")))
bool finite(double x) {
  return __builtin_isfinite(x);
}
__attribute__((visibility("default")))
bool finitef(float x) {
  return __builtin_isfinite(x);
}
__attribute__((visibility("default")))
bool isinf(double x) {
  return __builtin_isinf(x);
}
__attribute__((visibility("default")))
bool isinff(float x) {
  return __builtin_isinf(x);
}
__attribute__((visibility("default")))
bool isnan(double x) {
  return __builtin_isnan(x);
}
__attribute__((visibility("default")))
bool isnanf(float x) {
  return __builtin_isnan(x);
}
__attribute__((visibility("default")))
double nan(const char* str) {
  return 0.0 / 0.0;
}
__attribute__((visibility("default")))
float nanf(const char* str) {
  return 0.0f / 0.0f;
}
__attribute__((visibility("default")))
int signbit(double x) {
  return __builtin_signbit(x);
}
__attribute__((visibility("default")))
int signbitf(float x) {
  return __builtin_signbitf(x);
}
__attribute__((visibility("default")))
double sqrt(double x) {
  return __builtin_sqrt(x);
}
__attribute__((visibility("default")))
float sqrtf(float x) {
  return __builtin_sqrtf(x);
}