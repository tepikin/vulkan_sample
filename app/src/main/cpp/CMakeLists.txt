cmake_minimum_required(VERSION 3.4.1)

project("vulkan-template")

add_library(vulkan-template SHARED
        vulkan/vulkan_wrapper.cpp
        vulkan/pipeline.cpp
        vulkan/VDeleter.h
        VulkanInstance.h
        VulkanTemplateAndroid.cpp
        )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -std=c++11 \
                     -DVK_USE_PLATFORM_ANDROID_KHR")

target_link_libraries(vulkan-template log android)

