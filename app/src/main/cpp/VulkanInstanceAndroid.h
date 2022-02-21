#include "TemplateRender.h"
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

    virtual FileData readFile(const char* filePath){
        AAsset* file = AAssetManager_open(mAssetManager, filePath, AASSET_MODE_BUFFER);
        size_t fileLength = AAsset_getLength(file);

        char* fileContent = new char[fileLength];
        AAsset_read(file, fileContent, fileLength);

        struct FileData fileData = { fileContent,fileLength };
        return fileData;
    }

private:
    AAssetManager *mAssetManager;
    ANativeWindow *mWindow;

};


