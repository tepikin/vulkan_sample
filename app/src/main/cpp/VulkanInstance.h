#include <android/asset_manager.h>
#include <android/native_window.h>
#include "main.cpp"

class VulkanInstance  {

public:
    VulkanInstance(AAssetManager* assetManager, ANativeWindow* window) {
        mAssetManager = assetManager;
        mWindow = window;
        initialize(assetManager,window);
    }
    ~VulkanInstance() {
        // ... Vulkan cleanup code.
        terminate();
    }

    void drawFrame() {
        onDrawFrame();
    }


    void setSize(uint32_t w, uint32_t h) {
        width = w;
        height = h;
    }
    bool isResizeNeeded;
private:
    AAssetManager* mAssetManager;
    ANativeWindow* mWindow;
    uint32_t width;
    uint32_t height;
};
