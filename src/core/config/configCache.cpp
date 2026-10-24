#include "config.h"

static json configCache;

// saves the config into ram and returns the cached data
json getConfig() {
  if (configCache.empty()) {
    configCache = loadConfig();
  }
  return configCache;
}

// drops the cached config so the next getConfig() re-reads config.json from
// disk (used after the TUI writes changes live)
void invalidateConfigCache() { configCache = json(); }