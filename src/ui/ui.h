#include "../../lib/cpptui.hpp"

using namespace cpptui;

template <typename T>
using part = std::shared_ptr<T>;

template <typename T, typename... Args>
auto mkpart(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

std::string center(const std::string &text);

part<Vertical> Header();
void Root();