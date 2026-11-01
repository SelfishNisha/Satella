#include <iostream>
#include <string>
#include <windows.h>

// centers text based on the current terminal width so the title looks lined up
std::string center(const std::string& text) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  int termWidth = 80;

  if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
    termWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  }

  int textLength = static_cast<int>(text.length());
  int totalPadding = termWidth - textLength;

  if (totalPadding <= 0) {
    return text;
  }

  int leftPadding = totalPadding / 2;

  return std::string(leftPadding, ' ') + text;
}