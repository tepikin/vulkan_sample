#include "vulkan_wrapper.h"
#include <android_native_app_glue.h>
VkResult createShaderModule(AAssetManager* assetManager, VkDevice  device, const char* filePath, VkShaderModule* shaderOut);
