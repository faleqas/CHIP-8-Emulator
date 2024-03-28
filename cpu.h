#pragma once
#include <stdint.h>
#include "main.h"


typedef struct
{
    uint16_t pc;
    uint16_t i;
    uint8_t delay_timer;
    uint8_t sound_timer;

    uint8_t v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve;

    unsigned char memory[RAM_SIZE];
} CPU;

CPU*
CPU_Create();

void
CPU_Delete(CPU* cpu);

uint16_t
CPU_Fetch(CPU* cpu);

void
CPU_Dexecute(CPU* cpu, uint16_t inst);