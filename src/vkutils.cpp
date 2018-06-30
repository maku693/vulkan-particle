#include "vkutils.h"
#include <algorithm>
#include <iterator>

namespace vkutils {

std::set<std::string_view>
find_instance_layers(const std::set<std::string_view> &desired) {
  const auto props = vk::enumerateInstanceLayerProperties();
  std::set<std::string_view> available{};
  std::transform(props.cbegin(), props.cend(),
                 std::inserter(available, available.cend()),
                 [](const auto &x) { return x.layerName; });

  std::set<std::string_view> found{};
  std::set_intersection(desired.cbegin(), desired.cend(), available.cbegin(),
                        available.cend(), std::inserter(found, found.cend()));
  return found;
}

std::set<std::string_view>
find_instance_extensions(const std::set<std::string_view> &desired) {
  const auto props = vk::enumerateInstanceExtensionProperties();
  std::set<std::string_view> available{};
  std::transform(props.cbegin(), props.cend(),
                 std::inserter(available, available.cend()),
                 [](const auto &x) { return x.extensionName; });

  std::set<std::string_view> found{};
  std::set_intersection(desired.cbegin(), desired.cend(), available.cbegin(),
                        available.cend(), std::inserter(found, found.cend()));
  return found;
}


} // namespace vkutils
