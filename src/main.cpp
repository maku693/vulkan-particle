#include "win32.h"
#include <Windows.h>

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  const auto hwnd = win32::create_window();
  win32::show_window(hwnd);
  while (win32::process_messages()) {
  }
}
