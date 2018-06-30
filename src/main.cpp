#include "vkutils.h"
#include "win32.h"
#include <Windows.h>
#include <vulkan/vulkan.hpp>

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  vk::ApplicationInfo app_info{nullptr, 0, nullptr, 0, VK_VERSION_1_1};

  const auto found_layer_names =
      vkutils::find_instance_layers({"VK_LAYER_LUNARG_standard_validation"});

  std::vector<const char *> layer_names{};
  for (const auto &name : found_layer_names) {
    layer_names.push_back(name.data());
  }

  const auto found_extension_names = vkutils::find_instance_extensions(
      {VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME});

  std::vector<const char *> extension_names{};
  for (const auto &name : found_extension_names) {
    extension_names.emplace_back(name.data());
  }

  const auto instance = vk::createInstance({{},
                                            &app_info,
                                            layer_names.size(),
                                            layer_names.data(),
                                            extension_names.size(),
                                            extension_names.data()});

  const auto hwnd = win32::create_window();
  const auto surface =
      instance.createWin32SurfaceKHR({{}, win32::get_hinstance(), hwnd});

  win32::show_window(hwnd);
  while (win32::process_messages()) {
  }

  instance.destroySurfaceKHR(surface);
  instance.destroy();
}
