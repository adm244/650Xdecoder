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
  ADC, // Add memory to accumulator with carry
  AND, // "AND" memory with accumulator
  ASL, // Shift left one bit (memory or accumulator)
  BCC, // Branch on carry clear
  BCS, // Branch on carry set
  BEQ, // Branch on result zero
  BIT, // Test bits in memory with accumulator
  BMI, // Branch on result minus
  BNE, // Branch on result not zero
  BPL, // Branch on result plus
  BRK, // Force break
  BVC, // Branch on overflow clear
  BVS, // Branch on overflow set
  CLC, // Clear carry flag
  CLD, // Clear decimal mode
  CLI, // Clear interrupt disable bit
  CLV, // Clear overflow flag
  CMP, // Compare memory and accumulator
  CPX, // Compare memory and index X
  CPY, // Compare memory and index Y
  DEC, // Decrement memory by one
  DEX, // Decrement index X by one
  DEY, // Decrement index Y by one
  EOR, // "Exclusive-Or" memory with accumulator
  INC, // Increment memory by one
  INX, // Increment index X by one
  INY, // Increment index Y by one
  JMP, // Jump to new location
  JSR, // Jump to new location saving return address
  LDA, // Load accumulator with memory
  LDX, // Load index X with memory
  LDY, // Load index Y with memory
  LSR, // Shift right one bit (memory or accumulator)
  NOP, // No operation
  ORA, // "OR" memory with accumulator
  PHA, // Push accumulator on stack
  PHP, // Push processor status on stack
  PLA, // Pull accumulator from stack
  PLP, // Pull processor status from stack
  ROL, // Rotate one bit left (memory or accumulator)
  ROR, // Rotate one bit right (memory or accumulator)
  RTI, // Return from interrupt
  RTS, // Return from subroutine
  SBC, // Subtract memory from accumulator with borrow
  SEC, // Set carry flag
  SED, // Set decimal mode
  SEI, // Set interrupt disable status
  STA, // Store accumulator in memory
  STX, // Store index X in memory
  STY, // Store index Y in memory
  TAX, // Transfer accumulator to index X
  TAY, // Transfer accumulator to index Y
  TYA, // Transfer index Y to accumulator
  TSX, // Transfer stack pointer to index X
  TXA, // Transfer index X to accumulator
  TXS  // Transfer index X to stack pointer
};

enum addrmode_e {
  ADDRMODE_GARBAGE = 0,
  IMPLIED,     // 1
  ACCUMULATOR, // 1
  IMMEDIATE,   // 2
  RELATIVE,    // 2
  ZEROPAGE,    // 2
  ZEROPAGE_X,  // 2
  ZEROPAGE_Y,  // 2
  ABSOLUTE,    // 3
  ABSOLUTE_X,  // 3
  ABSOLUTE_Y,  // 3
  INDIRECT,    // 3
  INDIRECT_X,  // 2
  INDIRECT_Y   // 2
};

