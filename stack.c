#include <malloc.h>
#include "stack.h"

AddressStack* 
AddressStack_Create()
{
    AddressStack* stack = (AddressStack*)malloc(sizeof(AddressStack));
    stack->data = NULL;
    stack->len = 0;

    return stack;
}

void 
AddressStack_Delete(AddressStack* stack)
{
    if (!stack)
    {
        return;
    }

    if (stack->data != NULL)
    {
        free(stack->data);
        stack->data = NULL;
    }

    free(stack);
    stack = NULL;
}

int 
AddressStack_Add(AddressStack* stack, uint16_t address)
{
    if (!stack)
    {
        return 1;
    }

    if (stack->data == NULL)
    {
        stack->len = 1;
        stack->data = (uint16_t*)malloc(sizeof(uint16_t) * stack->len);
    }
    else
    {
        stack->len++;
        stack->data = (uint16_t*)realloc(stack->data, sizeof(uint16_t) * stack->len);
    }

    stack->data[stack->len-1] = address;

    return 0;
}

//THIS SHOULD PRINT IN HEX BUT I FORGOT THE FORMATTING.
int 
AddressStack_Print(AddressStack* stack, int index)
{
    if (!stack)
    {
        return 1;
    }
    if (!(stack->data))
    {
        return 2;
    }

    if (index >= stack->len)
    {
        return 3;
    }

    uint16_t address = stack->data[index];
    printf("%d |", address);

    return 0;
}

int 
AddressStack_PrintStack(AddressStack* stack)
{
    if (!stack)
    {
        return 1;
    }
    if (!(stack->data))
    {
        return 2;
    }

    for (int i = 0; i < stack->len; i++)
    {
        AddressStack_Print(stack, i);
    }

    return 0;
}