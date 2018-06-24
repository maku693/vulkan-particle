#include "win32.h"

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  const auto hwnd = win32::create_window();
  while (win32::process_messages()) {
  }
}
