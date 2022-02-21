
#include <android/log.h>
#include <android/native_window_jni.h>
#include <android/asset_manager_jni.h>
#include "VulkanInstanceAndroid.h"


extern "C" {

JNIEXPORT jlong JNICALL
Java_vk_VulkanTemplate_nativeCreate(JNIEnv *env, jobject vulkanTemplate,
                                    jlong vulkanInstancePointer,
                                    jobject surface, jobject pAssetManager) {
    VulkanInstanceAndroid *vulkanInstance = (VulkanInstanceAndroid *) vulkanInstancePointer;
    if (vulkanInstance) {
        delete vulkanInstance;
        vulkanInstance = NULL;
    }
    __android_log_print(ANDROID_LOG_DEBUG, "vulkanTemplate", "create");
    auto window = ANativeWindow_fromSurface(env, surface);
    auto assetManager = AAssetManager_fromJava(env, pAssetManager);
    vulkanInstance = new VulkanInstanceAndroid(assetManager, window);
    return (int64_t) vulkanInstance;
}

JNIEXPORT void JNICALL
Java_vk_VulkanTemplate_nativeDestroy(JNIEnv *env, jobject vulkanTemplate,
                                     jlong vulkanInstancePointer) {
    __android_log_print(ANDROID_LOG_DEBUG, "vulkanTemplate", "destroy");
    VulkanInstanceAndroid *vulkanInstance = (VulkanInstanceAndroid *) vulkanInstancePointer;
    if (vulkanInstance) {
        delete vulkanInstance;
        vulkanInstance = NULL;
    }
}

JNIEXPORT void JNICALL
Java_vk_VulkanTemplate_nativeResize(JNIEnv *env, jobject vulkanTemplate,
                                    jlong vulkanInstancePointer, jint width, jint height) {
    __android_log_print(ANDROID_LOG_DEBUG, "vulkanTemplate", "resize: %dx%d", width, height);
    VulkanInstanceAndroid *vulkanInstance = (VulkanInstanceAndroid *) vulkanInstancePointer;
    if (vulkanInstance) {
        vulkanInstance->setSize(width, height);
    }
}

JNIEXPORT void JNICALL
Java_vk_VulkanTemplate_nativeDraw(JNIEnv *env, jobject vulkanTemplate,
                                  jlong vulkanInstancePointer) {
    __android_log_print(ANDROID_LOG_DEBUG, "vulkanTemplate", "draw");
    VulkanInstanceAndroid *vulkanInstance = (VulkanInstanceAndroid *) vulkanInstancePointer;
    if (vulkanInstance) {
        vulkanInstance->drawFrame();
    }
}
}