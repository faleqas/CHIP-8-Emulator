#include "cpu.h"
#include <malloc.h>
#include "main.h"


CPU* 
CPU_Create()
{
    CPU* cpu = calloc(1, sizeof(CPU));

    return cpu;
}

void
CPU_Delete(CPU* cpu)
{
    if (cpu)
    {
        free(cpu);
        cpu = NULL;
    }
}


uint16_t
CPU_Fetch(CPU* cpu)
{
    if (cpu->pc >= RAM_SIZE-1) //we need 2 bytes at a time so we stop at 4094
    {
        cpu->pc = 0;
    }
    uint8_t byte1 = cpu->memory[cpu->pc];
    uint16_t byte2 = (uint16_t)(cpu->memory[cpu->pc+1]) << 8;
    uint16_t inst = (byte1 << 8) | (byte2 >> 8);

    printf("%d at %d\n", inst, cpu->pc);

    cpu->pc += 2;
    return inst;
}

void
CPU_Dexecute(CPU* cpu, uint16_t inst)
{
    switch (inst & 0xF000)
    {
        case 0x0000:
        {
            switch (inst)
            {
                case 0x00E0: //CLEAR SCREEN
                {
                    ClearScreen();
                } break;
            };
        } break;

        case 0x1000:
        {
            uint16_t to = inst & 0x0FFF;
            
            //the max 12 bit number is the same as RAM_SIZE(4096) so no need for bound checking
            //(the max is actually 4095 but we index at 0 duh)
            cpu->pc = to;
        }
    };
}