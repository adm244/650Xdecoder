#ifndef _ASM650X_DECODER_H_
#define _ASM650X_DECODER_H_

#ifndef internal
#define internal
#endif

#ifndef assert
#define assert
#endif

#ifndef ASM650X_NOTYPEDEF
#define true 1
#define false 0
typedef char bool;

typedef unsigned char byte;
typedef unsigned short word;
#endif

////////////////////////// INSTRUCTIONS ////////////////////////////
#define OPCODE(opname, addrmode) opname##_##addrmode

enum opname_e {
  OPNAME_GARBAGE = 0,
  JSR,
};

enum addrmode_e {
  ADDRMODE_GARBAGE = 0,
  ABSOLUTE,
};

enum opcode_e {
  OPCODE(JSR, ABSOLUTE) = 0x20,
};

/////////////////////////// GLOBAL DATA ////////////////////////////
//NOTE(adm244): assuming that cpu and data are little-endian
typedef union {
  byte b;
  word w;
} operand_t;

typedef struct {
  word offset; // instruction position in a buffer
  byte opname; // operation mnemonic
  byte addrmode; // operation address mode
  byte length;

//NOTE(adm244): we need this pragma here to make sure that compiler won't add any
// padding that can prevent us from properly accessing data through 'code' array
#pragma pack(push, 1)
  union {
    struct {
      byte opcode;
      operand_t operand;
    };
    byte code[3];
  };
#pragma pack(pop)
} instruction_t;

typedef struct {
  word length;
  instruction_t *items;
} instruction_list_t;

#ifndef ASM650X_CUSTOMARENA
typedef struct {
  void *base;
  void *end;
  void *cur;
  size_t count;
} arena_t;
#endif

#ifndef ASM650X_CUSTOMSTREAM
typedef struct {
  void *p;
  size_t size;
} buffer_t;

typedef struct {
  buffer_t buffer;
  size_t pos;
} stream_t;
#endif

typedef struct {
  arena_t data;
} asm650x_t;

internal asm650x_t asm650x;

//////////////////////// STREAM FUNCTIONS //////////////////////////
#ifndef ASM650X_CUSTOMSTREAM
internal void stream_init(stream_t *stream, void *buffer, size_t size)
{
  assert(stream);
  assert(buffer);
  
  stream->buffer.p = buffer;
  stream->buffer.size = size;
  stream->pos = 0;
}

internal bool stream_eof(stream_t *stream)
{
  assert(stream);
  assert(stream->buffer.p);
  
  return (stream->pos >= stream->buffer.size);
}

internal byte stream_read_byte(stream_t *stream)
{
  assert(stream);
  assert(stream->buffer.p);
  
  //TODO(adm244): error handling
  {
    byte *p = (byte *)stream->buffer.p;
    return p[stream->pos++];
  }
}

internal word stream_read_word(stream_t *stream)
{
  assert(stream);
  assert(stream->buffer.p);
  
  //TODO(adm244): error handling
  {
    byte bl = stream_read_byte(stream);
    byte bh = stream_read_byte(stream);
    
    return (word)((bh << 8) | bl);
  }
}
#endif

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
internal instruction_list_t * asm650x_list_create()
{
  instruction_list_t buffer = {0};
  instruction_list_t *list;
  
  list = arena_push(&asm650x.data, &buffer, sizeof(buffer));
  list->items = asm650x.data.cur;
  
  return list;
}

internal bool asm650x_list_push(instruction_list_t *list, instruction_t *instruction)
{
  arena_push(&asm650x.data, instruction, sizeof(instruction_t));
  ++list->length;
  
  return true;
}

internal byte asm650x_get_length(enum addrmode_e addrmode)
{
  switch (addrmode) {
    case ABSOLUTE:
      return 3;
    
    default: {
      assert(false);
      return 0;
    }
  }
}

///////////////////////// PUBLIC FUNCTIONS /////////////////////////
internal void asm650x_init(void *storage, size_t size)
{
  assert(storage);
  assert(size > 0);
  
  arena_init(&asm650x.data, storage, size);
}

internal instruction_list_t * asm650x_decode(void *buffer, size_t size)
{
  stream_t stream = {0};
  instruction_list_t *list;
  
  assert(buffer);
  assert(size > 0);
  
  arena_reset(&asm650x.data);
  list = asm650x_list_create();
  
  stream_init(&stream, buffer, size);
  
  while (!stream_eof(&stream)) {
    instruction_t instruction = {0};
    size_t address = stream.pos;
    byte opcode = stream_read_byte(&stream);
    
    instruction.offset = address;
    instruction.opcode = opcode;
    
    switch (opcode) {
      //TODO(adm244): make a macro for this
      case OPCODE(JSR, ABSOLUTE): {
        instruction.opname = JSR;
        instruction.addrmode = ABSOLUTE;
        instruction.length = asm650x_get_length(ABSOLUTE);
        instruction.operand.w = stream_read_word(&stream);
      } break;
      
      default: {
        assert(false);
      } break;
    }
    
    asm650x_list_push(list, &instruction);
  }
  
  return list;
}

//FIX(adm244): proper name
internal char * asm650x_get_string(char *buffer, size_t size, instruction_t *instruction)
{
  switch (instruction->opname) {
    case JSR: {
      sprintf_s(buffer, size, "JSR");
      switch (instruction->addrmode) {
        case ABSOLUTE: {
          sprintf_s(buffer, size, "%s $%04X", buffer, instruction->operand.w);
        } break;
        
        default:
          assert(false);
          break;
      }
    } break;
    
    default:
      assert(false);
      sprintf_s(buffer, size, "UNDEFINED");
      break;
  }
  
  return buffer;
}

#endif
