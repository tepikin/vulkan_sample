#include "VulkanInstance.h"
#include <android/asset_manager.h>
#include <android/native_window.h>
#include <jni.h>
#include <android/log.h>

// Android log function wrappers
static const char *kTAG = "Vulkan-template";
#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, kTAG, __VA_ARGS__))
#define LOGW(...) \
  ((void)__android_log_print(ANDROID_LOG_WARN, kTAG, __VA_ARGS__))
#define LOGE(...) \
  ((void)__android_log_print(ANDROID_LOG_ERROR, kTAG, __VA_ARGS__))
#define LOGD(...) \
  ((void)__android_log_print(ANDROID_LOG_DEBUG, kTAG, __VA_ARGS__))


class VulkanInstanceAndroid :public VulkanInstance{

public:
    VulkanInstanceAndroid(AAssetManager *assetManager, ANativeWindow *window) {
        mAssetManager = assetManager;
        mWindow = window;
        initialize();
    }

    ~VulkanInstanceAndroid() {
        terminate();
    }

    void log(const char* fmt, ...){
        //LOGE(&fmt);
    }

    FileData readFile(const char* filePath){
        AAsset* file = AAssetManager_open(mAssetManager, filePath, AASSET_MODE_BUFFER);
        size_t fileLength = AAsset_getLength(file);

        char* fileContent = new char[fileLength];
        AAsset_read(file, fileContent, fileLength);

        struct FileData fileData = { fileContent,fileLength };
        return fileData;
    }


    void createSurface() {
        //crate surface for current platform
        // if we create a surface, we need the surface extension
        VkAndroidSurfaceCreateInfoKHR createInfo{
                .sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR,
                .pNext = nullptr,
                .flags = 0,
                .window = mWindow};
        if (vkCreateAndroidSurfaceKHR(instance, &createInfo, nullptr,
                                      surface.replace()) != VK_SUCCESS) {
            log("failed creating android surface");
        };
    }

    void createInstance() {

        if (isEnabledValidationLayers() && !checkValidationLayerSupport(validationLayers)) {
            log("Validation layers requested, but not available!");
        }


        // createInstance()
        VkApplicationInfo appInfo = {
                .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                .pNext = nullptr,
                .apiVersion = VK_MAKE_VERSION(1, 0, 0),
                .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
                .engineVersion = VK_MAKE_VERSION(1, 0, 0),
                .pApplicationName = "Vulkan Template",
                .pEngineName = "VulkanEngine",
        };



        std::vector<const char *> instanceExt;
        instanceExt.push_back("VK_KHR_surface");
        instanceExt.push_back("VK_KHR_android_surface");
        const bool enableValidationLayers = isEnabledValidationLayers();
        if (enableValidationLayers) {
            instanceExt.push_back("VK_EXT_debug_report");
        }

        // Create the Vulkan instance
        VkInstanceCreateInfo instanceCreateInfo{
                .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                .pNext = nullptr,
                .pApplicationInfo = &appInfo,
                .enabledExtensionCount = static_cast<uint32_t>(instanceExt.size()),
                .ppEnabledExtensionNames = instanceExt.data()
        };
        if (enableValidationLayers) {
            instanceCreateInfo.enabledLayerCount = validationLayers.size();
            instanceCreateInfo.ppEnabledLayerNames = validationLayers.data();
        } else {
            instanceCreateInfo.enabledLayerCount = 0;
        }


        if (VK_SUCCESS != (vkCreateInstance(&instanceCreateInfo, nullptr, instance.replace()))) {
            log("Vulkan error. File[%s], line[%d]", __FILE__, __LINE__);
            assert(false);
        }

    }


private:
    AAssetManager *mAssetManager;
    ANativeWindow *mWindow;

};


