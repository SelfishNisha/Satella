#include <iostream>
#include <string>
#include <windows.h>

static int utf8Cols(const std::string& s) {
  int cols = 0;
  for (unsigned char c : s) {
    if ((c & 0xC0) != 0x80) cols++;
  }
  return cols;
}

static std::string centerLine(const std::string& text, int width) {
  int pad = (width - utf8Cols(text)) / 2;
  if (pad < 0) pad = 0;
  return std::string(pad, ' ') + text;
}

// centers text based on the current terminal width so the title looks lined up
std::string center(const std::string& text) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  int termWidth = 80;

  if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
    termWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  }

  return centerLine(text, termWidth);
}