#include <stdio.h>
#include <assert.h>

/*
  TODO:
    - error handling (expections?)
*/

#define internal static

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned short word;

#define true 1
#define false 0
typedef int bool;

#define OPCODE(opname, addrmode) opname##_##addrmode
#define DEFINE_OPCODE(opname, addrmode, opcode) OPCODE(opname, addrmode) = opcode
#define DEFINE_OPERATION(opname, addrmode, length, cycles) {opname,{OPCODE(opname, addrmode), length, cycles, addrmode}}

#define MAX_ADDR_MODES 16

typedef enum {
  DEFINE_OPCODE(ADC, IMMEDIATE,  0x69),
  DEFINE_OPCODE(ADC, ZEROPAGE,   0x65),
  DEFINE_OPCODE(ADC, ZEROPAGE_X, 0x75),
  DEFINE_OPCODE(ADC, ABSOLUTE,   0x6D),
  DEFINE_OPCODE(ADC, ABSOLUTE_X, 0x7D),
  DEFINE_OPCODE(ADC, ABSOLUTE_Y, 0x79),
  DEFINE_OPCODE(ADC, INDIRECT_X, 0x61),
  DEFINE_OPCODE(ADC, INDIRECT_Y, 0x71)
} opcodes;

typedef enum {
  ADC
} opname;

typedef enum {
  IMMEDIATE,
  ZEROPAGE,
  ZEROPAGE_X,
  ABSOLUTE,
  ABSOLUTE_X,
  ABSOLUTE_Y,
  INDIRECT_X,
  INDIRECT_Y
} opaddrmode;

typedef struct {
  opcodes opcode;
  opaddrmode addrmode;
  uint length;
  uint cycles;
} instruction_t;

typedef struct {
  opname name;
  instruction_t instructions[MAX_ADDR_MODES];
} operation_t;

internal const operation_t g_Operations[] = {
  DEFINE_OPERATION(ADC, IMMEDIATE,  2, 2),
  DEFINE_OPERATION(ADC, ZEROPAGE,   2, 3),
  DEFINE_OPERATION(ADC, ZEROPAGE_X, 2, 4),
  DEFINE_OPERATION(ADC, ABSOLUTE,   3, 4),
  DEFINE_OPERATION(ADC, ABSOLUTE_X, 3, 4),
  DEFINE_OPERATION(ADC, ABSOLUTE_Y, 3, 4),
  DEFINE_OPERATION(ADC, INDIRECT_X, 2, 6),
  DEFINE_OPERATION(ADC, INDIRECT_Y, 2, 5),
};

#define arraysize(a) (sizeof(a) / sizeof(a[0]))

typedef struct {
  void *p;
  size_t size;
} buffer_t;

typedef struct {
  buffer_t buffer;
  size_t pos;
} stream_t;

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

#define BL(a) ((byte)a)
#define BH(a) ((byte)(a >> 8))

int main(int argc, char *argv[])
{
  u8 buffer[] = {
    0x69, 0x05, // ADC #05h
    0x65, 0x20, // ADC 20h
    0x75, 0x15, // ADC 15h, X
    0x6D, 0xFE, 0xCA, // ADC CAFEh
    0x7D, 0xFE, 0xCA, // ADC CAFEh, X
    0x79, 0xFE, 0xCA, // ADC CAFEh, Y
    0x61, 0xAB, // ADC (ABh, X)
    0x71, 0xAB, // ADC (ABh), Y
    0xFF,
  };
  
  /* printf result:
    0000: 69 05     ADC #05h
    0002: 65 20     ADC 20h
    0004: 75 15     ADC 15h, X
    0006: 6D FE CA  ADC CAFEh
    0009: 7D FE CA  ADC CAFEh, X
    000C: 79 FE CA  ADC CAFEh, Y
    000F: 61 AB     ADC (ABh, X)
    0011: 71 AB     ADC (ABh), Y
    0013: FF        UNDEFINED
  */
  
  stream_t input_stream = {0};
  stream_init(&input_stream, buffer, arraysize(buffer));
  
  while (!stream_eof(&input_stream)) {
    byte opcode = stream_read_byte(&input_stream);
    word operand = 0;
    
    printf("%04X: %02X ", (input_stream.pos - 1), opcode);
    
    switch (opcode) {
      case OPCODE(ADC, IMMEDIATE): {
        operand = stream_read_byte(&input_stream);
        printf("%02X\tADC #%02Xh", operand, operand);
      } break;
      
      case OPCODE(ADC, ZEROPAGE): {
        operand = stream_read_byte(&input_stream);
        printf("%02X\tADC %02Xh", operand, operand);
      } break;
      
      case OPCODE(ADC, ZEROPAGE_X): {
        operand = stream_read_byte(&input_stream);
        printf("%02X\tADC %02Xh, X", operand, operand);
      } break;
      
      case OPCODE(ADC, ABSOLUTE): {
        operand = stream_read_word(&input_stream);
        printf("%02X %02X\tADC %0Xh", BL(operand), BH(operand), operand);
      } break;
      
      case OPCODE(ADC, ABSOLUTE_X): {
        operand = stream_read_word(&input_stream);
        printf("%02X %02X\tADC %0Xh, X", BL(operand), BH(operand), operand);
      } break;
      
      case OPCODE(ADC, ABSOLUTE_Y): {
        operand = stream_read_word(&input_stream);
        printf("%02X %02X\tADC %0Xh, Y", BL(operand), BH(operand), operand);
      } break;
      
      case OPCODE(ADC, INDIRECT_X): {
        operand = stream_read_byte(&input_stream);
        printf("%02X\tADC (%02Xh, X)", operand, operand);
      } break;
      
      case OPCODE(ADC, INDIRECT_Y): {
        operand = stream_read_byte(&input_stream);
        printf("%02X\tADC (%02Xh), Y", operand, operand);
      } break;
      
      default: {
        printf("\tUNDEFINED", opcode);
      } break;
    }
    
    printf("\n");
  }
  
  return(0);
}
