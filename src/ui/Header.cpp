#include "ui.h"

part<Vertical> Header() {
  part<Vertical> header = mkpart<Vertical>();

  // Big, bold, centered title
  part<Label> title = mkpart<Label>(center("===------- Satella -------==="));
  header->add(title);

  return header;
}