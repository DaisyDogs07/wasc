#include "malloc.h"
#include "mem.h"
#include <stdbool.h>
#include <stddef.h>

extern uint32_t __heap_base;
extern uint32_t __global_base;
extern uint32_t __data_end;
extern uint32_t __stack_low;
extern uint32_t __stack_high;

struct block {
  uint32_t size;
  struct block* next;
  char data[];
};

struct block* head = NULL;

#define USER_DATA_START(blk) ((uint32_t)(blk) + offsetof(struct block, data))
#define USER_DATA_END(blk) (USER_DATA_START(blk) + (blk)->size)
#define REMOVE_BLOCK_META(blk) ((uint32_t)(blk) - offsetof(struct block, data))
#define MEMORY_SIZE (__builtin_wasm_memory_size(0) * (64 * 1024))
#define VALID_ADDR(addr, n) (((uint32_t)(addr) + ((n) - 1)) < MEMORY_SIZE)

void validateAccess(void* addr, uint32_t size) {
  if ((addr >= (void*)&__global_base && addr + size <= (void*)&__data_end) ||
      (addr >= (void*)&__stack_low && addr + size <= (void*)&__stack_high))
    return;
  struct block* current = head;
  while (current) {
    if ((uint32_t)addr >= USER_DATA_START(current) && (uint32_t)addr + size <= USER_DATA_END(current))
      return;
    current = current->next;
  }
  __builtin_trap();
}

__attribute__((visibility("default")))
int8_t readInt8(void* addr) {
  validateAccess(addr, sizeof(int8_t));
  return *(int8_t*)addr;
}
__attribute__((visibility("default")))
uint8_t readUint8(void* addr) {
  validateAccess(addr, sizeof(uint8_t));
  return *(uint8_t*)addr;
}
__attribute__((visibility("default")))
int16_t readInt16(void* addr) {
  validateAccess(addr, sizeof(int16_t));
  return *(int16_t*)addr;
}
__attribute__((visibility("default")))
uint16_t readUint16(void* addr) {
  validateAccess(addr, sizeof(uint16_t));
  return *(uint16_t*)addr;
}
__attribute__((visibility("default")))
int32_t readInt32(void* addr) {
  validateAccess(addr, sizeof(int32_t));
  return *(int32_t*)addr;
}
__attribute__((visibility("default")))
uint32_t readUint32(void* addr) {
  validateAccess(addr, sizeof(uint32_t));
  return *(uint32_t*)addr;
}
__attribute__((visibility("default")))
int64_t readInt64(void* addr) {
  validateAccess(addr, sizeof(int64_t));
  return *(int64_t*)addr;
}
__attribute__((visibility("default")))
uint64_t readUint64(void* addr) {
  validateAccess(addr, sizeof(uint64_t));
  return *(uint64_t*)addr;
}
__attribute__((visibility("default")))
float readFloat(void* addr) {
  validateAccess(addr, sizeof(float));
  return *(float*)addr;
}
__attribute__((visibility("default")))
double readDouble(void* addr) {
  validateAccess(addr, sizeof(double));
  return *(double*)addr;
}

__attribute__((visibility("default")))
int8_t writeInt8(void* addr, int8_t value) {
  validateAccess(addr, sizeof(int8_t));
  return *(int8_t*)addr = value;
}
__attribute__((visibility("default")))
uint8_t writeUint8(void* addr, uint8_t value) {
  validateAccess(addr, sizeof(uint8_t));
  return *(uint8_t*)addr = value;
}
__attribute__((visibility("default")))
int16_t writeInt16(void* addr, int16_t value) {
  validateAccess(addr, sizeof(int16_t));
  return *(int16_t*)addr = value;
}
__attribute__((visibility("default")))
uint16_t writeUint16(void* addr, uint16_t value) {
  validateAccess(addr, sizeof(uint16_t));
  return *(uint16_t*)addr = value;
}
__attribute__((visibility("default")))
int32_t writeInt32(void* addr, int32_t value) {
  validateAccess(addr, sizeof(int32_t));
  return *(int32_t*)addr = value;
}
__attribute__((visibility("default")))
uint32_t writeUint32(void* addr, uint32_t value) {
  validateAccess(addr, sizeof(uint32_t));
  return *(uint32_t*)addr = value;
}
__attribute__((visibility("default")))
int64_t writeInt64(void* addr, int64_t value) {
  validateAccess(addr, sizeof(int64_t));
  return *(int64_t*)addr = value;
}
__attribute__((visibility("default")))
uint64_t writeUint64(void* addr, uint64_t value) {
  validateAccess(addr, sizeof(uint64_t));
  return *(uint64_t*)addr = value;
}
__attribute__((visibility("default")))
float writeFloat(void* addr, float value) {
  validateAccess(addr, sizeof(float));
  return *(float*)addr = value;
}
__attribute__((visibility("default")))
double writeDouble(void* addr, double value) {
  validateAccess(addr, sizeof(double));
  return *(double*)addr = value;
}

