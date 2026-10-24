#pragma once

#include "../../lib/cpptui.hpp"
#include "../core/config/config.h"

using namespace cpptui;

template <typename T>
using part = std::shared_ptr<T>;

template <typename T, typename... Args>
auto mkpart(Args &&...args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

std::string center(const std::string &text);
void openUrl(const std::string &url);

// Shared TUI state, defined in Root.cpp
extern json g_config;
extern App *g_app;
extern part<Label> g_statusLabel;

void setStatus(const std::string &msg, int durationMs = 2000);
void notifyConfigChanged();
void requestHotkeyRebuild();

// UI builders
part<Vertical> Header();
part<Border> buildMacroCard(const std::string &name, const json &macro);
part<Border> Footer();
void Root();