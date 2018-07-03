#include "vkutils.h"
#include "win32.h"
#include <Windows.h>
#include <array>
#include <vector>
#include <vulkan/vulkan.hpp>

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  const auto hwnd = win32::create_window();

  vk::ApplicationInfo app_info{nullptr, 0, nullptr, 0, VK_VERSION_1_1};

  const std::vector<const char *> layer_names{
      "VK_LAYER_LUNARG_standard_validation"};

  const std::vector<const char *> extension_names{
      VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME};

  const auto instance = vk::createInstance({{},
                                            &app_info,
                                            layer_names.size(),
                                            layer_names.data(),
                                            extension_names.size(),
                                            extension_names.data()});

  const auto surface =
      instance.createWin32SurfaceKHR({{}, win32::get_hinstance(), hwnd});

  const auto gpu = instance.enumeratePhysicalDevices().front();

  const auto queue_family_props = gpu.getQueueFamilyProperties();

  const auto graphics_queue_family_index =
      vkutils::queue_family_index_by_queue_flags(queue_family_props,
                                                 vk::QueueFlagBits::eGraphics);
  const int graphics_queue_index = 0;

  const auto compute_queue_family_index =
      vkutils::queue_family_index_by_queue_flags(queue_family_props,
                                                 vk::QueueFlagBits::eCompute);
  const int compute_queue_index = 1;

  const auto surface_queue_family_index =
      vkutils::present_queue_family(queue_family_props, gpu, surface);
  const int surface_queue_index = 2;

  std::array<vk::DeviceQueueCreateInfo, 3> queue_create_infos{
      {{{}, graphics_queue_family_index.value(), 1, nullptr},
       {{}, compute_queue_family_index.value(), 1, nullptr},
       {{}, surface_queue_family_index.value(), 1, nullptr}}};

  std::vector<const char *> device_extensions{VK_KHR_SWAPCHAIN_EXTENSION_NAME};

  const auto features = gpu.getFeatures();

  const auto device = gpu.createDevice({{},
                                        queue_create_infos.size(),
                                        queue_create_infos.data(),
                                        0,
                                        nullptr,
                                        device_extensions.size(),
                                        device_extensions.data(),
                                        &features});

  const auto graphics_queue = device.getQueue(
      graphics_queue_family_index.value(), graphics_queue_index);

  const auto compute_queue =
      device.getQueue(compute_queue_family_index.value(), compute_queue_index);

  const auto surface_queue =
      device.getQueue(surface_queue_family_index.value(), surface_queue_index);

  win32::show_window(hwnd);
  while (win32::process_messages()) {
  }

  device.destroy();

  instance.destroySurfaceKHR(surface);
  instance.destroy();
}
