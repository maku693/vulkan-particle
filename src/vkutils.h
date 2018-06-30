#include <set>
#include <string_view>
#include <vulkan/vulkan.hpp>

namespace vkutils {

std::set<std::string_view>
find_instance_layers(const std::set<std::string_view> &);

std::set<std::string_view>
find_instance_extensions(const std::set<std::string_view> &);

} // namespace vkutils
