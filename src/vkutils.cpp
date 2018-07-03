#include "vkutils.h"
#include <algorithm>
#include <iterator>

namespace vkutils {

std::optional<ptrdiff_t> queue_family_index_by_queue_flags(
    const std::vector<vk::QueueFamilyProperties> &props,
    const vk::QueueFlags flags) {
  const auto found =
      std::find_if(props.cbegin(), props.cend(),
                   [&flags](const auto &x) { return x.queueFlags & flags; });
  if (found == props.cend()) {
    return std::nullopt;
  }
  return std::distance(props.cbegin(), found);
}

std::optional<ptrdiff_t>
present_queue_family(const std::vector<vk::QueueFamilyProperties> &props,
                     const vk::PhysicalDevice &gpu,
                     const vk::SurfaceKHR &surface) {
  int size = props.size();
  for (int i = 0; i < size; i++) {
    if (gpu.getSurfaceSupportKHR(i, surface)) {
      return i;
    }
  }
  return std::nullopt;
}

} // namespace vkutils
