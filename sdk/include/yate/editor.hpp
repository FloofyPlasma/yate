#ifndef YATE_SDK_EDITOR_HPP
#define YATE_SDK_EDITOR_HPP

#include <cstdint>
#include <memory>

namespace yate {
class Editor {
  public:
  virtual ~Editor() = default;

  virtual bool forward_key() = 0;
  virtual bool forward_mouse() = 0;

  virtual void tick(float dt, std::uint32_t viewport_width, std::uint32_t viewport_height) = 0;
};

std::unique_ptr<Editor> create_editor();
} // namespace yate

#endif