enum opcode_e {
  // ADC
  OPCODE(ADC, IMMEDIATE)  = 0x69,
  OPCODE(ADC, ZEROPAGE)   = 0x65,
  OPCODE(ADC, ZEROPAGE_X) = 0x75,
  OPCODE(ADC, ABSOLUTE)   = 0x6D,
  OPCODE(ADC, ABSOLUTE_X) = 0x7D,
  OPCODE(ADC, ABSOLUTE_Y) = 0x79,
  OPCODE(ADC, INDIRECT_X) = 0x61,
  OPCODE(ADC, INDIRECT_Y) = 0x71,
  // AND
  OPCODE(AND, IMMEDIATE)  = 0x29,
  OPCODE(AND, ZEROPAGE)   = 0x25,
  OPCODE(AND, ZEROPAGE_X) = 0x35,
  OPCODE(AND, ABSOLUTE)   = 0x2D,
  OPCODE(AND, ABSOLUTE_X) = 0x3D,
  OPCODE(AND, ABSOLUTE_Y) = 0x39,
  OPCODE(AND, INDIRECT_X) = 0x21,
  OPCODE(AND, INDIRECT_Y) = 0x31,
  // ASL
  OPCODE(ASL, ACCUMULATOR) = 0x0A,
  OPCODE(ASL, ZEROPAGE)    = 0x06,
  OPCODE(ASL, ZEROPAGE_X)  = 0x16,
  OPCODE(ASL, ABSOLUTE)    = 0x0E,
  OPCODE(ASL, ABSOLUTE_X)  = 0x1E,
  // BCC
  OPCODE(BCC, RELATIVE) = 0x90,
  // BCS
  OPCODE(BCS, RELATIVE) = 0xB0,
  // BEQ
  OPCODE(BEQ, RELATIVE) = 0xF0,
  // BIT
  OPCODE(BIT, ZEROPAGE) = 0x24,
  OPCODE(BIT, ABSOLUTE) = 0x2C,
  // BMI
  OPCODE(BMI, RELATIVE) = 0x30,
  // BNE
  OPCODE(BNE, RELATIVE) = 0xD0,
  // BPL
  OPCODE(BPL, RELATIVE) = 0x10,
  // BRK
  OPCODE(BRK, IMPLIED) = 0x00,
  // BVC
  OPCODE(BVC, RELATIVE) = 0x50,
  // BVS
  OPCODE(BVS, RELATIVE) = 0x70,
  // CLC
  OPCODE(CLC, IMPLIED) = 0x18,
  // CLD
  OPCODE(CLD, IMPLIED) = 0xD8,
  // CLI
  OPCODE(CLI, IMPLIED) = 0x58,
  // CLV
  OPCODE(CLV, IMPLIED) = 0xB8,
  // CMP
  OPCODE(CMP, IMMEDIATE)  = 0xC9,
  OPCODE(CMP, ZEROPAGE)   = 0xC5,
  OPCODE(CMP, ZEROPAGE_X) = 0xD5,
  OPCODE(CMP, ABSOLUTE)   = 0xCD,
  OPCODE(CMP, ABSOLUTE_X) = 0xDD,
  OPCODE(CMP, ABSOLUTE_Y) = 0xD9,
  OPCODE(CMP, INDIRECT_X) = 0xC1,
  OPCODE(CMP, INDIRECT_Y) = 0xD1,
  // CPX
  OPCODE(CPX, IMMEDIATE) = 0xE0,
  OPCODE(CPX, ZEROPAGE)  = 0xE4,
  OPCODE(CPX, ABSOLUTE)  = 0xEC,
  // CPY
  OPCODE(CPY, IMMEDIATE) = 0xC0,
  OPCODE(CPY, ZEROPAGE)  = 0xC4,
  OPCODE(CPY, ABSOLUTE)  = 0xCC,
  // DEC
  OPCODE(DEC, ZEROPAGE)   = 0xC6,
  OPCODE(DEC, ZEROPAGE_X) = 0xD6,
  OPCODE(DEC, ABSOLUTE)   = 0xCE,
  OPCODE(DEC, ABSOLUTE_X) = 0xDE,
  // DEX
  OPCODE(DEX, IMPLIED) = 0xCA,
  // DEY
  OPCODE(DEY, IMPLIED) = 0x88,
  // EOR
  OPCODE(EOR, IMMEDIATE)  = 0x49,
  OPCODE(EOR, ZEROPAGE)   = 0x45,
  OPCODE(EOR, ZEROPAGE_X) = 0x55,
  OPCODE(EOR, ABSOLUTE)   = 0x4D,
  OPCODE(EOR, ABSOLUTE_X) = 0x5D,
  OPCODE(EOR, ABSOLUTE_Y) = 0x59,
  OPCODE(EOR, INDIRECT_X) = 0x41,
  OPCODE(EOR, INDIRECT_Y) = 0x51,
  // INC
  OPCODE(INC, ZEROPAGE)   = 0xE6,
  OPCODE(INC, ZEROPAGE_X) = 0xF6,
  OPCODE(INC, ABSOLUTE)   = 0xEE,
  OPCODE(INC, ABSOLUTE_X) = 0xFE,
  // INX
  OPCODE(INX, IMPLIED) = 0xE8,
  // INY
  OPCODE(INY, IMPLIED) = 0xC8,
  // JMP
  OPCODE(JMP, ABSOLUTE) = 0x4C,
  OPCODE(JMP, INDIRECT) = 0x6C,
  // JSR
  OPCODE(JSR, ABSOLUTE) = 0x20,
  // LDA
  OPCODE(LDA, IMMEDIATE)  = 0xA9,
  OPCODE(LDA, ZEROPAGE)   = 0xA5,
  OPCODE(LDA, ZEROPAGE_X) = 0xB5,
  OPCODE(LDA, ABSOLUTE)   = 0xAD,
  OPCODE(LDA, ABSOLUTE_X) = 0xBD,
  OPCODE(LDA, ABSOLUTE_Y) = 0xB9,
  OPCODE(LDA, INDIRECT_X) = 0xA1,
  OPCODE(LDA, INDIRECT_Y) = 0xB1,
  // LDX
  OPCODE(LDX, IMMEDIATE)  = 0xA2,
  OPCODE(LDX, ZEROPAGE)   = 0xA6,
  OPCODE(LDX, ZEROPAGE_Y) = 0xB6,
  OPCODE(LDX, ABSOLUTE)   = 0xAE,
  OPCODE(LDX, ABSOLUTE_Y) = 0xBE,
  // LDY
  OPCODE(LDY, IMMEDIATE)  = 0xA0,
  OPCODE(LDY, ZEROPAGE)   = 0xA4,
  OPCODE(LDY, ZEROPAGE_X) = 0xB4,
  OPCODE(LDY, ABSOLUTE)   = 0xAC,
  OPCODE(LDY, ABSOLUTE_X) = 0xBC,
  // LSR
  OPCODE(LSR, ACCUMULATOR) = 0x4A,
  OPCODE(LSR, ZEROPAGE)    = 0x46,
  OPCODE(LSR, ZEROPAGE_X)  = 0x56,
  OPCODE(LSR, ABSOLUTE)    = 0x4E,
  OPCODE(LSR, ABSOLUTE_X)  = 0x5E,
  // NOP
  OPCODE(NOP, IMPLIED) = 0xEA,
  // ORA
  OPCODE(ORA, IMMEDIATE)  = 0x09,
  OPCODE(ORA, ZEROPAGE)   = 0x05,
  OPCODE(ORA, ZEROPAGE_X) = 0x15,
  OPCODE(ORA, ABSOLUTE)   = 0x0D,
  OPCODE(ORA, ABSOLUTE_X) = 0x1D,
  OPCODE(ORA, ABSOLUTE_Y) = 0x19,
  OPCODE(ORA, INDIRECT_X) = 0x01,
  OPCODE(ORA, INDIRECT_Y) = 0x11,
  // PHA
  OPCODE(PHA, IMPLIED) = 0x48,
  // PHP
  OPCODE(PHP, IMPLIED) = 0x08,
  // PLA
  OPCODE(PLA, IMPLIED) = 0x68,
  // PLP
  OPCODE(PLP, IMPLIED) = 0x28,
  // ROL
  OPCODE(ROL, ACCUMULATOR) = 0x2A,
  OPCODE(ROL, ZEROPAGE)    = 0x26,
  OPCODE(ROL, ZEROPAGE_X)  = 0x36,
  OPCODE(ROL, ABSOLUTE)    = 0x2E,
  OPCODE(ROL, ABSOLUTE_X)  = 0x3E,
  // ROR
  OPCODE(ROR, ACCUMULATOR) = 0x6A,
  OPCODE(ROR, ZEROPAGE)    = 0x66,
  OPCODE(ROR, ZEROPAGE_X)  = 0x76,
  OPCODE(ROR, ABSOLUTE)    = 0x6E,
  OPCODE(ROR, ABSOLUTE_X)  = 0x7E,
  // RTI
  OPCODE(RTI, IMPLIED) = 0x40,
  // RTS
  OPCODE(RTS, IMPLIED) = 0x60,
  // SBC
  OPCODE(SBC, IMMEDIATE)  = 0xE9,
  OPCODE(SBC, ZEROPAGE)   = 0xE5,
  OPCODE(SBC, ZEROPAGE_X) = 0xF5,
  OPCODE(SBC, ABSOLUTE)   = 0xED,
  OPCODE(SBC, ABSOLUTE_X) = 0xFD,
  OPCODE(SBC, ABSOLUTE_Y) = 0xF9,
  OPCODE(SBC, INDIRECT_X) = 0xE1,
  OPCODE(SBC, INDIRECT_Y) = 0xF1,
  // SEC
  OPCODE(SEC, IMPLIED) = 0x38,
  // SED
  OPCODE(SED, IMPLIED) = 0xF8,
  // SEI
  OPCODE(SEI, IMPLIED) = 0x78,
  // STA
  OPCODE(STA, ZEROPAGE)   = 0x85,
  OPCODE(STA, ZEROPAGE_X) = 0x95,
  OPCODE(STA, ABSOLUTE)   = 0x8D,
  OPCODE(STA, ABSOLUTE_X) = 0x9D,
  OPCODE(STA, ABSOLUTE_Y) = 0x99,
  OPCODE(STA, INDIRECT_X) = 0x81,
  OPCODE(STA, INDIRECT_Y) = 0x91,
  // STX
  OPCODE(STX, ZEROPAGE)   = 0x86,
  OPCODE(STX, ZEROPAGE_Y) = 0x96,
  OPCODE(STX, ABSOLUTE)   = 0x8E,
  // STY
  OPCODE(STY, ZEROPAGE)   = 0x84,
  OPCODE(STY, ZEROPAGE_X) = 0x94,
  OPCODE(STY, ABSOLUTE)   = 0x8C,
  // TAX
  OPCODE(TAX, IMPLIED) = 0xAA,
  // TAY
  OPCODE(TAY, IMPLIED) = 0xA8,
  // TYA
  OPCODE(TYA, IMPLIED) = 0x98,
  // TSX
  OPCODE(TSX, IMPLIED) = 0xBA,
  // TXA
  OPCODE(TXA, IMPLIED) = 0x8A,
  // TXS
  OPCODE(TXS, IMPLIED) = 0x9A,
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
  if (!list) {
    return 0;
  }
  
