#include "cpu.h"
#include <malloc.h>
#include "main.h"
#include "display.h"

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
    
    /*if (inst)
    {
        printf("\n%d at %d\n", inst, cpu->pc);
    }*/
    
    cpu->pc += 2;
    return inst;
}

void
CPU_Dexecute(CPU* cpu, Display* display, const uint16_t inst)
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
        } break;
        
        //set register
        case 0x6000:
        {
            uint16_t register_number = (inst & 0x0F00) >> 8;
            uint8_t* register_ptr = cpu->v + register_number;
            
            *register_ptr = (inst & 0x00FF);
        } break;
        
        //add to register
        case 0x7000:
        {
            uint16_t register_number = (inst & 0x0F00) >> 8;
            uint8_t* register_ptr = cpu->v + register_number;
            
            (*register_ptr) += (inst & 0x00FF);
        } break;
        
        //set i register
        case 0xA000:
        {
            cpu->i = inst & 0x0FFF;
        } break;
        
        //draw instruction
        case 0xD000:
        {
            if (!display)
            {
                break;
            }
            
            uint8_t* vx = (cpu->v) + ((inst & 0x0F00) >> 8);
            uint8_t* vy = (cpu->v) + ((inst & 0x00F0) >> 4);
            int color = inst & 0x000F;
            
            display->pixels[(*vx) + ((*vy) * DISPLAY_WIDTH)] = color;
            
        } break;
    };
}















