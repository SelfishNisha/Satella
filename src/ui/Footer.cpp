#include "ui.h"

part<Border> Footer() {
  auto footer = mkpart<Border>();
  footer->fixed_height = 9;
  footer->height = 9;

  auto footInner = mkpart<Vertical>();
  footInner->fixed_height = 9;

  auto helpLine = mkpart<Horizontal>();
  auto helpText = mkpart<Label>("Need help? ");
  auto linkBtn = mkpart<Button>(
      StyledText().underline("How To Use"),
      [] { openUrl("https://github.com/selfishnisha/sattela/blob/main/how%20to%20use.md"); });
  linkBtn->bg_color = Color(26, 27, 38); // flat link look: matches root background
  linkBtn->hover_color = Color(26, 27, 38);
  linkBtn->focus_color = Color(26, 27, 38);
  linkBtn->text_color = Color(122, 162, 247); // TokyoNight primary blue
  auto noteText = mkpart<Label>(" — opens in your browser");
  helpLine->add(helpText);
  helpLine->add(linkBtn);
  helpLine->add(noteText);
  footInner->add(helpLine);

  auto hint1 = mkpart<Label>(
      "F4 · quit   |   Tab · move focus   |   Enter/Space · toggle");
  hint1->fg_color = Color(114, 118, 146);
  footInner->add(hint1);

  auto hint2 = mkpart<Label>("Changes are saved to config.json automatically");
  hint2->fg_color = Color(114, 118, 146);
  footInner->add(hint2);

  g_statusLabel = mkpart<Label>("");
  g_statusLabel->fg_color = Color(158, 206, 106); // success green
  footInner->add(g_statusLabel);

  footer->add(footInner);

  return footer;
}