#include "ui.h"

part<Vertical> Header() {
  auto header = mkpart<Vertical>();
  
  // keep the title block compact so the editor doesn't stretch vertically
  header->fixed_height = 4;
  header->height = 4;

  auto title = mkpart<Label>(center("Satella  ·  Config Editor"));
  title->fg_color = Color(169, 177, 214);
  title->focusable = false;
  header->add(title);

  auto sep = mkpart<Label>(center("────────────────────────────────────────────"));
  sep->fg_color = Color(41, 46, 66);
  sep->focusable = false;
  header->add(sep);

  return header;
}