#include "ui.h"

part<Vertical> Header() {
  auto header = mkpart<Vertical>();

  // keep the title block compact so the editor doesn't stretch vertically
  header->fixed_height = 5;
  header->height = 5;

  // measure the console up front, everything below centers against this
  int termWidth = 80;
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
    termWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  }

  auto title = mkpart<Label>(center("Satella  ·  Config Editor"));
  title->fg_color = Color(169, 177, 214);
  title->focusable = false;
  header->add(title);

  // blank row between the title and the button
  auto gap = mkpart<Label>(std::string(" "));
  gap->focusable = false;
  header->add(gap);

  const bool holdToLoopEnabled = gConfig.contains("Hold To Loop") && gConfig["Hold To Loop"].get<bool>();

  auto holdButton = mkpart<Checkbox>(StyledText("   Hold To Loop"), holdToLoopEnabled);
  holdButton->text_color = holdToLoopEnabled ? Color(158, 206, 106) : Color(96, 100, 130);
  holdButton->focus_color = holdToLoopEnabled ? Color(158, 206, 106) : Color(96, 100, 130);
  holdButton->hover_color = holdToLoopEnabled ? Color(158, 206, 106) : Color(96, 100, 130);
  holdButton->on_change = [holdButton](bool enabled) {
    holdButton->text_color = enabled ? Color(158, 206, 106) : Color(96, 100, 130);
    holdButton->focus_color = enabled ? Color(158, 206, 106) : Color(96, 100, 130);
    holdButton->hover_color = enabled ? Color(158, 206, 106) : Color(96, 100, 130);
    gConfig["Hold To Loop"] = enabled;
    notifyConfigChanged();
  };

  // Vertical stacks children top to bottom, so a spacer label above the button
  // just made a blank row. put the button in its own Horizontal row instead:
  // [left spacer][button]
  const int leftPad = std::max(0, (termWidth - 18) / 2);

  auto spacer = mkpart<Label>(std::string(leftPad, ' '));
  spacer->focusable = false;
  spacer->fixed_width = leftPad;
  spacer->width = leftPad;

  auto buttonRow = mkpart<Horizontal>();
  buttonRow->add(spacer);
  buttonRow->add(holdButton);
  header->add(buttonRow);

  return header;
}