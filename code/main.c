/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include <assert.h>

#include "asm650x.h"

internal char storage[4096];
internal word code_base_address = 0x600;

char * get_instruction_string(char *buffer, size_t size, instruction_t *instruction);

int main(int argc, char *argv[])
{
  char buffer[] = {
    /* SNAKE6502
       Taken from here (scroll down a bit, click "Assemble" then "Hexdump"):
        http://skilldrick.github.io/easy6502/#snake
    */
    0x20, 0x06, 0x06, 0x20, 0x38, 0x06, 0x20, 0x0D, 0x06, 0x20, 0x2A, 0x06, 0x60, 0xA9, 0x02, 0x85,
    0x02, 0xA9, 0x04, 0x85, 0x03, 0xA9, 0x11, 0x85, 0x10, 0xA9, 0x10, 0x85, 0x12, 0xA9, 0x0F, 0x85,
    0x14, 0xA9, 0x04, 0x85, 0x11, 0x85, 0x13, 0x85, 0x15, 0x60, 0xA5, 0xFE, 0x85, 0x00, 0xA5, 0xFE,
    0x29, 0x03, 0x18, 0x69, 0x02, 0x85, 0x01, 0x60, 0x20, 0x4D, 0x06, 0x20, 0x8D, 0x06, 0x20, 0xC3,
    0x06, 0x20, 0x19, 0x07, 0x20, 0x20, 0x07, 0x20, 0x2D, 0x07, 0x4C, 0x38, 0x06, 0xA5, 0xFF, 0xC9,
    0x77, 0xF0, 0x0D, 0xC9, 0x64, 0xF0, 0x14, 0xC9, 0x73, 0xF0, 0x1B, 0xC9, 0x61, 0xF0, 0x22, 0x60,
    0xA9, 0x04, 0x24, 0x02, 0xD0, 0x26, 0xA9, 0x01, 0x85, 0x02, 0x60, 0xA9, 0x08, 0x24, 0x02, 0xD0,
    0x1B, 0xA9, 0x02, 0x85, 0x02, 0x60, 0xA9, 0x01, 0x24, 0x02, 0xD0, 0x10, 0xA9, 0x04, 0x85, 0x02,
    0x60, 0xA9, 0x02, 0x24, 0x02, 0xD0, 0x05, 0xA9, 0x08, 0x85, 0x02, 0x60, 0x60, 0x20, 0x94, 0x06,
    0x20, 0xA8, 0x06, 0x60, 0xA5, 0x00, 0xC5, 0x10, 0xD0, 0x0D, 0xA5, 0x01, 0xC5, 0x11, 0xD0, 0x07,
    0xE6, 0x03, 0xE6, 0x03, 0x20, 0x2A, 0x06, 0x60, 0xA2, 0x02, 0xB5, 0x10, 0xC5, 0x10, 0xD0, 0x06,
    0xB5, 0x11, 0xC5, 0x11, 0xF0, 0x09, 0xE8, 0xE8, 0xE4, 0x03, 0xF0, 0x06, 0x4C, 0xAA, 0x06, 0x4C,
    0x35, 0x07, 0x60, 0xA6, 0x03, 0xCA, 0x8A, 0xB5, 0x10, 0x95, 0x12, 0xCA, 0x10, 0xF9, 0xA5, 0x02,
    0x4A, 0xB0, 0x09, 0x4A, 0xB0, 0x19, 0x4A, 0xB0, 0x1F, 0x4A, 0xB0, 0x2F, 0xA5, 0x10, 0x38, 0xE9,
    0x20, 0x85, 0x10, 0x90, 0x01, 0x60, 0xC6, 0x11, 0xA9, 0x01, 0xC5, 0x11, 0xF0, 0x28, 0x60, 0xE6,
    0x10, 0xA9, 0x1F, 0x24, 0x10, 0xF0, 0x1F, 0x60, 0xA5, 0x10, 0x18, 0x69, 0x20, 0x85, 0x10, 0xB0,
    0x01, 0x60, 0xE6, 0x11, 0xA9, 0x06, 0xC5, 0x11, 0xF0, 0x0C, 0x60, 0xC6, 0x10, 0xA5, 0x10, 0x29,
    0x1F, 0xC9, 0x1F, 0xF0, 0x01, 0x60, 0x4C, 0x35, 0x07, 0xA0, 0x00, 0xA5, 0xFE, 0x91, 0x00, 0x60,
    0xA6, 0x03, 0xA9, 0x00, 0x81, 0x10, 0xA2, 0x00, 0xA9, 0x01, 0x81, 0x10, 0x60, 0xA2, 0x00, 0xEA,
    0xEA, 0xCA, 0xD0, 0xFB, 0x60, 0x00
  };
  
  printf("sizeof(instruction_t): %d\n", sizeof(instruction_t));
  printf("\n");
  
  asm650x_init(storage, sizeof(storage));
  {
    int i, j;
    instruction_list_t *instructions = asm650x_decode(buffer, sizeof(buffer));
    
    assert(instructions);
    
    for (i = 0; i < instructions->length; ++i) {
      instruction_t *instruction = &instructions->items[i];
      char buffer[100];
      char asm[100] = {0};
      
      sprintf(buffer, "$%04X: ", instruction->offset + code_base_address);
      
      sprintf(buffer, "%s%02X", buffer, instruction->code[0]);
      for (j = 1; j < instruction->length; ++j) {
        sprintf(buffer, "%s %02X", buffer, instruction->code[j]);
      }
      
      get_instruction_string(asm, sizeof(asm), instruction);
      sprintf(buffer, "%s\t%s\n", buffer, asm);
      
      printf(buffer);
    }
  }
  
  return(0);
}

