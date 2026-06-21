#include <yate/editor.hpp>

namespace yate {
class EditorImpl : public Editor {
  public:
  EditorImpl();
  ~EditorImpl() override = default;

  bool forward_key() override {
    return true;
  }
  bool forward_mouse() override {
    return true;
  }

  void tick(float dt, std::uint32_t viewport_width, std::uint32_t viewport_height) override {}
};

EditorImpl::EditorImpl() {}

std::unique_ptr<Editor> create_editor() {
  return std::make_unique<EditorImpl>();
}
} // namespace yate
