#include "win32.h"

namespace win32 {

namespace detail {

static constexpr auto window_class_name = L"main";

LRESULT CALLBACK wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
  if (msg == WM_DESTROY) {
    PostQuitMessage(0);
    return 0;
  }

  return DefWindowProcW(hwnd, msg, wparam, lparam);
}

void register_window_class() {
  WNDCLASSEXW wcex{};
  wcex.cbSize = sizeof(WNDCLASSEXW);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = wndproc;
  wcex.hInstance = ::GetModuleHandleW(nullptr);
  wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
  wcex.lpszClassName = window_class_name;
  ::RegisterClassExW(&wcex);
}

} // namespace detail

HWND create_window() {
  detail::register_window_class();
  return ::CreateWindowExW(0, detail::window_class_name, L"",
                           WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                           640, 480, nullptr, nullptr,
                           ::GetModuleHandleW(nullptr), nullptr);
}

bool process_messages() {
  MSG msg{};
  while (::PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
    ::TranslateMessage(&msg);
    ::DispatchMessageW(&msg);
    if (msg.message == WM_QUIT) {
      return false;
    }
  }
  return true;
}

} // namespace win32
