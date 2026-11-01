#include "../ui.h"

// clears the current macro list and rebuilds it from the latest config data
void rebuildMacroCards(part<ScrollableVertical> scroll) {
  if (!scroll) {
    return;
  }

  scroll->clear_children();
  for (auto &[name, macro] : gConfig["Macros"].items()) {
    scroll->add(buildMacroCard(name, macro));
  }
}
