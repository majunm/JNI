#include <jni.h>
#include <stdio.h>
#include <string.h>
#include "mlog.h"
// 定义c方法:对应java的 stTst();
extern "C" jstring obtainString(JNIEnv* env, jobject thiz);
extern "C" jstring statTst(JNIEnv* env, jobject thiz);
extern "C" jstring tst(JNIEnv* env, jobject thiz);
extern "C" jstring obtainPath(JNIEnv* env, jobject thiz, jobject context);
extern "C" jstring obtainTaskUrl(JNIEnv* env, jobject thiz, jint taskType);
void hello(JNIEnv* env, jobject thiz,jobject context,jint type) {
	LOGE("hello executing..................");
}
//(void*) 指针
JNINativeMethod metheds[] = {
// java方法名,函数签名(参数列表)-返回值,java映射成C世界的方法
		{ "stTst", "()Ljava/lang/String;", (void*) statTst }, { "tst",
				"()Ljava/lang/String;", (void*) tst }, { "obtainStr",
				"()Ljava/lang/String;", (void*) obtainString }, { "obtainPath",
				"(Landroid/content/Context;)Ljava/lang/String;",
				(void*) obtainPath }, { "obtainTaskUrl",
				"(I)Ljava/lang/String;", (void*) obtainTaskUrl },{
						"hel","(Landroid/content/Context;I)V",(void*) hello
				} };
jstring statTst(JNIEnv* env, jobject thiz) {
	return env->NewStringUTF("静态方法返回的string");
}
jstring tst(JNIEnv* env, jobject thiz) {
	return env->NewStringUTF("非静态方法返回的string");
}
jstring obtainString(JNIEnv* env, jobject thiz) {
	return env->NewStringUTF("非静态方法obtainString");
}
jstring obtainTaskUrl(JNIEnv* env, jobject thiz, jint taskType) {
	const char* bytes;
	switch (taskType) {
	case 1:
		bytes = "http://www.fanjie.test1";
		break;
	case 2:
		bytes = "http://www.fanjie.test2";
		break;
	case 3:
		bytes = "http://www.fanjie.test3";
		break;
	default:
		bytes = "http://www.fanjie.com.default";
		break;
	}
	return env->NewStringUTF(bytes);
}
jstring obtainPath(JNIEnv* env, jobject thiz, jobject context) {
	jclass clazz = env->FindClass("android/content/ContextWrapper");
	LOGE("-------obtainPath1---------");
	const char* name = "getFilesDir";
	const char* signature = "()Ljava/io/File;";
	jmethodID method = env->GetMethodID(clazz, name, signature);
	LOGE("-------obtainPath11---------");
	jobject jFile = env->CallObjectMethod(context, method);
	LOGE("-------obtainPath222---------");
	jclass fileClazz = env->GetObjectClass(jFile);
	const char* fname = "getAbsolutePath";
	const char* fsignature = "()Ljava/lang/String;";
	LOGE("-------obtainPath2222---------");
	jmethodID fielMethed = env->GetMethodID(fileClazz, fname, fsignature);
	jstring result = (jstring) env->CallObjectMethod(jFile, fielMethed);
	return result;
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
