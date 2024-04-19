#include "malloc.h"
#include "mem.h"
#include <stdbool.h>
#include <stddef.h>

extern uint32_t __heap_base;

struct block {
  uint32_t size;
  struct block* next;
  char data[];
};

struct block* head = NULL;

#define USER_DATA_START(blk) ((uint32_t)(blk) + offsetof(struct block, data))
#define USER_DATA_END(blk) (USER_DATA_START(blk) + (blk)->size)
#define REMOVE_BLOCK_META(blk) ((uint32_t)(blk) - offsetof(struct block, data))

__attribute__((visibility("default")))
void* malloc(uint32_t size) {
  if (size == 0)
    return NULL;
  struct block* current = head;
  if (!current) {
    struct block* newBlock = (struct block*)&__heap_base;
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
  while (current && bestSize != size) {
    struct block* nextBlock = current->next;
    uint32_t freeSpace;
    if (nextBlock)
      freeSpace = REMOVE_BLOCK_META((uint32_t)nextBlock - USER_DATA_END(current));
    else freeSpace = REMOVE_BLOCK_META(UINT32_MAX - USER_DATA_END(current));
    if (freeSpace >= size && freeSpace < bestSize) {
      bestSize = freeSpace;
      bestBlock = current;
      if (isBestBeforeHead)
        isBestBeforeHead = false;
    }
    current = nextBlock;
  }
  if (isBestBeforeHead) {
    struct block* newBlock = (struct block*)&__heap_base;
    newBlock->size = size;
    newBlock->next = head;
    head = newBlock;
    return (void*)USER_DATA_START(newBlock);
  }
  struct block* newBlock = (struct block*)USER_DATA_END(bestBlock);
  newBlock->size = size;
  newBlock->next = bestBlock->next;
  bestBlock->next = newBlock;
  return (void*)USER_DATA_START(newBlock);
}

__attribute__((visibility("default")))
void* calloc(uint32_t size, uint32_t nmemb) {
  size_t res = 0;
  if (__builtin_mul_overflow(nmemb, size, &res))
    return NULL;
  void* ptr = malloc(res);
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
  }
  if (ptr == NULL)
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
    if (next) {
      uint32_t freeSpace = (uint32_t)next - USER_DATA_START(current);
      if (freeSpace >= size) {
        current->size = size;
        return (void*)USER_DATA_START(current);
      }
    } else {
      current->size = size;
      return (void*)USER_DATA_START(current);
    }
  }
  void* newPtr = malloc(size);
  memcpy(newPtr, ptr, current->size);
  free(ptr);
  return newPtr;
}