  list->items = asm650x.data.cur;
  
  return list;
}

internal bool asm650x_list_push(instruction_list_t *list, instruction_t *instruction)
{
  void *p = arena_push(&asm650x.data, instruction, sizeof(instruction_t));
  if (!p) {
    return false;
  }
  
  ++list->length;
  
  return true;
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
    
#define CASE_OPCODE_1(op, mode) case OPCODE(op, mode): {\
  instruction.opname = op;\
  instruction.addrmode = mode;\
  instruction.length = 1;\
  instruction.operand.w = 0;\
} break

#define CASE_OPCODE_2(op, mode) case OPCODE(op, mode): {\
  instruction.opname = op;\
  instruction.addrmode = mode;\
  instruction.length = 2;\
  instruction.operand.w = 0;\
  instruction.operand.b = stream_read_byte(&stream);\
} break

#define CASE_OPCODE_3(op, mode) case OPCODE(op, mode): {\
  instruction.opname = op;\
  instruction.addrmode = mode;\
  instruction.length = 3;\
  instruction.operand.w = stream_read_word(&stream);\
} break
    
    switch (opcode) {
      // ADC
      CASE_OPCODE_2(ADC, IMMEDIATE);
      CASE_OPCODE_2(ADC, ZEROPAGE);
      CASE_OPCODE_2(ADC, ZEROPAGE_X);
      CASE_OPCODE_3(ADC, ABSOLUTE);
      CASE_OPCODE_3(ADC, ABSOLUTE_X);
      CASE_OPCODE_3(ADC, ABSOLUTE_Y);
      CASE_OPCODE_2(ADC, INDIRECT_X);
      CASE_OPCODE_2(ADC, INDIRECT_Y);
      // AND
      CASE_OPCODE_2(AND, IMMEDIATE);
      CASE_OPCODE_2(AND, ZEROPAGE);
      CASE_OPCODE_2(AND, ZEROPAGE_X);
      CASE_OPCODE_3(AND, ABSOLUTE);
      CASE_OPCODE_3(AND, ABSOLUTE_X);
      CASE_OPCODE_3(AND, ABSOLUTE_Y);
      CASE_OPCODE_2(AND, INDIRECT_X);
      CASE_OPCODE_2(AND, INDIRECT_Y);
      // ASL
      CASE_OPCODE_1(ASL, ACCUMULATOR);
      CASE_OPCODE_2(ASL, ZEROPAGE);
      CASE_OPCODE_2(ASL, ZEROPAGE_X);
      CASE_OPCODE_3(ASL, ABSOLUTE);
      CASE_OPCODE_3(ASL, ABSOLUTE_X);
      // BCC
      CASE_OPCODE_2(BCC, RELATIVE);
      // BCS
      CASE_OPCODE_2(BCS, RELATIVE);
      // BEQ
      CASE_OPCODE_2(BEQ, RELATIVE);
      // BIT
      CASE_OPCODE_2(BIT, ZEROPAGE);
      CASE_OPCODE_3(BIT, ABSOLUTE);
      // BMI
      CASE_OPCODE_2(BMI, RELATIVE);
      // BNE
      CASE_OPCODE_2(BNE, RELATIVE);
      // BPL
      CASE_OPCODE_2(BPL, RELATIVE);
      // BRK
      CASE_OPCODE_1(BRK, IMPLIED);
      // BVC
      CASE_OPCODE_2(BVC, RELATIVE);
      // BVS
      CASE_OPCODE_2(BVS, RELATIVE);
      // CLC
      CASE_OPCODE_1(CLC, IMPLIED);
      // CLD
      CASE_OPCODE_1(CLD, IMPLIED);
      // CLI
      CASE_OPCODE_1(CLI, IMPLIED);
      // CLV
      CASE_OPCODE_1(CLV, IMPLIED);
      // CMP
      CASE_OPCODE_2(CMP, IMMEDIATE);
      CASE_OPCODE_2(CMP, ZEROPAGE);
      CASE_OPCODE_2(CMP, ZEROPAGE_X);
      CASE_OPCODE_3(CMP, ABSOLUTE);
      CASE_OPCODE_3(CMP, ABSOLUTE_X);
      CASE_OPCODE_3(CMP, ABSOLUTE_Y);
      CASE_OPCODE_2(CMP, INDIRECT_X);
      CASE_OPCODE_2(CMP, INDIRECT_Y);
      // CPX
      CASE_OPCODE_2(CPX, IMMEDIATE);
      CASE_OPCODE_2(CPX, ZEROPAGE);
      CASE_OPCODE_3(CPX, ABSOLUTE);
      // CPY
      CASE_OPCODE_2(CPY, IMMEDIATE);
      CASE_OPCODE_2(CPY, ZEROPAGE);
      CASE_OPCODE_3(CPY, ABSOLUTE);
      // DEC
      CASE_OPCODE_2(DEC, ZEROPAGE);
      CASE_OPCODE_2(DEC, ZEROPAGE_X);
      CASE_OPCODE_3(DEC, ABSOLUTE);
      CASE_OPCODE_3(DEC, ABSOLUTE_X);
      // DEX
      CASE_OPCODE_1(DEX, IMPLIED);
      // DEY
      CASE_OPCODE_1(DEY, IMPLIED);
      // EOR
      CASE_OPCODE_2(EOR, IMMEDIATE);
      CASE_OPCODE_2(EOR, ZEROPAGE);
      CASE_OPCODE_2(EOR, ZEROPAGE_X);
      CASE_OPCODE_3(EOR, ABSOLUTE);
      CASE_OPCODE_3(EOR, ABSOLUTE_X);
      CASE_OPCODE_3(EOR, ABSOLUTE_Y);
      CASE_OPCODE_2(EOR, INDIRECT_X);
      CASE_OPCODE_2(EOR, INDIRECT_Y);
      // INC
      CASE_OPCODE_2(INC, ZEROPAGE);
      CASE_OPCODE_2(INC, ZEROPAGE_X);
      CASE_OPCODE_3(INC, ABSOLUTE);
      CASE_OPCODE_3(INC, ABSOLUTE_X);
      // INX
      CASE_OPCODE_1(INX, IMPLIED);
      // INY
      CASE_OPCODE_1(INY, IMPLIED);
      // JMP
      CASE_OPCODE_3(JMP, ABSOLUTE);
      CASE_OPCODE_2(JMP, INDIRECT);
      // JSR
      CASE_OPCODE_3(JSR, ABSOLUTE);
      // LDA
      CASE_OPCODE_2(LDA, IMMEDIATE);
      CASE_OPCODE_2(LDA, ZEROPAGE);
      CASE_OPCODE_2(LDA, ZEROPAGE_X);
      CASE_OPCODE_3(LDA, ABSOLUTE);
      CASE_OPCODE_3(LDA, ABSOLUTE_X);
      CASE_OPCODE_3(LDA, ABSOLUTE_Y);
      CASE_OPCODE_2(LDA, INDIRECT_X);
      CASE_OPCODE_2(LDA, INDIRECT_Y);
      // LDX
      CASE_OPCODE_2(LDX, IMMEDIATE);
      CASE_OPCODE_2(LDX, ZEROPAGE);
      CASE_OPCODE_2(LDX, ZEROPAGE_Y);
      CASE_OPCODE_3(LDX, ABSOLUTE);
      CASE_OPCODE_3(LDX, ABSOLUTE_Y);
      // LDY
      CASE_OPCODE_2(LDY, IMMEDIATE);
      CASE_OPCODE_2(LDY, ZEROPAGE);
      CASE_OPCODE_2(LDY, ZEROPAGE_X);
      CASE_OPCODE_3(LDY, ABSOLUTE);
      CASE_OPCODE_3(LDY, ABSOLUTE_X);
      // LSR
      CASE_OPCODE_1(LSR, ACCUMULATOR);
      CASE_OPCODE_2(LSR, ZEROPAGE);
      CASE_OPCODE_2(LSR, ZEROPAGE_X);
      CASE_OPCODE_3(LSR, ABSOLUTE);
      CASE_OPCODE_3(LSR, ABSOLUTE_X);
      // NOP
      CASE_OPCODE_1(NOP, IMPLIED);
      // ORA
      CASE_OPCODE_2(ORA, IMMEDIATE);
      CASE_OPCODE_2(ORA, ZEROPAGE);
      CASE_OPCODE_2(ORA, ZEROPAGE_X);
      CASE_OPCODE_3(ORA, ABSOLUTE);
      CASE_OPCODE_3(ORA, ABSOLUTE_X);
      CASE_OPCODE_3(ORA, ABSOLUTE_Y);
      CASE_OPCODE_2(ORA, INDIRECT_X);
      CASE_OPCODE_2(ORA, INDIRECT_Y);
      // PHA
      CASE_OPCODE_1(PHA, IMPLIED);
      // PHP
      CASE_OPCODE_1(PHP, IMPLIED);
      // PLA
      CASE_OPCODE_1(PLA, IMPLIED);
      // PLP
      CASE_OPCODE_1(PLP, IMPLIED);
      // ROL
      CASE_OPCODE_1(ROL, ACCUMULATOR);
      CASE_OPCODE_2(ROL, ZEROPAGE);
      CASE_OPCODE_2(ROL, ZEROPAGE_X);
      CASE_OPCODE_3(ROL, ABSOLUTE);
      CASE_OPCODE_3(ROL, ABSOLUTE_X);
      // ROR
      CASE_OPCODE_1(ROR, ACCUMULATOR);
      CASE_OPCODE_2(ROR, ZEROPAGE);
      CASE_OPCODE_2(ROR, ZEROPAGE_X);
      CASE_OPCODE_3(ROR, ABSOLUTE);
      CASE_OPCODE_3(ROR, ABSOLUTE_X);
      // RTI
      CASE_OPCODE_1(RTI, IMPLIED);
      // RTS
      CASE_OPCODE_1(RTS, IMPLIED);
      // SBC
      CASE_OPCODE_2(SBC, IMMEDIATE);
      CASE_OPCODE_2(SBC, ZEROPAGE);
      CASE_OPCODE_2(SBC, ZEROPAGE_X);
      CASE_OPCODE_3(SBC, ABSOLUTE);
      CASE_OPCODE_3(SBC, ABSOLUTE_X);
      CASE_OPCODE_3(SBC, ABSOLUTE_Y);
      CASE_OPCODE_2(SBC, INDIRECT_X);
      CASE_OPCODE_2(SBC, INDIRECT_Y);
      // SEC
      CASE_OPCODE_1(SEC, IMPLIED);
      // SED
      CASE_OPCODE_1(SED, IMPLIED);
      // SEI
      CASE_OPCODE_1(SEI, IMPLIED);
      // STA
      CASE_OPCODE_2(STA, ZEROPAGE);
      CASE_OPCODE_2(STA, ZEROPAGE_X);
      CASE_OPCODE_3(STA, ABSOLUTE);
      CASE_OPCODE_3(STA, ABSOLUTE_X);
      CASE_OPCODE_3(STA, ABSOLUTE_Y);
      CASE_OPCODE_2(STA, INDIRECT_X);
      CASE_OPCODE_2(STA, INDIRECT_Y);
      // STX
      CASE_OPCODE_2(STX, ZEROPAGE);
      CASE_OPCODE_2(STX, ZEROPAGE_Y);
      CASE_OPCODE_3(STX, ABSOLUTE);
      // STY
      CASE_OPCODE_2(STY, ZEROPAGE);
      CASE_OPCODE_2(STY, ZEROPAGE_X);
      CASE_OPCODE_3(STY, ABSOLUTE);
      // TAX
      CASE_OPCODE_1(TAX, IMPLIED);
      // TAY
      CASE_OPCODE_1(TAY, IMPLIED);
      // TYA
      CASE_OPCODE_1(TYA, IMPLIED);
      // TSX
      CASE_OPCODE_1(TSX, IMPLIED);
      // TXA
      CASE_OPCODE_1(TXA, IMPLIED);
      // TXS
      CASE_OPCODE_1(TXS, IMPLIED);
      
      default: {
        assert(false);
      } break;
    }
    
#undef CASE_OPCODE_3
#undef CASE_OPCODE_2
#undef CASE_OPCODE_1
    
    if (!asm650x_list_push(list, &instruction)) {
      assert(false);
    }
  }
  
  return list;
}

#endif
