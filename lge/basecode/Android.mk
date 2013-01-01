LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := basecode_static

LOCAL_MODULE_FILENAME := libbasecode

define all-cpp-files-under
$(patsubst ./%,%, $(shell find $(LOCAL_PATH) -name "*.cpp" -and -not -name ".*"))
endef

define all-subdir-cpp-files
$(call all-cpp-files-under,.)
endef

CPP_FILE_LIST := $(call all-subdir-cpp-files)
LOCAL_SRC_FILES := $(CPP_FILE_LIST:$(LOCAL_PATH)/%=%)   
               
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
                                                     
LOCAL_C_INCLUDES := $(LOCAL_PATH)            
          
include $(BUILD_STATIC_LIBRARY)
