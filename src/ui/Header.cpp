#include "ui.h"

part<Vertical> Header() {
  auto header = mkpart<Vertical>();
  header->fixed_height = 4;
  header->height = 4;

  auto subtitle = mkpart<Label>(center("Satella  ·  Config Editor"));
  subtitle->fg_color = Color(169, 177, 214);
  subtitle->focusable = false;
  header->add(subtitle);

  auto sep = mkpart<Label>(center("────────────────────────────────────────────"));
  sep->fg_color = Color(41, 46, 66);
  sep->focusable = false;
  header->add(sep);

  return header;
}