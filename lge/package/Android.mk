LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := socket_static

LOCAL_MODULE_FILENAME := libsocket

define all-cpp-files-under
$(patsubst ./%,%, $(shell find $(LOCAL_PATH) -name "*.cpp" -and -not -name ".*"))
endef

define all-subdir-cpp-files
$(call all-cpp-files-under,.)
endef

CPP_FILE_LIST := $(call all-subdir-cpp-files)
LOCAL_SRC_FILES := $(CPP_FILE_LIST:$(LOCAL_PATH)/%=%)   
               
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
                                                     
LOCAL_C_INCLUDES := $(LOCAL_PATH)/ \
                           $(LOCAL_PATH)/Include            
                    
#LOCAL_EXPORT_LDLIBS := -lpthread
#LOCAL_LDLIBS := -lpthread
LOCAL_LDLIBS := -lpthread

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static

            
include $(BUILD_STATIC_LIBRARY)

#$(call import-module,cocos2dx/platform/third_party/android/modules/libxml2)

