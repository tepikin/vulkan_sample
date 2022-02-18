#include "vulkan_wrapper.h"
#include <android/asset_manager.h>
VkResult createShaderModule(AAssetManager* assetManager, VkDevice  device, const char* filePath, VkShaderModule* shaderOut);
