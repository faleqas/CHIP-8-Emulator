#include "main.h"
#include "cpu.h"
#include "display.h"

static int running = 1;
static SDL_Renderer* renderer = NULL; 

static Display* display = NULL;
static CPU* cpu = NULL;

int 
CreateWindow(SDL_Window** window, SDL_Surface** window_surface);

int 
main(int argc, char** argv)
{
    SDL_Window* window = NULL;
    SDL_Surface* window_surface = NULL;
    
    int code = CreateWindow(&window, &window_surface);
    if (code)
    {
        return code; //ERROR
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    display = Display_create();
    
    SDL_Event e;
    AddressStack* stack = AddressStack_Create();
    {
        AddressStack_Add(stack, 0xFFAE);
        AddressStack_Add(stack, 0x0001);
        AddressStack_Add(stack, 0x100F);
        //AddressStack_PrintStack(stack);
    }
    
    cpu = CPU_Create();
    
    //clear screen
    cpu->memory[0] = 0x00;
    cpu->memory[1] = 0xE0;
    
    //set register v0
    cpu->memory[2] = 0x60;
    cpu->memory[3] = DISPLAY_HEIGHT - 1;
    
    cpu->memory[4] = 0x61;
    cpu->memory[5] = DISPLAY_WIDTH - 1;
    
    //draw white pixel at (v1, v0)
    cpu->memory[6] = 0xD1;
    cpu->memory[7] = 0x01;
    
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
        CPU_Dexecute(cpu, display, inst);
        
        Display_draw(display, renderer);
        
        SDL_RenderPresent(renderer);
    }
    
    printf("v0: %d\n", cpu->v[0]);
    printf("v6: %d\n", cpu->v[1]);
    printf("i: %d\n", cpu->i);
    
    if (PROGRAM_CLEANUP)
    {
        AddressStack_Delete(stack);
        CPU_Delete(cpu);
        Display_destroy(display);
    }
    
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
                               WINDOW_WIDTH, WINDOW_HEIGHT,
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
    if (display)
    {
        Display_clear(display, 0);
    }
}