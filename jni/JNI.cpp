#include <jni.h>
#include <stdio.h>
#include <string.h>
#include "mlog.h"
// 定义c方法:对应java的 stTst();
//extern "C" void staticTst(JNIEnv* env, jobject thiz);
extern "C" jstring statTst(JNIEnv* env, jobject thiz);
extern "C" jstring tst(JNIEnv* env, jobject thiz);
//(void*) 指针
JNINativeMethod metheds[] = {
// java方法名,函数签名(参数列表)-返回值,java映射成C世界的方法
		{ "stTst", "()Ljava/lang/String;", (void*) statTst }, { "tst",
				"()Ljava/lang/String;", (void*) tst } };
jstring statTst(JNIEnv* env, jobject thiz) {
	return env->NewStringUTF("静态方法返回的string");
}
jstring tst(JNIEnv* env, jobject thiz) {
	return env->NewStringUTF("非静态方法返回的string");
}
jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	jint result = JNI_ERR;
	JNIEnv* env = NULL;
	if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
		LOGE("-------4---------");
		return result;
	}
	jclass clazz = env->FindClass("com/jni/jni/Jni");
	if (clazz == NULL) {
		LOGE("-------1---------");
		return result;
	}
	if (env->RegisterNatives(clazz, metheds,
			sizeof(metheds) / sizeof(metheds[0])) < 0) {
		LOGE("-------2---------");
		return result;
	}
	result = JNI_VERSION_1_4;
	LOGE("-------3=ok---------");
	return result;
}
