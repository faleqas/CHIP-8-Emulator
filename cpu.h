#pragma once
#include <stdint.h>

#include "display.h"

#define RAM_SIZE 4096


typedef struct
{
    uint16_t pc;
    uint16_t i; //index register
    uint8_t delay_timer;
    uint8_t sound_timer;
    
    uint8_t v[16]; //v registers
    
    unsigned char memory[RAM_SIZE];
} CPU;

CPU*
CPU_Create();

void
CPU_Delete(CPU* cpu);

uint16_t
CPU_Fetch(CPU* cpu);

//decode and execute
void
CPU_Dexecute(CPU* cpu, Display* display, const uint16_t inst);