__attribute__((visibility("default")))
void* malloc(uint32_t size) {
  if (size == 0)
    return NULL;
  struct block* current = head;
  if (!current) {
    struct block* newBlock = (struct block*)&__heap_base;
    {
      uint32_t res;
      if (__builtin_add_overflow(offsetof(struct block, data), size, &res) ||
          !VALID_ADDR(newBlock, res))
        return NULL;
    }
    newBlock->size = size;
    newBlock->next = NULL;
    head = newBlock;
    return (void*)USER_DATA_START(head);
  }
  uint32_t bestSize = UINT32_MAX;
  struct block* bestBlock = NULL;
  bool isBestBeforeHead = false;
  if (current > (struct block*)&__heap_base) {
    uint32_t freeSpace = (uint32_t)current - USER_DATA_START(&__heap_base);
    if (freeSpace >= size) {
      bestSize = freeSpace;
      isBestBeforeHead = true;
    }
  }
  while (current) {
    struct block* nextBlock = current->next;
    uint32_t freeSpace;
    if (nextBlock)
      freeSpace = (uint32_t)nextBlock - USER_DATA_END(current);
    else freeSpace = MEMORY_SIZE - USER_DATA_END(current);
    if (freeSpace < offsetof(struct block, data)) {
      current = nextBlock;
      continue;
    }
    freeSpace = REMOVE_BLOCK_META(freeSpace);
    if (freeSpace >= size && freeSpace < bestSize) {
      bestSize = freeSpace;
      bestBlock = current;
      if (isBestBeforeHead)
        isBestBeforeHead = false;
      if (freeSpace == size)
        break;
    }
    current = nextBlock;
  }
  if (!bestBlock)
    return NULL;
  if (isBestBeforeHead) {
    struct block* newBlock = (struct block*)&__heap_base;
    if (!VALID_ADDR(newBlock, offsetof(struct block, data) + size))
      return NULL;
    newBlock->size = size;
    newBlock->next = head;
    head = newBlock;
    return (void*)USER_DATA_START(newBlock);
  }
  struct block* newBlock = (struct block*)USER_DATA_END(bestBlock);
  if (!VALID_ADDR(newBlock, offsetof(struct block, data) + size))
    return NULL;
  newBlock->size = size;
  newBlock->next = bestBlock->next;
  bestBlock->next = newBlock;
  return (void*)USER_DATA_START(newBlock);
}

__attribute__((visibility("default")))
void* calloc(uint32_t size, uint32_t nmemb) {
  uint32_t res = 0;
  if (__builtin_mul_overflow(nmemb, size, &res))
    return NULL;
  void* ptr = malloc(res);
  if (!ptr)
    return NULL;
  memset(ptr, '\0', res);
  return ptr;
}

__attribute__((visibility("default")))
void free(void* ptr) {
  struct block* prev = NULL;
  struct block* current = head;
  struct block* next = NULL;
  while (current) {
    next = current->next;
    if ((void*)USER_DATA_START(current) == ptr)
      break;
    prev = current;
    current = next;
  }
  if (!current)
    return;
  if (!prev)
    head = next;
  else prev->next = next;
  return;
}

__attribute__((visibility("default")))
void* realloc(void* ptr, uint32_t size) {
  if (size == 0) {
    if (ptr != NULL)
      free(ptr);
    return NULL;
  } else if (ptr == NULL)
    return malloc(size);
  struct block* current = head;
  while (current) {
    if ((void*)USER_DATA_START(current) == ptr)
      break;
    current = current->next;
  }
  if (!current)
    return NULL;
  if (current->size == size)
    return (void*)USER_DATA_START(current);
  {
    struct block* next = current->next;
    uint32_t freeSpace;
    if (next)
      freeSpace = (uint32_t)next - USER_DATA_START(current);
    else freeSpace = MEMORY_SIZE - USER_DATA_START(current);
    if (freeSpace >= size) {
      if (!VALID_ADDR(current, offsetof(struct block, data) + size))
        return NULL;
      current->size = size;
      return (void*)USER_DATA_START(current);
    }
  }
  void* newPtr = malloc(size);
  if (!newPtr)
    return NULL;
  memcpy(newPtr, ptr, current->size);
  free(ptr);
  return newPtr;
}