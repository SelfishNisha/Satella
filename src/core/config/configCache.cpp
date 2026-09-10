#include "config.h"

static json configCache;

// saves the config into ram and returns the cached data
json getConfig() {
  if (configCache.empty()) {
    configCache = loadConfig();
  }
  return configCache;
}