#include "ui.h"
#include "core.h"

#include <atomic>
#include <chrono>
#include <filesystem>
#include <thread>

json gConfig;
App *gApp = nullptr;
part<Label> gStatusLabel;
std::string gStatusMsg;
std::chrono::steady_clock::time_point gStatusExpiry;
part<ScrollableVertical> gScroll;

void Root() {
  // set the terminal title so the window looks like the app and not a blank console
  SetConsoleTitleA("Satella - Your Cute Little Macro");
  Theme::set_theme(Theme::TokyoNight());

  // if config.json doesn't exist yet, make a default one before the UI tries to read it
  if (!std::filesystem::exists(getConfigPath())) {
    saveConfig(defaultConfig);
  }
  gConfig = getConfig();

  // the app owns the UI state and status timer
  App app;
  gApp = &app;
  app.register_exit_key(VK_F4);

  // hotkeys live on their own thread, so the UI can keep updating while the hook runs
  std::thread hotkeyThread(registerHotkeys);
  hotkeyThread.detach();

  // wait a moment for the hook thread to initialize before the app starts doing stuff
  for (int i = 0; i < 100 && g_hookThreadId == 0; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  auto root = mkpart<Vertical>();
  root->add(Header());

  auto scroll = mkpart<ScrollableVertical>();
  gScroll = scroll;
  rebuildMacroCards(scroll);
  root->add(scroll);

  auto footer = Footer();
  root->add(footer);

  // re-check the config every few hundred ms so live edits show up without restarting
  app.add_timer(400, refreshUiState);

  app.run(root);
  gApp = nullptr;
  gScroll.reset();
}