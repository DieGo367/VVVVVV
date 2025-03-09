# change settings to target the ARM7 CPU
# this could potentially be adapted to add real ARM7 support to BlocksDS's CMake files, but not as it is now
set(ARCH_FLAGS "-mcpu=arm7tdmi")
if(NDS_ARCH_THUMB)
    set(ARCH_FLAGS "${ARCH_FLAGS} -mthumb")
endif()
set(CMAKE_C_FLAGS "${ARCH_FLAGS} -ffunction-sections -fdata-sections -D__NDS__ -DARM7")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_C_STANDARD_LIBRARIES "-Wl,--start-group -lnds7d -lc -Wl,--end-group")
else()
	set(CMAKE_C_STANDARD_LIBRARIES "-Wl,--start-group -lnds7 -lc -Wl,--end-group")
endif()
set(LINK_LIBDIRS "-L${BLOCKSDS}/libs/maxmod/lib -L${BLOCKSDS}/libs/libnds/lib")
set(CMAKE_EXE_LINKER_FLAGS "${ARCH_FLAGS} ${LINK_LIBDIRS} -specs=${BLOCKSDS}/sys/crts/ds_arm7.specs")

add_executable(VVVVVV_ARM7 main.c)
target_link_libraries(VVVVVV_ARM7 -lmm7)
target_compile_definitions(VVVVVV_ARM7 PRIVATE USE_MAXMOD)