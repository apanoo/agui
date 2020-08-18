#include <stdio.h>
#include <SDL.h>
#include <glad/glad.h>
#include <imgui.h>

#include "util.h"

SDL_Window *_sdl_window;
SDL_GLContext _glContext;
SDL_Event _event;
bool _quit = false;

void initGL()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("Could not initialize SDL");
    }

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    _sdl_window = SDL_CreateWindow(
        "Test", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 600, 480,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (_sdl_window == NULL)
    {
        SDL_Log("Could not create window");
    }
    _glContext = SDL_GL_CreateContext(_sdl_window);
    if (_glContext == NULL)
    {
        SDL_Log("Could not create the OpenGL context");
    }

    gladLoadGLLoader(SDL_GL_GetProcAddress);
    SDL_Log("OpenGL : %s", glGetString(GL_VERSION));

    // V-Sync
    SDL_GL_SetSwapInterval(1);

    // set viewport
    GLint vpWidth, vpHeight;
    SDL_GL_GetDrawableSize(_sdl_window, &vpWidth, &vpHeight);
    glViewport(0, 0, vpWidth, vpHeight);

    //// enable bland for rgba format texture
    glEnable(GL_BLEND);
    //// set blend mode
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void initImgui()
{
}

void render()
{
}

int main()
{
    initGL();
    initImgui();
    while (!_quit)
    {

        // event loop
        while (SDL_PollEvent(&_event))
        {
            if (_event.type == SDL_QUIT)
                _quit = true;
            if (_event.type == SDL_WINDOWEVENT && _event.window.event == SDL_WINDOWEVENT_CLOSE && _event.window.windowID == SDL_GetWindowID(_sdl_window))
                _quit = true;
        }

        // show 3D model should clear depth bit
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        SDL_GL_SwapWindow(_sdl_window);

        // check error and pause
        glCheckError();

        render();
    }

    SDL_DestroyWindow(_sdl_window);
    _sdl_window = nullptr;

    SDL_Quit();
}