internal bool get_operand_string(char *buffer, size_t size, instruction_t *instruction)
{
  char fmt[64];
  
  switch (instruction->addrmode) {
    case IMPLIED:
      return false;
    
    case ACCUMULATOR: {
      sprintf_s(buffer, size, "A");
      return true;
    }
    
    case IMMEDIATE: {
      strcpy_s(fmt, sizeof(fmt), "#$%02X");
    } break;
    
    case RELATIVE: {
      int next_address = instruction->offset + instruction->length;
      int offset = next_address + (char)instruction->operand.b;
      
      sprintf_s(buffer, size, "$%04X", offset + code_base_address);
      return true;
    }
    
    case ZEROPAGE: {
      strcpy_s(fmt, sizeof(fmt), "$%02X");
    } break;
    
    case ZEROPAGE_X: {
      strcpy_s(fmt, sizeof(fmt), "$%02X, X");
    } break;
    
    case ZEROPAGE_Y: {
      strcpy_s(fmt, sizeof(fmt), "$%02X, Y");
    } break;
    
    case ABSOLUTE: {
      strcpy_s(fmt, sizeof(fmt), "$%04X");
    } break;
    
    case ABSOLUTE_X: {
      strcpy_s(fmt, sizeof(fmt), "$%04X, X");
    } break;
    
    case ABSOLUTE_Y: {
      strcpy_s(fmt, sizeof(fmt), "$%04X, Y");
    } break;
    
    case INDIRECT: {
      strcpy_s(fmt, sizeof(fmt), "($%02X)");
    } break;
    
    case INDIRECT_X: {
      strcpy_s(fmt, sizeof(fmt), "($%02X, X)");
    } break;
    
    case INDIRECT_Y: {
      strcpy_s(fmt, sizeof(fmt), "($%02X), Y");
    } break;
    
    default:
      assert(false);
      return false;
  }
  
  sprintf_s(buffer, size, fmt, instruction->operand.w);
  return true;
}

internal char * get_instruction_string(char *buffer, size_t size, instruction_t *instruction)
{
#define CASE_OPCODE(op) case op: {\
  char buffer_operand[64];\
  if (get_operand_string(buffer_operand, sizeof(buffer_operand), instruction)) {\
    sprintf_s(buffer, size, #op" %s", buffer_operand);\
  } else {\
    sprintf_s(buffer, size, #op);\
  }\
} break

  switch (instruction->opname) {
    CASE_OPCODE(ADC);
    CASE_OPCODE(AND);
    CASE_OPCODE(ASL);
    CASE_OPCODE(BCC);
    CASE_OPCODE(BCS);
    CASE_OPCODE(BEQ);
    CASE_OPCODE(BIT);
    CASE_OPCODE(BMI);
    CASE_OPCODE(BNE);
    CASE_OPCODE(BPL);
    CASE_OPCODE(BRK);
    CASE_OPCODE(BVC);
    CASE_OPCODE(BVS);
    CASE_OPCODE(CLC);
    CASE_OPCODE(CLD);
    CASE_OPCODE(CLI);
    CASE_OPCODE(CLV);
    CASE_OPCODE(CMP);
    CASE_OPCODE(CPX);
    CASE_OPCODE(CPY);
    CASE_OPCODE(DEC);
    CASE_OPCODE(DEX);
    CASE_OPCODE(DEY);
    CASE_OPCODE(EOR);
    CASE_OPCODE(INC);
    CASE_OPCODE(INX);
    CASE_OPCODE(INY);
    CASE_OPCODE(JMP);
    CASE_OPCODE(JSR);
    CASE_OPCODE(LDA);
    CASE_OPCODE(LDX);
    CASE_OPCODE(LDY);
    CASE_OPCODE(LSR);
    CASE_OPCODE(NOP);
    CASE_OPCODE(ORA);
    CASE_OPCODE(PHA);
    CASE_OPCODE(PHP);
    CASE_OPCODE(PLA);
    CASE_OPCODE(PLP);
    CASE_OPCODE(ROL);
    CASE_OPCODE(ROR);
    CASE_OPCODE(RTI);
    CASE_OPCODE(RTS);
    CASE_OPCODE(SBC);
    CASE_OPCODE(SEC);
    CASE_OPCODE(SED);
    CASE_OPCODE(SEI);
    CASE_OPCODE(STA);
    CASE_OPCODE(STX);
    CASE_OPCODE(STY);
    CASE_OPCODE(TAX);
    CASE_OPCODE(TAY);
    CASE_OPCODE(TYA);
    CASE_OPCODE(TSX);
    CASE_OPCODE(TXA);
    CASE_OPCODE(TXS);
    
    default: {
      assert(false);
      sprintf_s(buffer, size, "UNDEFINED");
    } break;
  }
  
#undef CASE_OPCODE
  
  return buffer;
}
