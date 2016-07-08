LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_LDLIBS    := -lm -llog -landroid
LOCAL_MODULE    := JNI
LOCAL_SRC_FILES := JNI.cpp

include $(BUILD_SHARED_LIBRARY)
