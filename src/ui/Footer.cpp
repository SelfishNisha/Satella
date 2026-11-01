#include "ui.h"

part<Border> Footer() {
  auto footer = mkpart<Border>();
  // keep the help/footer pane a fixed size so it doesn't push the cards around
  footer->fixed_height = 9;
  footer->height = 9;

  auto inner = mkpart<Vertical>();
  inner->fixed_height = 9;

  auto line = mkpart<Horizontal>();
  auto help = mkpart<Label>("Need help? ");
  auto link = mkpart<Button>(StyledText().underline("How To Use"), openHowToUseUrl);
  link->bg_color = Color(26, 27, 38);
  link->hover_color = Color(26, 27, 38);
  link->focus_color = Color(26, 27, 38);
  link->text_color = Color(122, 162, 247);

  auto note = mkpart<Label>(" — opens in your browser");
  line->add(help);
  line->add(link);
  line->add(note);
  inner->add(line);

  auto hintA = mkpart<Label>("Tab · move focus   |   Enter/Space · toggle");
  hintA->fg_color = Color(114, 118, 146);
  inner->add(hintA);

  auto hintB = mkpart<Label>("Changes are saved to config.json automatically");
  hintB->fg_color = Color(114, 118, 146);
  inner->add(hintB);

  // status text is updated live when config writes complete or reloads happen
  gStatusLabel = mkpart<Label>("");
  gStatusLabel->fg_color = Color(158, 206, 106);
  inner->add(gStatusLabel);

  footer->add(inner);

  return footer;
}