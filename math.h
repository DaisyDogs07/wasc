#include <stdbool.h>
#include <stdint.h>

typedef long int time_t;

int abs(int x);
long labs(long x);
long long llabs(long long x);
double fabs(double x);
float fabsf(float x);
double copysign(double x, double y);
float copysignf(float x, float y);
double difftime(time_t time1, time_t time2);
double fdim(double x, double y);
float fdimf(float x, float y);
double floor(double x);
float floorf(float x);
double ceil(double x);
float ceilf(float x);
double remainder(double x, double y);
float remainderf(float x, float y);
double round(double x);
float roundf(float x);
long lround(double x);
long lroundf(float x);
long long llround(double x);
long long llroundf(float x);
double trunc(double x);
float truncf(float x);
double fma(double x, double y, double z);
double fmod(double x, double y);
float fmodf(float x, float y);
double modf(double x, double* i);
float modff(float x, float* i);
double frexp(double x, int* exp);
float frexpf(float x, int* exp);
double fmax(double x, double y);
float fmaxf(float x, float y);
double fmin(double x, double y);
float fminf(float x, float y);
bool finite(double x);
bool finitef(float x);
bool isinf(double x);
bool isinff(float x);
bool isnan(double x);
bool isnanf(float x);
double nan(const char* str);
float nanf(const char* str);
int signbit(double x);
int signbitf(float x);
double sqrt(double x);
float sqrtf(float x);