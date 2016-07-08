package com.jni.jni;

public class Jni {
	public static native String stTst();
	static{
		System.loadLibrary("JNI");
	}
	public native String tst();
}
