#pragma once
#include <stdint.h>

//We only need a stack to hold 16 bit addresses, we don't need a general purpose one
//or the performance overhead that comes with it.
typedef struct
{
    uint16_t* data;
    int len;
} AddressStack;

//Returns:
//0: if successful
//1: if the stack is NULL

AddressStack* 
AddressStack_Create();
void 
AddressStack_Delete(AddressStack* stack);
int 
AddressStack_Add(AddressStack* stack, uint16_t address);

//Debug
int
AddressStack_Print(AddressStack* stack, int index);
int 
AddressStack_PrintStack(AddressStack* stack);