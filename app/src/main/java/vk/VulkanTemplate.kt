package vk

import android.content.Context
import android.content.res.AssetManager
import android.view.Surface
import android.view.SurfaceHolder

class VulkanTemplate(val context: Context) : VulkanSurfaceView.IVulkanRenderer {

    init {
        System.loadLibrary("vulkan-template")
    }

    private external fun nativeCreate(nativeId: Long,surface: Surface, assetManager: AssetManager): Long
    private external fun nativeDestroy(nativeId: Long)
    private external fun nativeResize(nativeId: Long, width: Int, height: Int)
    private external fun nativeDraw(nativeId: Long)

    var nativeId = 0L;

    override fun draw(holder: SurfaceHolder) {
        nativeDraw(nativeId)
    }

    override fun create(holder: SurfaceHolder) {
        nativeId = nativeCreate(nativeId,holder.surface, context.resources.assets)
    }

    override fun destroy(holder: SurfaceHolder) {
        nativeDestroy(nativeId)
    }

    override fun resize(holder: SurfaceHolder, width: Int, height: Int) {
        nativeResize(nativeId, width, height)
    }
}