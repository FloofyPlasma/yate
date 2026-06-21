#ifndef APP_RENDERER_HPP
#define APP_RENDERER_HPP

#include <memory>
#include <cstdint>

struct SDL_Window;

namespace yate::app {
    class Renderer {
    public:
        virtual ~Renderer() = default;

        virtual void submit() = 0;
        virtual void present() = 0;
        virtual void resize(std::uint32_t width, std::uint32_t height) = 0;

        virtual std::uint32_t width() const = 0;
        virtual std::uint32_t height() const = 0;
    };

    std::unique_ptr<Renderer> create_bgfx_renderer(SDL_Window* window);
} // namespace yate::app

#endif
