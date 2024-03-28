#include "main.h"
#include "cpu.h"

static int running = 1;
static SDL_Renderer* renderer = NULL; 

int 
CreateWindow(SDL_Window** window, SDL_Surface** window_surface);

int 
main(int argc, char** argv)
{
    SDL_Window *window = NULL;
    SDL_Surface *window_surface = NULL;
    
    int code = CreateWindow(&window, &window_surface);
    if (code)
    {
        return code; //ERROR
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  
    SDL_Event e;
    AddressStack* stack = AddressStack_Create();
    {
        // AddressStack_Add(stack, 0xFFAE);
        // AddressStack_Add(stack, 0x0001);
        // AddressStack_Add(stack, 0x100F);
        // AddressStack_PrintStack(stack);
    }

    CPU* cpu = CPU_Create();
    cpu->memory[0] = 0x10;
    cpu->memory[1] = 0x04;
    
    cpu->memory[4] = 0x00;
    cpu->memory[5] = 0xE0;

    cpu->memory[6] = 0x10;
    cpu->memory[7] = 0x00;

    uint16_t inst = 0;

    while (running)
    {
        while (SDL_PollEvent(&e) > 0)
        {
            switch (e.type)
            {
                case SDL_QUIT:
                {
                    running = 0;
                } break;
            }                    
        }

        inst = CPU_Fetch(cpu);
        CPU_Dexecute(cpu, inst);

        SDL_RenderPresent(renderer);
    }
    AddressStack_Delete(stack);
    CPU_Delete(cpu);

    return 0;
}

int 
CreateWindow(SDL_Window** window, SDL_Surface** window_surface)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialize the SDL2 library\n");
        return -1;
    }
    
    *window = SDL_CreateWindow("SDL2 Window",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              680, 480,
                              0);
    
    if(!(*window))
    {
        printf("Failed to create window\n");
        return -1;
    }
    
    *window_surface = SDL_GetWindowSurface(*window);
    
    if(!(*window_surface))
    {
        printf("Failed to get the surface from the window\n");
        return -1;
    }
    return 0;
}

void 
ClearScreen()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}