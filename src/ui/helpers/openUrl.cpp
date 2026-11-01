#include "../ui.h"

#include <shellapi.h>

#pragma comment(lib, "shell32.lib")

// opens a URL with the system browser
void openUrl(const std::string& url) {
  ShellExecuteA(nullptr, "open", url.c_str(), nullptr, nullptr, SW_SHOW);
}
