package code.template.vulkan

import android.os.Bundle

import androidx.appcompat.app.AppCompatActivity

import android.view.View
import android.view.animation.AccelerateDecelerateInterpolator

import vk.VulkanSurfaceView
import vk.VulkanTemplate

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContentView(R.layout.fragment_first)

        var vulkanSurfaceView =  findViewById<VulkanSurfaceView>(R.id.vulkanSurfaceView)
        vulkanSurfaceView.vulkanRenderer = VulkanTemplate(this)
        findViewById<View>(R.id.button_first).setOnClickListener {
            vulkanSurfaceView?.scaleX=1f
            vulkanSurfaceView?.scaleY=1f
            vulkanSurfaceView?.rotation=0f
            vulkanSurfaceView?.translationX=0f
           // vulkanSurfaceView?.alpha=0f

            vulkanSurfaceView?.animate()?.scaleX(0.5f)?.scaleY(0.5f)?.translationX(360f)?.setDuration(1000)?.setInterpolator(AccelerateDecelerateInterpolator())?.withEndAction {
                vulkanSurfaceView?.scaleX=1f
                vulkanSurfaceView?.scaleY=1f
                vulkanSurfaceView?.rotation=0f
                vulkanSurfaceView?.translationX=0f
            //    vulkanSurfaceView?.alpha=0f
            }

                ?.start()
        }

    }


}