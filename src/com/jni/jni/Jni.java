package com.jni.jni;

import android.content.Context;

public class Jni {
	public static native String stTst();
	static{
		System.loadLibrary("JNI");
	}
	public native String tst();
	public native String obtainStr();
	public native String obtainPath(Context context);
	public native String obtainTaskUrl(int type);
	public native void hel(Context context,int type);
}
