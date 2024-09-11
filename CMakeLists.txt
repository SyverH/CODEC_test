cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(CODEC_test)

target_sources(app PRIVATE src/main.c)

target_include_directories(app PRIVATE
    inc/opus
    inc/opus/libc_opus
    inc/opus/src
    inc/opus/include
    inc/opus/celt
    inc/opus/celt/arm
    inc/opus/silk
    inc/opus/silk/arm
    inc/opus/silk/fixed
    inc/opus/silk/fixed/arm
    inc/opus/silk/fixed/mips
    inc/opus/silk/float
    inc/opus/silk/float/arm
    inc/opus/silk/mips
    ${ZEPHYR_NRF_MODULE_DIR}/boards/arm/nrf5340_audio_dk_nrf5340
    )

FILE(GLOB SRC_FILES
    "inc/opus/*.c"
    "inc/opus/libc_opus/*.c"
    "inc/opus/src/*.c"
    "inc/opus/include/*.c"
    "inc/opus/celt/*.c"
    "inc/opus/celt/arm/*.c"
    "inc/opus/silk/*.c"
    "inc/opus/silk/arm/*.c"
    "inc/opus/silk/fixed/*.c"
    "inc/opus/silk/fixed/arm/*.c"
    "inc/opus/silk/fixed/mips/*.c"
    "inc/opus/silk/float/*.c"
    "inc/opus/silk/float/arm/*.c"
    "inc/opus/silk/mips/*.c"
    )

target_sources(app PRIVATE ${SRC_FILES})

#-DFIXED_POINT \
# For OPUS
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} \
-DARM_MATH_CM4 \
-DDISABLE_FLOAT_API \
-DUSE_ALLOCA \
-DHAVE_LRINT \
-DHAVE_LRINTF \
-DOPUS_ARM_ASM \
-DOPUS_ARM_INLINE_EDSP \
-DOPUS_ARM_INLINE_MEDIA \
-DOPUS_ARM_MAY_HAVE_EDSP \
-DOPUS_ARM_PRESUME_EDSP \
-DCUSTOM_SUPPORT \
-DVAR_ARRAYS \
-DOPUS_BUILD \
-DHAVE_CONFIG_H \
-g \
-mfpu=neon \
-mfloat-abi=hard \
")
