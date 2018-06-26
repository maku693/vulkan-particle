#include "win32.h"
#include <Windows.h>
#include <algorithm>
#include <iterator>
#include <string>
#include <string_view>
#include <vector>
#include <vulkan/vulkan.hpp>

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  vk::ApplicationInfo app_info{nullptr, 0, nullptr, 0, VK_VERSION_1_1};

  std::vector<std::string_view> desired_layer_names{
      "VK_LAYER_LUNARG_standard_validation"};
  std::sort(desired_layer_names.begin(), desired_layer_names.end());

  const auto layer_props = vk::enumerateInstanceLayerProperties();
  std::vector<std::string_view> available_layer_names{};
  std::transform(layer_props.cbegin(), layer_props.cend(),
                 std::back_inserter(available_layer_names),
                 [](const auto &x) { return x.layerName; });
  std::sort(available_layer_names.begin(), available_layer_names.end());

  std::vector<std::string_view> found_layer_names{};
  std::set_intersection(
      desired_layer_names.cbegin(), desired_layer_names.cend(),
      available_layer_names.cbegin(), available_layer_names.cend(),
      std::back_inserter(found_layer_names));

  std::vector<const char *> layer_names{};
  layer_names.reserve(found_layer_names.size());
  for (const auto &name : found_layer_names) {
    layer_names.emplace_back(name.data());
  }

  std::vector<std::string_view> desired_extension_names{
      VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME};
  std::sort(desired_extension_names.begin(), desired_extension_names.end());

  const auto extension_props = vk::enumerateInstanceExtensionProperties();
  std::vector<std::string_view> available_extension_names{};
  std::transform(extension_props.cbegin(), extension_props.cend(),
                 std::back_inserter(available_extension_names),
                 [](const auto &x) { return x.extensionName; });
  std::sort(available_extension_names.begin(), available_extension_names.end());

  std::vector<std::string_view> found_extension_names{};
  std::set_intersection(
      desired_extension_names.cbegin(), desired_extension_names.cend(),
      available_extension_names.cbegin(), available_extension_names.cend(),
      std::back_inserter(found_extension_names));

  std::vector<const char *> extension_names{};
  extension_names.reserve(found_extension_names.size());
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
  win32::show_window(hwnd);
  while (win32::process_messages()) {
  }

  instance.destroy();
}
