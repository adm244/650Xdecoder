#include <stdio.h>

#define internal static
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int uint;

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
  
  size_t i = 0;
  size_t size = (sizeof(buffer) / sizeof(buffer[0]));
  while (i < size) {
    u8 opcode = buffer[i];
    u16 operand = 0;
    
    printf("%04X: %02X ", i, opcode);
    
    switch (opcode) {
      case OPCODE(ADC, IMMEDIATE): {
        operand = buffer[i + 1];
        printf("%02X\tADC #%02Xh", operand, operand);
        i += 2;
      } break;
      
      case OPCODE(ADC, ZEROPAGE): {
        operand = buffer[i + 1];
        printf("%02X\tADC %02Xh", operand, operand);
        i += 2;
      } break;
      
      case OPCODE(ADC, ZEROPAGE_X): {
        operand = buffer[i + 1];
        printf("%02X\tADC %02Xh, X", operand, operand);
        i += 2;
      } break;
      
      case OPCODE(ADC, ABSOLUTE): {
        u8 bl = buffer[i + 1];
        u8 bh = buffer[i + 2];
        operand = (bh << 8) | bl;
        printf("%02X %02X\tADC %0Xh", bl, bh, operand);
        i += 3;
      } break;
      
      case OPCODE(ADC, ABSOLUTE_X): {
        u8 bl = buffer[i + 1];
        u8 bh = buffer[i + 2];
        operand = (bh << 8) | bl;
        printf("%02X %02X\tADC %0Xh, X", bl, bh, operand);
        i += 3;
      } break;
      
      case OPCODE(ADC, ABSOLUTE_Y): {
        u8 bl = buffer[i + 1];
        u8 bh = buffer[i + 2];
        operand = (bh << 8) | bl;
        printf("%02X %02X\tADC %0Xh, Y", bl, bh, operand);
        i += 3;
      } break;
      
      case OPCODE(ADC, INDIRECT_X): {
        operand = buffer[i + 1];
        printf("%02X\tADC (%02Xh, X)", operand, operand);
        i += 2;
      } break;
      
      case OPCODE(ADC, INDIRECT_Y): {
        operand = buffer[i + 1];
        printf("%02X\tADC (%02Xh), Y", operand, operand);
        i += 2;
      } break;
      
      default: {
        printf("\tUNDEFINED", opcode);
        ++i;
      } break;
    }
    
    printf("\n");
  }
  
  return(0);
}
