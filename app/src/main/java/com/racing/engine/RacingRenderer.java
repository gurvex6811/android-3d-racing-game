package com.racing.engine;

import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class RacingRenderer implements GLSurfaceView.Renderer {
    private AssetManager assetManager;
    private long lastFrameTime;

    public RacingRenderer(AssetManager assetManager) {
        this.assetManager = assetManager;
        this.lastFrameTime = System.currentTimeMillis();
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        nativeInit(assetManager);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        nativeResize(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        long currentTime = System.currentTimeMillis();
        float deltaTime = (currentTime - lastFrameTime) / 1000.0f;
        lastFrameTime = currentTime;
        
        nativeUpdate(deltaTime);
        nativeRender();
    }

    // Native methods
    private native void nativeInit(AssetManager assetManager);
    private native void nativeResize(int width, int height);
    private native void nativeUpdate(float deltaTime);
    private native void nativeRender();
}