/**
 *  naken_asm assembler.
 *  Author: Michael Kohn
 *   Email: mike@mikekohn.net
 *     Web: http://www.mikekohn.net/
 * License: GPL
 *
 * Copyright 2010-2016 by Michael Kohn
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "disasm/common.h"
#include "disasm/propeller.h"
#include "table/propeller.h"

#define READ_RAM32(a) (memory_read_m(memory, a + 0) << 24) | \
                      (memory_read_m(memory, a + 1) << 16) | \
                      (memory_read_m(memory, a + 2) << 8) | \
                       memory_read_m(memory, a + 3)

int get_cycle_count_propeller(unsigned short int opcode)
{
  return -1;
}

int disasm_propeller(struct _memory *memory, uint32_t address, char *instruction, int *cycles_min, int *cycles_max)
{
  int opcode;
  int n;
  int i,d,s;

  *cycles_min = -1;
  *cycles_max = -1;

  opcode = READ_RAM32(address);

  i = (opcode & 0x00400000) >> 22;
  s = opcode & 0x1f;
  d = (opcode >> 9) & 0x1f;

  n = 0;
  while(table_propeller[n].instr != NULL)
  {
    if ((opcode & table_propeller[n].mask) == table_propeller[n].opcode)
    {
      *cycles_min = table_propeller[n].cycles_min;
      *cycles_max = table_propeller[n].cycles_min;

      switch(table_propeller[n].type)
      {
        case PROPELLER_OP_NONE:
        {
          strcpy(instruction, table_propeller[n].instr);
          return 4;
        }
        case PROPELLER_OP_DS:
        {
          if (i == 0)
          {
            sprintf(instruction, "%s 0x%x, 0x%x", table_propeller[n].instr, d, s);
          }
            else
          {
            sprintf(instruction, "%s 0x%x, #0x%x", table_propeller[n].instr, d, s);
          }
          return 4;
        }
        case PROPELLER_OP_S:
        {
          if (i == 0)
          {
            sprintf(instruction, "%s 0x%x", table_propeller[n].instr, s);
          }
            else
          {
            sprintf(instruction, "%s #0x%x", table_propeller[n].instr, s);
          }
          return 4;
        }
        case PROPELLER_OP_D:
        {
          sprintf(instruction, "%s 0x%x", table_propeller[n].instr, d);
          return 4;
        }
        case PROPELLER_OP_IMMEDIATE:
        {
          sprintf(instruction, "%s #0x%x", table_propeller[n].instr, s);
          return 4;
        }
        default:
        {
          //print_error_internal(asm_context, __FILE__, __LINE__);
          break;
        }
      }
    }

    n++;
  }

  strcpy(instruction, "???");

  return 1;
}

void list_output_propeller(struct _asm_context *asm_context, uint32_t start, uint32_t end)
{
  int cycles_min, cycles_max;
  uint32_t opcode;
  char instruction[128];
  char bytes[16];
  int count;

  fprintf(asm_context->list, "\n");

  while(start < end)
  {
    count = disasm_propeller(&asm_context->memory, start, instruction, &cycles_min, &cycles_max);

    opcode = get_opcode32(&asm_context->memory, start);
    sprintf(bytes, "0x%08x", opcode);

    fprintf(asm_context->list, "0x%04x: %-16s %-40s cycles: ", start / 4, bytes, instruction);

    if (cycles_min == 0)
    {
      fprintf(asm_context->list, "?\n");
    }
      else
    if (cycles_min == cycles_max)
    {
      fprintf(asm_context->list, "%d\n", cycles_min);
    }
      else
    if (cycles_max < 1)
    {
      fprintf(asm_context->list, "%d or %d\n", cycles_min, -cycles_max);
    }
      else
    {
      fprintf(asm_context->list, "%d-%d\n", cycles_min, cycles_max);
    }

    start += count;
  }
}

void disasm_range_propeller(struct _memory *memory, uint32_t start, uint32_t end)
{
  char instruction[128];
  char bytes[16];
  int cycles_min = 0,cycles_max = 0;
  int count;

  printf("\n");

  printf("%-7s %-5s %-40s Cycles\n", "Addr", "Opcode", "Instruction");
  printf("------- ------ ----------------------------------       ------\n");

  while(start <= end)
  {
    count = disasm_propeller(memory, start, instruction, &cycles_min, &cycles_max);

    sprintf(bytes, "0x%08x", READ_RAM32(start));
    printf("0x%04x: %-16s %-40s ", start / 4, bytes, instruction);

    if (cycles_min == 0)
    {
      printf("?\n");
    }
      else
    if (cycles_min == cycles_max)
    {
      printf("%d\n", cycles_min);
    }
      else
    if (cycles_max < 1)
    {
      printf("%d or %d\n", cycles_min, -cycles_max);
    }
      else
    {
      printf("%d-%d\n", cycles_min, cycles_max);
    }

    start = start + count;
  }
}


