
#include <android/log.h>
#include <android/native_window_jni.h>
#include <android/asset_manager_jni.h>
#include "VulkanInstanceAndroid.h"

VulkanInstanceAndroid *vulkanInstance = NULL;

extern "C" {

JNIEXPORT void JNICALL
Java_vk_VulkanTemplate_nativeCreate(JNIEnv *env, jobject vulkanTemplate,
                                    jobject surface, jobject pAssetManager) {
    if (vulkanInstance) {
        delete vulkanInstance;
        vulkanInstance = NULL;
    }
    __android_log_print(ANDROID_LOG_DEBUG, "vulkanTemplate", "create");
    auto window = ANativeWindow_fromSurface(env, surface);
    auto assetManager = AAssetManager_fromJava(env, pAssetManager);
    vulkanInstance = new VulkanInstanceAndroid(assetManager, window);
}

JNIEXPORT void JNICALL
Java_vk_VulkanTemplate_nativeDestroy(JNIEnv *env, jobject vulkanTemplate) {
    __android_log_print(ANDROID_LOG_DEBUG, "vulkanTemplate", "destroy");
    if (vulkanInstance) {
        delete vulkanInstance;
        vulkanInstance = NULL;
    }
}

JNIEXPORT void JNICALL
Java_vk_VulkanTemplate_nativeResize(JNIEnv *env, jobject vulkanTemplate, jint width, jint height) {
    __android_log_print(ANDROID_LOG_DEBUG, "vulkanTemplate", "resize: %dx%d", width, height);
    if (vulkanInstance) {
        vulkanInstance->setSize(width, height);
    }
}

JNIEXPORT void JNICALL
Java_vk_VulkanTemplate_nativeDraw(JNIEnv *env, jobject vulkanTemplate) {
    __android_log_print(ANDROID_LOG_DEBUG, "vulkanTemplate", "draw");
    if (vulkanInstance) {
        vulkanInstance->drawFrame();
    }
}
}