#include <stdio.h>
#include <stdlib.h>
#include "disasm_stm8.h"

struct _stm8_single stm8_single[] = {
  { "break", 0x8b, 1, ST7_YES },
  { "ccf", 0x8c, 1, ST7_NO },
  { "halt", 0x8e, 10, ST7_YES },
  { "iret", 0x80, 11, ST7_YES },
  { "nop", 0x9d, 1, ST7_YES },
  { "rcf", 0x98, 1, ST7_YES },
  { "ret", 0x81, 4, ST7_YES },
  { "retf", 0x87, 5, ST7_NO },
  { "rim", 0x9a, 1, ST7_YES },
  { "rvf", 0x9c, 1, ST7_YES },
  { "scf", 0x99, 1, ST7_YES },
  { "sim", 0x9b, 1, ST7_YES },
  { "trap", 0x83, 9, ST7_YES },
  { "wfi", 0x8f, 10, ST7_YES },
  { NULL, 0x00, 0, 0 },
};

struct _stm8_x_y stm8_x_y[] = {
  { "clrw", 0x5f, 1, ST7_NO },
  { "cplw", 0x53, 2, ST7_YES },
  { "decw", 0x5a, 1, ST7_NO },
  { "incw", 0x5c, 1, ST7_NO },
  { "negw", 0x50, 2, ST7_NO },
  { "popw", 0x85, 2, ST7_YES },
  { "pushw", 0x89, 2, ST7_YES },
  { "rlcw", 0x59, 2, ST7_YES },
  { "rlwa", 0x02, 1, ST7_NO },
  { "rrcw", 0x56, 2, ST7_YES },
  { "rrwa", 0x01, 1, ST7_NO },
  { "sllw", 0x58, 2, ST7_NO },
  { "slaw", 0x58, 2, ST7_NO },   // Same as sllw
  { "sraw", 0x57, 2, ST7_NO },
  { "srlw", 0x54, 2, ST7_NO },
  { "swapw", 0x5e, 1, ST7_YES },
  { "tnzw", 0x5d, 2, ST7_NO },
  { NULL, 0x00, 0, 0 },
};

/*
SUB    0   // plus SUB SP, #byte
CP     1
SBC    2
AND    4
BCP    5
LD     6
LD     7   // reverse
XOR    8
ADC    9
OR     a
ADD    b
JP     c   // no a, b, 1
CALL   d   // no a and b
*/

//struct _stm8_instr stm8_type1[] = {
char *stm8_type1[] = {
  "sub",   //0   // plus SUB SP, #byte
  "cp",    //1
  "sbc",   //2
  NULL,    //3
  "and",   //4
  "bcp" ,  //5
  "ld",    //6
  "ld",    //7   // reverse
  "xor",   //8
  "adc",   //9
  "or",    //a
  "add",   //b
  "jp",    //c   // no a, b, 1
  "call",  //d   // no a and b
  NULL,    //e
  NULL,    //f
};

/*
NEG   0
CPL   3
SRL   4
RRC   6
SRA   7
SLL   8   (SLA also)
RLC   9
DEC   a
INC   c
TNZ   d
SWAP  e
CLR   f
*/

//struct _stm8_instr stm8_type2[] = {
char *stm8_type2[] = {
  "neg",  // 0
  NULL,   // 1
  NULL,   // 2
  "cpl",  // 3
  "srl",  // 4
  NULL,   // 5
  "rrc",  // 6
  "sra",  // 7
  "sll",  // 8   (SLA also)
  "rlc",  // 9
  "dec",  // a
  NULL,   // b
  "inc",  // c
  "tnz",  // d
  "swap", // e
  "clr",  // f
};

/*
Load and Transfer
LD
LDF
MOV
EXG
LDW
EXGW

Stack operation
PUSH
POP

Compare and Tests
CPW


Bit Operation
BSET
BRES
BCPL
BCCM

Conditional Bit Test and Branch
BTJT
BTJF

Arithmetic operations
MUL
DIV
DIVW
ADDW
SUBW

Unconditional Jump or Call
JRA
JRT
JRF
JPF
CALLR
CALLF

Conditional Branch/ Execution
JRxx
WFE

*/


