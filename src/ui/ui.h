#pragma once

#include <chrono>
#include <functional>
#include <string>

#include "../../lib/cpptui.hpp"
#include "../core/config/config.h"

// shared UI state and helper functions for the config editor

using namespace cpptui;

template <typename T>
using part = std::shared_ptr<T>;

template <typename T, typename... Args>
auto mkpart(Args &&...args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

std::string center(const std::string& text);
void openUrl(const std::string& url);
void openHowToUseUrl();

// Shared TUI state, defined in Root.cpp
extern json gConfig;
extern App *gApp;
extern part<Label> gStatusLabel;
extern std::string gStatusMsg;
extern std::chrono::steady_clock::time_point gStatusExpiry;
extern part<ScrollableVertical> gScroll;

void setStatus(const std::string& msg, int durationMs = 2000);
void notifyConfigChanged();
void requestHotkeyRebuild();
void refreshUiState();
void rebuildMacroCards(part<ScrollableVertical> scroll);
void addMacroCardRow(part<Vertical> container, part<Widget> widget, int& rowCount);
void addMacroFieldRow(part<Vertical> container, const std::string& labelText, const std::string& initial, const std::string& macroName, std::function<void(std::string)> write, int& rowCount);
void writeMacroField(std::function<void(std::string)> onChange, std::string value);
std::function<void(std::string)> saveMacroField(const std::string& macroName, std::function<void(std::string)> write);
void saveMacroValue(const std::string& macroName, std::function<void(std::string)> write, std::string value);
void setMacroFieldValue(const std::string& macroName, const std::string& fieldName, std::string value);
void setMacroSlotValue(const std::string& macroName, const std::string& slotName, std::string value);
void setMacroExtraValue(const std::string& macroName, const std::string& extraName, std::string value);
void handleMacroToggle(const std::string& name, part<Border> border, bool enabled);

// UI builders
part<Vertical> Header();
part<Border> buildMacroCard(const std::string& name, const json& macro);
part<Border> Footer();
void Root();