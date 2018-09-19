#ifndef CLEANUP_H
#define CLEANUP_H

// variadic template

#include <utility>
#include <SDL2/SDL.h>

template<typename T, typename... Args>
void CleanUp(T * &t, Args &&... args)  // 采用c++14的写法，可以确保传输的参数能以引用的方式返回自身
{
    CleanUp(t);
    CleanUp(std::forward<Args>(args)...);
}


template<>
inline void CleanUp<SDL_Window>(SDL_Window * &objSDL_Window)
{
    if(objSDL_Window == nullptr){
        return;
    }
    SDL_DestroyWindow(objSDL_Window);
    objSDL_Window = nullptr;
}


template<>
inline void CleanUp<SDL_Texture>(SDL_Texture * &objSDL_Texture)
{
    if(objSDL_Texture == nullptr){
        return;
    }
    SDL_DestroyTexture(objSDL_Texture);
    objSDL_Texture = nullptr;
}

template<>
inline void CleanUp<SDL_Renderer>(SDL_Renderer * &objSDL_Renderer)
{
    if(objSDL_Renderer == nullptr){
        return;
    }
    SDL_DestroyRenderer(objSDL_Renderer);
    objSDL_Renderer = nullptr;
}

template<>
inline void CleanUp<SDL_Surface>(SDL_Surface * &objSDL_Surface)
{
    if(objSDL_Surface == nullptr){
        return;
    }
    SDL_FreeSurface(objSDL_Surface);
    objSDL_Surface = nullptr;
}


#endif // CLEANUP_H
