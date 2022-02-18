
#include <android/log.h>
#include <android/native_window_jni.h>
#include <android/asset_manager_jni.h>
#include "VulkanInstance.h"

VulkanInstance *vulkanInstance = NULL;

extern "C" {

JNIEXPORT void JNICALL
Java_vk_VulkanAppBridge_nativeCreate(JNIEnv *env, jobject vulkanAppBridge,
        jobject surface, jobject pAssetManager) {
if (vulkanInstance) {
delete vulkanInstance;
    vulkanInstance = NULL;
}
__android_log_print(ANDROID_LOG_DEBUG, "mc-native-VulkanAppBridge", "create");
auto window = ANativeWindow_fromSurface(env, surface);
auto assetManager = AAssetManager_fromJava(env, pAssetManager);
    vulkanInstance = new VulkanInstance(assetManager, window);
}

JNIEXPORT void JNICALL
Java_vk_VulkanAppBridge_nativeDestroy(JNIEnv *env, jobject vulkanAppBridge) {
__android_log_print(ANDROID_LOG_DEBUG, "mc-native-VulkanAppBridge", "destroy");
if (vulkanInstance) {
delete vulkanInstance;
    vulkanInstance = NULL;
}
}

JNIEXPORT void JNICALL
Java_vk_VulkanAppBridge_nativeResize(JNIEnv *env, jobject vulkanAppBridge, jint width, jint height) {
__android_log_print(ANDROID_LOG_DEBUG, "mc-native-VulkanAppBridge", "resize: %dx%d", width, height);
if (vulkanInstance) {
vulkanInstance->setSize(width, height);
    vulkanInstance->isResizeNeeded = true;
}
}

JNIEXPORT void JNICALL
Java_vk_VulkanAppBridge_nativeDraw(JNIEnv *env, jobject vulkanAppBridge) {
__android_log_print(ANDROID_LOG_DEBUG, "mc-native-VulkanAppBridge", "draw");
if (vulkanInstance) {
vulkanInstance->drawFrame();
}
}
}