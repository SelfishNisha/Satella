#include "../ui.h"

// this is just the final handoff from the input callback into the macro save function
void writeMacroField(std::function<void(std::string)> onChange, std::string value) {
  onChange(std::move(value));
}
