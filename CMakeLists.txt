cmake_minimum_required(VERSION 3.11)

project(vulkan-particle CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

find_package(Vulkan REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME}
    SYSTEM PUBLIC ${Vulkan_INCLUDE_DIRS}
    SYSTEM PUBLIC "${CMAKE_CURRENT_LIST_DIR}/third_party/GSL/include"
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src")

target_link_libraries(${PROJECT_NAME}
    ${Vulkan_LIBRARY})

target_compile_definitions(${PROJECT_NAME} PRIVATE
    "UNICODE"
    "_UNICODE"
    "VK_USE_PLATFORM_WIN32_KHR")
