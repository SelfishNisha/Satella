#include "ui.h"
#include "core.h"

#include <shellapi.h>
#include <atomic>
#include <chrono>
#include <filesystem>
#include <thread>

#pragma comment(lib, "shell32.lib")

json g_config;
App *g_app = nullptr;
part<Label> g_statusLabel;

std::string g_statusMsg;
std::chrono::steady_clock::time_point g_statusExpiry;

void setStatus(const std::string &msg, int durationMs) {
  g_statusMsg = msg;
  g_statusExpiry = std::chrono::steady_clock::now() +
                   std::chrono::milliseconds(durationMs);
  g_statusLabel->set_text(msg);
  if (g_app) {
    g_app->update();
  }
}

void notifyConfigChanged() {
  saveConfig(g_config);
  invalidateConfigCache();
  setStatus("Saved to config.json", 1500);
  g_hotkeysDirty = true;
  requestHotkeyRebuild();
}

void requestHotkeyRebuild() {
  g_hotkeysDirty = true;
  if (g_hookThreadId != 0) {
    PostThreadMessage(g_hookThreadId, WM_APP + 1, 0, 0);
  }
}

void openUrl(const std::string &url) {
  ShellExecuteA(nullptr, "open", url.c_str(), nullptr, nullptr, SW_SHOW);
}

void Root() {
  SetConsoleTitleA("Satella - Your Cute Little Macro");
  Theme::set_theme(Theme::TokyoNight());

  // Make sure config.json exists before loading (silently create defaults)
  if (!std::filesystem::exists(getConfigPath())) {
    saveConfig(defaultConfig);
  }
  g_config = getConfig();

  App app;
  g_app = &app;
  app.register_exit_key(VK_F4);

  // The hotkey hook lives on its own thread so the TUI stays responsive.
  std::thread hotkeyThread(registerHotkeys);
  hotkeyThread.detach();
  for (int i = 0; i < 100 && g_hookThreadId == 0; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  auto root = mkpart<Vertical>();
  root->add(Header());

  auto scroll = mkpart<ScrollableVertical>();

  std::function<void()> rebuildCards = [&]() {
    scroll->clear_children();
    for (auto &[name, macro] : g_config["Macros"].items()) {
      scroll->add(buildMacroCard(name, macro));
    }
  };
  rebuildCards();
  root->add(scroll);

  //  footer
  auto footer = Footer();
  
  root->add(footer);

  // Timers: clear expired status + reload config from disk so external edits
  // show up in the TUI in real time.
  app.add_timer(400, [&]() {
    if (!g_statusMsg.empty() &&
        std::chrono::steady_clock::now() >= g_statusExpiry) {
      g_statusMsg.clear();
      g_statusLabel->set_text("");
    }

    json fresh = loadConfig();
    if (fresh.dump() != g_config.dump()) {
      g_config = fresh;
      rebuildCards();
      g_hotkeysDirty = true;
      requestHotkeyRebuild();
      setStatus("Config reloaded from disk", 2500);
    }
  });

  app.run(root);
  g_app = nullptr;
}