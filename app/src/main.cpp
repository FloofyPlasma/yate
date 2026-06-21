#include "renderer.hpp"
#include <SDL3/SDL.h>
#include <chrono>
#include <iostream>
#include <print>
#include <yate/editor.hpp>

int main() {
  if (!::SDL_Init(SDL_INIT_VIDEO)) {
    std::println(std::cerr, "Failed to initialize SDL: {}", ::SDL_GetError());
  }

  SDL_Window* window = ::SDL_CreateWindow("yate", 1280, 720, SDL_WINDOW_RESIZABLE);
  if (!window) {
    std::println(std::cerr, "Failed to create window: {}", ::SDL_GetError());
    ::SDL_Quit();
    return 1;
  }
  {
    auto editor = yate::create_editor();
    if (!editor) {
      std::println(std::cerr, "Failed to create editor");
      ::SDL_DestroyWindow(window);
      ::SDL_Quit();
      return 1;
    }

    auto renderer = yate::app::create_bgfx_renderer(window);
    if (!renderer) {
      std::println(std::cerr, "Failed to create renderer");
      ::SDL_DestroyWindow(window);
      ::SDL_Quit();
      return 1;
    }

    bool running = true;
    auto last_time = std::chrono::high_resolution_clock::now();

    while (running) {
      SDL_Event event;
      while (::SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT: {
          running = false;
        } break;
        case SDL_EVENT_WINDOW_RESIZED: {
          renderer->resize(event.window.data1, event.window.data2);
        } break;
        default: {
        } break;
        }

        auto now = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration<float>(now - last_time).count();
        last_time = now;

        editor->tick(dt, renderer->width(), renderer->height());

        renderer->submit();
        renderer->present();
      }
    }
  }

  ::SDL_DestroyWindow(window);
  ::SDL_Quit();
  return 0;
}
