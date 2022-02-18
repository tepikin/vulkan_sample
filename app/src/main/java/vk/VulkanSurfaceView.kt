package vk

import android.content.Context
import android.util.AttributeSet
import android.view.SurfaceHolder
import android.view.SurfaceView


class VulkanSurfaceView: SurfaceView, SurfaceHolder.Callback2 {

    interface IVulkanRenderer {
        fun draw(holder: SurfaceHolder)
        fun create(holder: SurfaceHolder)
        fun destroy(holder: SurfaceHolder)
        fun resize(holder: SurfaceHolder, width: Int, height: Int)
    }

    var vulkanRenderer :IVulkanRenderer? =null

    constructor(context: Context): super(context) {
    }

    constructor(context: Context, attrs: AttributeSet): super(context, attrs) {
    }

    constructor(context: Context, attrs: AttributeSet, defStyle: Int): super(context, attrs, defStyle) {
    }

    constructor(context: Context, attrs: AttributeSet, defStyle: Int, defStyleRes: Int): super(context, attrs, defStyle, defStyleRes) {
    }

    init {
        alpha = 1F
        holder.addCallback(this)
    }

    private fun requireRender()=vulkanRenderer?:throw IllegalArgumentException("vulkanRenderer not setted")

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
        requireRender().resize(holder,width, height)
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
        requireRender().destroy(holder)
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
        requireRender().create(holder)
    }

    override fun surfaceRedrawNeeded(holder: SurfaceHolder) {
        requireRender().draw(holder)
    }
}