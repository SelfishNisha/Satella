#include "../ui.h"

// adds a widget to the card and keeps track of how many rows are in the layout
void addMacroCardRow(part<Vertical> container, part<Widget> widget, int& rowCount) {
  container->add(widget);
  ++rowCount;
}
