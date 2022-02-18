package vk

import android.content.Context
import android.content.res.AssetManager
import android.view.Surface
import android.view.SurfaceHolder

class VulkanTemplate(val context:Context): VulkanSurfaceView.IVulkanRenderer {

    init {
        System.loadLibrary("vulkan-template")
    }

    private external fun nativeCreate(surface: Surface, assetManager: AssetManager)
    private external fun nativeDestroy()
    private external fun nativeResize(width: Int, height: Int)
    private external fun nativeDraw()

    override fun draw(holder: SurfaceHolder) {
        nativeDraw()
    }

    override fun create(holder: SurfaceHolder) {
        nativeCreate(holder.surface,context.resources.assets)
    }
    
    override fun destroy(holder: SurfaceHolder) {
        nativeDestroy()
    }

    override fun resize(holder: SurfaceHolder, width: Int, height: Int) {
        nativeResize(width, height)
    }
}