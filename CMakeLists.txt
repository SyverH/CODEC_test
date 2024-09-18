cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(CODEC_test)

target_sources(app PRIVATE src/main.c)

# Exclude files with main function
list(APPEND EXCLUDE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/inc/opus/celt/dump_modes/dump_modes.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/inc/opus/src_c/opus_compare.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/inc/opus/src_c/opus_demo.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/inc/opus/src_c/repacketizer_demo.c"
)

FILE(GLOB audio_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/opus/*.c

    ${CMAKE_CURRENT_SOURCE_DIR}/inc/opus/celt/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/opus/celt/arm/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/opus/celt/dump_modes/*.c

    ${CMAKE_CURRENT_SOURCE_DIR}/inc/opus/silk/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/opus/silk/arm/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/opus/silk/fixed/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/opus/silk/fixed/arm/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/opus/silk/float/*.c

    ${CMAKE_CURRENT_SOURCE_DIR}/inc/opus/libc_opus/*.c

    ${CMAKE_CURRENT_SOURCE_DIR}/inc/opus/src_c/*.c
    )

foreach(file ${EXCLUDE_FILES})
    list(REMOVE_ITEM audio_sources ${file})
endforeach()

target_sources(app PRIVATE ${audio_sources})

target_include_directories(app PRIVATE
    inc/opus
    inc/opus/libc_opus
    inc/opus/include
    inc/opus/celt
    inc/opus/celt/arm
    inc/opus/celt/dump_modes
    inc/opus/silk
    inc/opus/silk/arm
    inc/opus/silk/fixed
    inc/opus/silk/fixed/arm
    inc/opus/silk/float
    ${ZEPHYR_NRF_MODULE_DIR}/boards/arm/nrf5340_audio_dk_nrf5340
)


# For OPUS
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} \
-DARM_MATH_CM4 \
-DUSE_ALLOCA \
-DHAVE_LRINT \
-DHAVE_LRINTF \
-DCUSTOM_SUPPORT \
-DVAR_ARRAYS \
-DOPUS_BUILD \
-DHAVE_CONFIG_H \
-g \
-mfpu=fpv5-sp-d16 \
-mfloat-abi=hard \
-mcpu=cortex-m33 \
-mthumb \
")