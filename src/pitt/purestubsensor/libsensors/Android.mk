# Copyright (C) 2019 Boyuan Yang <by.yang@pitt.edu>
#
# All Rights Reserved.

# Pure Stub Sensor - provides fake sensor data to the system

LOCAL_PATH := $(call my-dir)

# HAL module implemenation, not prelinked, and stored in
# hw/<SENSORS_HARDWARE_MODULE_ID>.<ro.product.board>.so
include $(CLEAR_VARS)

LOCAL_MODULE := sensors.purestubsensor

LOCAL_MODULE_RELATIVE_PATH := hw

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := \
    -DLOG_TAG=\"Sensors\" \
    -Wall

LOCAL_SRC_FILES := \
    purestubsensors.cpp \
    sensors.cpp

LOCAL_SHARED_LIBRARIES := liblog

include $(BUILD_SHARED_LIBRARY)
