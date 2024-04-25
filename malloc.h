#include <stdint.h>

void validateAccess(void* addr, uint32_t size);
int8_t readInt8(void* addr);
uint8_t readUint8(void* addr);
int16_t readInt16(void* addr);
uint16_t readUint16(void* addr);
int32_t readInt32(void* addr);
uint32_t readUint32(void* addr);
int64_t readInt64(void* addr);
uint64_t readUint64(void* addr);
double readDouble(void* addr);
float readFloat(void* addr);
int8_t writeInt8(void* addr, int8_t value);
uint8_t writeUint8(void* addr, uint8_t value);
int16_t writeInt16(void* addr, int16_t value);
uint16_t writeUint16(void* addr, uint16_t value);
int32_t writeInt32(void* addr, int32_t value);
uint32_t writeUint32(void* addr, uint32_t value);
int64_t writeInt64(void* addr, int64_t value);
uint64_t writeUint64(void* addr, uint64_t value);
double writeDouble(void* addr, double value);
float writeFloat(void* addr, float value);
void* malloc(uint32_t size);
void* calloc(uint32_t size, uint32_t nmemb);
void free(void* ptr);
void* realloc(void* ptr, uint32_t size);