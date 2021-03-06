//
//   Criando uma janela para ser renderizada pelo OpenGl
//   Uso do SDL2
// 

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

SDL_Window* displayWindow;

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Renderer* displayRenderer;

	int flags = SDL_WINDOW_OPENGL;

	atexit(SDL_Quit);
	
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_CreateWindowAndRenderer(800, 600, flags,&displayWindow, &displayRenderer);

    SDL_GL_CreateContext(displayWindow);
    SDL_Delay(500);
    SDL_Quit();
    
    return 0;
}
