# Simple 650x Instruction Set Decoder

A very basic MCS650x microprocessor family instruction set architecture (ISA) decoder.

Instructions are encoded using a one-byte opcode that indicates a type of operation and addressing mode.
They can be of length 1, 2 or 3 bytes depending on addressing mode used.
So we basically have a table of opcodes that we use to decode an instruction.

Based on "[MCS6500 Microcomputer Family Programming Manual (Jan. 1976)](http://archive.6502.org/books/mcs6500_family_programming_manual.pdf)".

### Usage
```c
#include "asm650x.h"
char storage[4096];

// buffer contains sequence of bytes to be decoded
void decode(void *buffer, size_t size)
{
  // initializes fixed-size arena allocator
  asm650x_init(storage, sizeof(storage));
  
  // decodes bytes in buffer into a list of instructions
  // pointer returned is pointing into a memory inside of "storage"
  instruction_list_t *instructions = asm650x_decode(buffer, size);
  assert(instructions);
  
  for (int i = 0; i < instructions->length; ++i) {
    instruction_t *instruction = &instructions->items[i];
    
    word offset = instruction->offset; // position in a buffer
    byte length = instruction->length; // length of instruction, in bytes
    
    byte opname = instruction->opname; // mnemonic, opname_e constant
    byte addrmode = instruction->addrmode; // address mode, addrmode_e constant
    
    // you can use OPCODE(opname, addrmode) macro to "generate" opcode_e constant
    byte opcode = instruction->opcode; // opcode of instruction
    byte b = instruction->operand.b; // byte-size operand
    word w = instruction->operand.w; // word-size operand (MSB is 0 if byte-size operand)
    
    // you can also access each byte of an instruction
    //byte opcode = instruction->code[0];
    //byte lsb = instruction->code[1];
    //byte msb = instruction->code[2];
    
    //...
  }
}
```

## License
This is free and unencumbered software released into the **public domain**.

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
