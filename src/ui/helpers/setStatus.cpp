#include "../ui.h"

// sets a transient status message in the footer and refreshes the app so it shows immediately
void setStatus(const std::string& msg, int durationMs) {
  gStatusMsg = msg;
  gStatusExpiry = std::chrono::steady_clock::now() + std::chrono::milliseconds(durationMs);
  gStatusLabel->set_text(msg);
  if (gApp) {
    gApp->update();
  }
}
