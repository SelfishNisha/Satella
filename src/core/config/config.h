#include "../../../lib/json.hpp"
#include <vector>
#include <variant>
#include <string>

using json = nlohmann::ordered_json;
using ExtraValue = std::variant<bool, std::string>;

json loadConfig();
void saveConfig(const json& data);

std::string getConfigPath();
json getConfig();
std::vector<std::string> getKeys(std::string mn);
std::vector<ExtraValue> getExtra(std::string mn);

extern const json defaultConfig;