#ifndef _ASM650X_DECODER_H_
#define _ASM650X_DECODER_H_

/////////////////////////// GLOBAL DATA ////////////////////////////
#ifndef internal
#define internal
#endif

#ifndef assert
#define assert
#endif

#ifndef ASM650X_NOTYPEDEF
typedef unsigned char byte;
typedef unsigned short word;
#endif

typedef struct {
  word offset; // instruction position in a buffer
  byte opname; // operation mnemonic
  byte addrmode; // operation address mode
  byte length;
  byte code[3];
} instruction_t;

typedef struct {
  word count;
  instruction_t *list;
} instruction_list_t;

#ifndef ASM650X_CUSTOMARENA
typedef struct {
  void *base;
  void *end;
  void *cur;
  size_t count;
} arena_t;
#endif

typedef struct {
  arena_t data;
} asm650x_t;

internal asm650x_t asm650x;

///////////////////////// ARENA FUNCTIONS //////////////////////////
#ifndef ASM650X_CUSTOMARENA
internal void arena_init(arena_t *arena, void *base, size_t size)
{
  assert(arena);
  assert(base);
  assert(size > 0);
  
  arena->base = base;
  arena->end = ((char *)base + size);
  arena->cur = arena->base;
  arena->count = 0;
}

internal void arena_reset(arena_t *arena)
{
  assert(arena);
  
  arena->cur = arena->base;
  arena->count = 0;
}

internal void * arena_push(arena_t *arena, void *data, size_t size)
{
  size_t free_space;
  void *result;
  
  assert(arena);
  assert(data);
  
  if (size == 0) {
    size = strlen((char *)data) + 1;
  }
  
  free_space = ((char *)arena->end - arena->cur);
  if (free_space < size) {
    return 0;
  }
  
  memcpy_s(arena->cur, free_space, data, size);
  
  result = arena->cur;
  arena->cur = (char *)arena->cur + size;
  
  assert((arena->cur >= arena->base) && (arena->cur <= arena->end));
  
  ++arena->count;
  return result;
}
#endif

//////////////////////// PRIVATE FUNCTIONS /////////////////////////


///////////////////////// PUBLIC FUNCTIONS /////////////////////////
internal void asm650x_init(void *storage, size_t size)
{
  assert(storage);
  assert(size > 0);
  
  arena_init(&asm650x.data, storage, size);
}

internal instruction_list_t * asm650x_decode(void *buffer, size_t size)
{
  //stream_t input_stream = {0};
  //stream_init(&input_stream, buffer, sizeof(buffer));
  
  return 0;
}

internal char * asm650x_get_string(instruction_t *instruction)
{
  return 0;
}

#endif
