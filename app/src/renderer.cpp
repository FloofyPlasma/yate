#include "renderer.hpp"

#include <SDL3/SDL.h>
#include <bgfx/bgfx.h>

#include <iostream>
#include <print>

namespace yate::app {
class BgfxRenderer : public Renderer {
  public:
  BgfxRenderer(SDL_Window* window);
  ~BgfxRenderer() override;

  void submit() override;
  void present() override;
  void resize(std::uint32_t width, std::uint32_t height) override;

  std::uint32_t width() const override {
    return m_width;
  }
  std::uint32_t height() const override {
    return m_height;
  }

  private:
  SDL_Window* m_window;
  std::uint32_t m_width, m_height;
};

BgfxRenderer::BgfxRenderer(SDL_Window* window) : m_window(window) {
  int w, h;
  ::SDL_GetWindowSize(window, &w, &h);
  m_width = w;
  m_height = h;

  bgfx::PlatformData pd{};
  pd.type = bgfx::NativeWindowHandleType::Default;

#if defined(SDL_PLATFORM_WIN32)
  pd.nwh = ::SDL_GetPointerProperty(::SDL_GetWindowProperties(window),
                                    SDL_PROP_WINDOW_WIN32_HWND_POINTER, NULL);
#elif defined(SDL_PLATFORM_MACOS)
  pd.nwh = ::SDL_GetPointerProperty(::SDL_GetWindowProperties(window),
                                    SDL_PROP_WINDOW_COCOA_WINDOW_POINTER, NULL);
#elif defined(SDL_PLATFORM_LINUX)
  if (::SDL_strcmp(::SDL_GetCurrentVideoDriver(), "x11") == 0) {
    pd.ndt = ::SDL_GetPointerProperty(::SDL_GetWindowProperties(window),
                                      SDL_PROP_WINDOW_X11_DISPLAY_POINTER, NULL);
    pd.nwh = ::SDL_GetPointerProperty(::SDL_GetWindowProperties(window),
                                      SDL_PROP_WINDOW_X11_WINDOW_NUMBER, NULL);
  } else if (::SDL_strcmp(::SDL_GetCurrentVideoDriver(), "wayland") == 0) {
    pd.ndt = ::SDL_GetPointerProperty(::SDL_GetWindowProperties(window),
                                      SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER, NULL);
    pd.nwh = ::SDL_GetPointerProperty(::SDL_GetWindowProperties(window),
                                      SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, NULL);
    pd.type = bgfx::NativeWindowHandleType::Wayland;
  }
#endif

  bgfx::Init init{};
  init.platformData = pd;
  init.type = bgfx::RendererType::Count;
  init.resolution.width = m_width;
  init.resolution.height = m_height;
  init.resolution.reset = BGFX_RESET_VSYNC;

  if (!bgfx::init(init)) {
    std::println(std::cerr, "What the fuck?");
    std::abort();
  }
  bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x1e1e1eff, 1.0f, 0);
}

BgfxRenderer::~BgfxRenderer() {
     bgfx::shutdown();
}

void BgfxRenderer::submit() {
    bgfx::setViewRect(0, 0, 0, m_width, m_height);
    bgfx::touch(0);
}

void BgfxRenderer::present() {
    bgfx::frame();
}

void BgfxRenderer::resize(std::uint32_t width, std::uint32_t height) {
    m_width = width;
    m_height = height;
    bgfx::reset(width, height, BGFX_RESET_VSYNC);
}

std::unique_ptr<Renderer> create_bgfx_renderer(SDL_Window* window) {
  return std::make_unique<BgfxRenderer>(window);
}

} // namespace yate::app
