#include <iostream>
#include <string>
#include <windows.h>

std::string center(const std::string &text) {
  // Get console handle and screen buffer info
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  int termWidth = 80; // default fallback

  if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
    termWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  }

  // Calculate padding
  int textLength = static_cast<int>(text.length());
  int totalPadding = termWidth - textLength;

  if (totalPadding <= 0) {
    // Text is longer than terminal width, return as-is
    return text;
  }

  int leftPadding = totalPadding / 2;

  return std::string(leftPadding, ' ') + text;
}