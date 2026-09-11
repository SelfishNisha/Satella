@echo off
mkdir lib 2>nul

curl -L -o lib/rang.hpp https://raw.githubusercontent.com/agauniyal/rang/master/include/rang.hpp
curl -L -o lib/json.hpp https://github.com/nlohmann/json/releases/download/v3.12.0/json.hpp

echo Done.