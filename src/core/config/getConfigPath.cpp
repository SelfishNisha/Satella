#include <windows.h>
#include <string>

// Gets the path to the config file
std::string getConfigPath() {
  // create a buffer to store the path of the exe
  char buffer[MAX_PATH];

  // get full path of the exe
  GetModuleFileNameA(NULL, buffer, MAX_PATH);

  // convert the char buffer into a string
  std::string path(buffer);

  // find the locaion of the last backslash in the path
  size_t pos = path.find_last_of('\\');

  // remove the exe name and add config.json
  return path.substr(0, pos + 1) + "config.json";
}