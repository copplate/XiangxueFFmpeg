package com.wwyc.ffmpegpdfxiangxue

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.Surface
import android.view.SurfaceHolder
import android.view.SurfaceView
import android.widget.Toast
import java.io.File

class FFmpegActivity : AppCompatActivity() {
    private lateinit var sfv: SurfaceView

    // 指针改用 0L 初始化（对应 C++ 的 NULL/nullptr）
    private var player: Long = 0L
    // 动态拼接的视频路径
    private var path: String = ""

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_ffmpeg)
        sfv = findViewById<SurfaceView>(R.id.sfv)

        // 1. 查看当前的 API 版本
        val apiVersion = android.os.Build.VERSION.SDK_INT
        Log.d("FFmpegNative", "当前设备的 Android API 版本是: $apiVersion (Android 7.1 对应 25)")

        // 2. 在沙盒内新建一个名为 "videos" 的空白文件夹
        // getExternalFilesDir(null) 获取到的路径就是: /sdcard/Android/data/com.wwyc.ffmpegpdfxiangxue/files
        val videoFolder = File(getExternalFilesDir(null), "videos")
        if (!videoFolder.exists()) {
            val isCreated = videoFolder.mkdirs()
            Log.d("FFmpegNative", "文件夹 [videos] 创建结果: $isCreated")
        }

        // 3. 拼接出视频文件的绝对路径
        val videoFile = File(videoFolder, "video.mp4")
        path = videoFile.absolutePath

        // 4. 打印绝对路径到 Logcat，方便你用电脑导入视频
        Log.e("FFmpegNative", "====================================================")
        Log.e("FFmpegNative", "请把你的视频重命名为 video.mp4 并放到以下路径：")
        Log.e("FFmpegNative", path)
        Log.e("FFmpegNative", "====================================================")

        Toast.makeText(this, "路径已打印到 Logcat，请查看", Toast.LENGTH_LONG).show()

        initSfv()
    }

    private fun initSfv() {
        sfv.holder.addCallback(object : SurfaceHolder.Callback {
            override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {}
            override fun surfaceDestroyed(holder: SurfaceHolder) {}

            override fun surfaceCreated(holder: SurfaceHolder) {
                // 5. 修正原代码的 null 判断错误。0L 代表还没创建 player 实例
                if (player == 0L) {
                    player = createPlayer(path, holder.surface)
                    if (player != 0L) {
                        play(player)
                    } else {
                        Log.e("FFmpegNative", "播放器创建失败，请检查 C++ 底层或视频路径！")
                    }
                }
            }
        })
    }

    private external fun createPlayer(path: String, surface: Surface): Long
    private external fun play(player: Long)
    private external fun pause(player: Long)

    companion object {
        init {
            System.loadLibrary("ffmpegpdfxiangxue")
        }
    }
}