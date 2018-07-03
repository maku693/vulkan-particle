#include <cstddef>
#include <optional>
#include <set>
#include <string_view>
#include <vector>
#include <vulkan/vulkan.hpp>

namespace vkutils {

std::optional<ptrdiff_t> queue_family_index_by_queue_flags(
    const std::vector<vk::QueueFamilyProperties> &, const vk::QueueFlags);

std::optional<ptrdiff_t>
present_queue_family(const std::vector<vk::QueueFamilyProperties> &,
                     const vk::PhysicalDevice &, const vk::SurfaceKHR &);

} // namespace vkutils
