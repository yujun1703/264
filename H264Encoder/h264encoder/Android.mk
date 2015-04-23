LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_LDLIBS += -llog
LOCAL_CFLAGS += -std=gnu99

LOCAL_SRC_FILES +=      \
				common/cpu.c	\
				common/bitstream.c	\
				common/cabac_com.c		\
				common/common.c	\
				common/macroblock_com.c	\
				common/dct.c		\
				common/deblock.c	\
				common/frame.c		\
				common/mc.c	\
				common/mvpred.c	\
				common/osdep.c		\
				common/pixel.c	\
				common/predict.c	\
				common/quant.c	\
				common/threadpool.c	\
				common/rectangle.c	\
				common/set_com.c	\
				common/vlc.c	\
common/arm/mc-c.c \
common/arm/predict-c.c\
encoder/analyse.c          \
encoder/macroblock.c       \
encoder/me.c               \
encoder/encoder.c          \
encoder/ratecontrol.c      \
encoder/lookahead.c        \
encoder/set.c              \
encoder/cabac.c         \
encoder/cavlc.c         \


LOCAL_CFLAGS += -DANDROID

LOCAL_CFLAGS += -mfpu=neon  -march=armv7-a  -mfloat-abi=softfp

# This is the target being built.
LOCAL_MODULE:= libH264Encoder

LOCAL_MODULE_CLASS := STATIC_LIBRARIES
intermediates := $(call local-intermediates-dir)

LOCAL_SRC_FILES  += \
    common/arm/asm.S                                                        \
    common/arm/cpu-a.S                                                      \
    common/arm/dct-a.S                                                      \
    common/arm/deblock-a.S                                                  \
    common/arm/mc-a.S                                                       \
    common/arm/pixel-a.S                                                    \
    common/arm/predict-a.S                                                  \
    common/arm/quant-a.S                                                    \


# All the assembly sources must be converted from ADS to GAS compatible format
VPX_GEN := $(addprefix $(intermediates)/, $(ASM_FILES))
$(VPX_GEN) : PRIVATE_PATH := $(LOCAL_PATH)
$(VPX_GEN) : PRIVATE_CUSTOM_TOOL = cat $< | perl external/libvpx/build/make/ads2gas.pl > $@
$(VPX_GEN) : $(intermediates)/%.S : $(LOCAL_PATH)/%.asm
	$(transform-generated-source)

LOCAL_GENERATED_SOURCES += $(VPX_GEN)

LOCAL_C_INCLUDES += \
    $(JNI_H_INCLUDE)\
    $(LOCAL_PATH)/                                  \
    $(LOCAL_PATH)/common                            \
    $(LOCAL_PATH)/encoder                           \
    $(LOCAL_PATH)/extras                           
    
# No specia compiler flags.
LOCAL_CFLAGS +=

# Link libs (ex logs)
LOCAL_LDLIBS := -llog

# Don't prelink this library.  For more efficient code, you may want
# to add this library to the prelink map and set this to true.
LOCAL_PRELINK_MODULE := false

include $(BUILD_STATIC_LIBRARY) 
#include $(BUILD_SHARED_LIBRARY) 
