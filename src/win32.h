#include <Windows.h>

namespace win32 {

HWND create_window();

void show_window(const HWND);

bool process_messages();

} // namespace win32
