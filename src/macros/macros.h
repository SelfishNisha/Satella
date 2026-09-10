#pragma once

#include <string>
#include <variant>
#include <vector>

using ExtraValue = std::variant<bool, std::string>;

void pearlCatch(
  std::vector<std::string> keys,
  std::vector<ExtraValue> extra);

void stunSlam(
  std::vector<std::string> keys,
  std::vector<ExtraValue> extra);

void breachSwap(std::vector<std::string> keys);

void lungeSwap(std::vector<std::string> keys);

void singleAnchor(std::vector<std::string> keys);