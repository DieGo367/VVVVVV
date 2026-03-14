# CMake File for VVVVVV
# Written by Ethan "flibitijibibo" Lee

cmake_minimum_required(VERSION 2.8.12...3.5)

# CMake Options
option(ENABLE_WARNINGS "Enable compilation warnings" ON)
option(ENABLE_WERROR "Treat compilation warnings as errors" OFF)

option(BUNDLE_DEPENDENCIES "Use bundled TinyXML-2, PhysicsFS, and FAudio (if disabled, TinyXML-2, PhysicsFS, and FAudio will be dynamically linked; LodePNG, C-HashMap and SheenBidi will still be statically linked)" ON)

option(STEAM "Use the Steam API" OFF)
option(GOG "Use the GOG API" OFF)

option(OFFICIAL_BUILD "Compile an official build of the game" OFF)

option(MAKEANDPLAY "Compile a version of the game without the main campaign (provided for convenience; consider modifying MakeAndPlay.h instead" OFF)

if(OFFICIAL_BUILD AND NOT MAKEANDPLAY)
    set(STEAM ON)
    set(GOG ON)
endif()

option(REMOVE_ABSOLUTE_PATHS "If supported by the compiler, replace all absolute paths to source directories compiled into the binary (if any) with relative paths" ON)


# Architecture Flags
if(APPLE)
    # Wow, Apple is a huge jerk these days huh?
    set(OSX_10_9_SDK_PATH /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk)
    if(NOT CMAKE_OSX_SYSROOT)
        if(IS_DIRECTORY ${OSX_10_9_SDK_PATH})
            set(CMAKE_OSX_SYSROOT ${OSX_10_9_SDK_PATH})
        else()
            message(WARNING "CMAKE_OSX_SYSROOT not set and macOS 10.9 SDK not found! Using default one.")
        endif()
    endif()
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.9)
    link_directories(/usr/local/lib)
    add_compile_options(-Werror=partial-availability)
endif()

project(VVVVVV)

if(APPLE)
    message(STATUS "Using macOS SDK at ${CMAKE_OSX_SYSROOT}")
endif()

# RPATH
if(NOT WIN32)
    if(APPLE)
        set(BIN_LIBROOT "osx")
        set(BIN_RPATH "@executable_path/osx")
    elseif(CMAKE_SIZEOF_VOID_P MATCHES "8")
        set(BIN_LIBROOT "lib64")
        set(BIN_RPATH "\$ORIGIN/lib64")
    else()
        set(BIN_LIBROOT "lib")
        set(BIN_RPATH "\$ORIGIN/lib")
    endif()
    set(CMAKE_SKIP_BUILD_RPATH TRUE)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    set(CMAKE_INSTALL_RPATH ${BIN_RPATH})
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
endif()

# Source Lists
set(VVV_CXX_SRC
    src/BinaryBlob.cpp
    src/BlockV.cpp
    src/ButtonGlyphs.cpp
    src/CustomLevels.cpp
    src/CWrappers.cpp
    src/Editor.cpp
    src/Ent.cpp
    src/Entity.cpp
    src/FileSystemUtils.cpp
    src/Finalclass.cpp
    src/Font.cpp
    src/FontBidi.cpp
    src/Game.cpp
    src/Graphics.cpp
    src/GraphicsResources.cpp
    src/GraphicsUtil.cpp
    src/IMERender.cpp
    src/Input.cpp
    src/KeyPoll.cpp
    src/Labclass.cpp
    src/LevelDebugger.cpp
    src/Localization.cpp
    src/LocalizationMaint.cpp
    src/LocalizationStorage.cpp
    src/Logic.cpp
    src/Map.cpp
    src/Music.cpp
    src/Otherlevel.cpp
    src/preloader.cpp
    src/Render.cpp
    src/RenderFixed.cpp
    src/RoomnameTranslator.cpp
    src/Screen.cpp
    src/Script.cpp
    src/Scripts.cpp
    src/Spacestation2.cpp
    src/TerminalScripts.cpp
    src/Textbox.cpp
    src/Tower.cpp
    src/UtilityClass.cpp
    src/WarpClass.cpp
    src/XMLUtils.cpp
    src/main.cpp
)
set(VVV_C_SRC
    src/DeferCallbacks.c
    src/GlitchrunnerMode.c
    src/Network.c
    src/Textbook.c
    src/TileDecode.c
    src/ThirdPartyDeps.c
    src/UTF8.c
    src/VFormat.c
    src/Vlogging.c
    src/Xoshiro.c
    ../third_party/physfs/extras/physfsrwops.c
)
if(STEAM)
    list(APPEND VVV_C_SRC src/SteamNetwork.c)
endif()
if(GOG)
    list(APPEND VVV_C_SRC src/GOGNetwork.c)
endif()

set(VVV_SRC ${VVV_CXX_SRC} ${VVV_C_SRC})

# Executable information
if(WIN32)
    add_executable(VVVVVV WIN32 ${VVV_SRC} icon.rc)
elseif(ANDROID)
    add_library(VVVVVV SHARED ${VVV_SRC})
else()
    add_executable(VVVVVV ${VVV_SRC})
endif()

# Include Directories
if(BUNDLE_DEPENDENCIES)
    target_include_directories(
        VVVVVV PRIVATE
        src
        ../third_party
        ../third_party/tinyxml2
        ../third_party/physfs/src
        ../third_party/physfs/extras
        ../third_party/lodepng
        ../third_party/c-hashmap
        ../third_party/FAudio/include
        ../third_party/FAudio/src
        ../third_party/SheenBidi/Headers
    )
else()
    target_include_directories(
        VVVVVV PRIVATE
        src
        ../third_party
        ../third_party/lodepng
        ../third_party/physfs/extras
        ../third_party/c-hashmap
        ../third_party/FAudio/src
        ../third_party/SheenBidi/Headers
    )
endif()

if(MAKEANDPLAY)
    target_compile_definitions(VVVVVV PRIVATE -DMAKEANDPLAY)
endif()

if(STEAM)
    target_compile_definitions(VVVVVV PRIVATE -DSTEAM_NETWORK)
endif()
if(GOG)
    target_compile_definitions(VVVVVV PRIVATE -DGOG_NETWORK)
endif()

set(XML2_SRC
    ../third_party/tinyxml2/tinyxml2.cpp
)
set(FAUDIO_SRC
    ../third_party/FAudio/src/FAudio.c
    ../third_party/FAudio/src/FAudio_internal.c
    ../third_party/FAudio/src/FAudio_internal_simd.c
    ../third_party/FAudio/src/FAudio_operationset.c
    ../third_party/FAudio/src/FAudio_platform_sdl2.c
)
set(PFS_SRC
    ../third_party/physfs/src/physfs.c
    ../third_party/physfs/src/physfs_archiver_dir.c
    ../third_party/physfs/src/physfs_archiver_unpacked.c
    ../third_party/physfs/src/physfs_archiver_zip.c
    ../third_party/physfs/src/physfs_byteorder.c
    ../third_party/physfs/src/physfs_unicode.c
    ../third_party/physfs/src/physfs_platform_posix.c
    ../third_party/physfs/src/physfs_platform_unix.c
    ../third_party/physfs/src/physfs_platform_windows.c
    ../third_party/physfs/src/physfs_platform_haiku.cpp
    ../third_party/physfs/src/physfs_platform_android.c
    ../third_party/physfs/src/physfs_platform_nds.c
)
if(APPLE)
    # Are you noticing a pattern with this Apple crap yet?
    set(PFS_SRC ${PFS_SRC} ../third_party/physfs/src/physfs_platform_apple.m)
endif()
set(PNG_SRC src/lodepng_wrapper.c)
set(CHM_SRC ../third_party/c-hashmap/map.c)
set(SBIDI_SRC ../third_party/SheenBidi/Source/SheenBidi.c)

if(NOT OFFICIAL_BUILD)
    # Add interim commit hash and its date to the build

    # These filenames have to be qualified, because when we run
    # the CMake script, its work dir gets set to the build folder
    set(VERSION_INPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/InterimVersion.in.c)
    set(VERSION_OUTPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/InterimVersion.out.c)

    add_custom_command(
        # This OUTPUT line is required for this to be ran every time
        OUTPUT ${VERSION_OUTPUT_FILE} ${CMAKE_CURRENT_SOURCE_DIR}/src/_dummy.c
        COMMAND ${CMAKE_COMMAND}
        # These args have to be passed through, otherwise the script can't see them
        # Also, these args have to come BEFORE `-P`! (Otherwise it fails with an unclear error)
        -DINPUT_FILE=${VERSION_INPUT_FILE}
        -DOUTPUT_FILE=${VERSION_OUTPUT_FILE}
        -P ${CMAKE_CURRENT_SOURCE_DIR}/version.cmake
    )

    target_compile_definitions(VVVVVV PRIVATE -DINTERIM_VERSION_EXISTS)

    add_library(InterimVersion STATIC src/InterimVersion.out.c)
    list(APPEND STATIC_LIBRARIES InterimVersion)
endif()

# Build options
if(ENABLE_WARNINGS)
    # The weird syntax is due to CMake generator expressions.
    # Saves quite a few lines and boilerplate at the price of readability.
    target_compile_options(VVVVVV PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
            -Wall -Wpedantic $<$<BOOL:${ENABLE_WERROR}>:-Werror>>
        $<$<CXX_COMPILER_ID:MSVC>:
            /W4 $<$<BOOL:${ENABLE_WERROR}>:/WX>>)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(SUPPORTS_IMPLICIT_FALLTHROUGH TRUE)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 7.0)
        set(SUPPORTS_IMPLICIT_FALLTHROUGH TRUE)
    else()
        set(SUPPORTS_IMPLICIT_FALLTHROUGH FALSE)
    endif()
else()
    set(SUPPORTS_IMPLICIT_FALLTHROUGH FALSE)
endif()


if(SUPPORTS_IMPLICIT_FALLTHROUGH)
    target_compile_options(VVVVVV PRIVATE -Werror=implicit-fallthrough)
endif()

if(MSVC)
    # Disable MSVC warnings about implicit conversion
    target_compile_options(VVVVVV PRIVATE /wd4244)
endif()

# Disable warnings about `long long` in C++03 (from including PhysFS)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(VVVVVV PRIVATE -Wno-long-long)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(VVVVVV PRIVATE -Wno-c++11-long-long)
endif()

# Disable warnings about flexible array members in C++ (from including FAudio)
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(VVVVVV PRIVATE -Wno-c99-extensions)
endif()

if(MSVC)
    # MSVC doesn't have /std:c99 or /std:c++98 switches!

    # MSVC does not officially support disabling exceptions,
    # so this is as far as we are willing to go to disable them.
    string(REGEX REPLACE "/EH[a-z]+" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set_source_files_properties(${VVV_CXX_SRC} PROPERTIES COMPILE_FLAGS /EHsc)

    # Disable RTTI
    string(REPLACE "/GR" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set_source_files_properties(${VVV_CXX_SRC} PROPERTIES COMPILE_FLAGS /GR-)

    if(MSVC_VERSION GREATER 1900)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /utf-8")
    endif()
else()
    string(REGEX REPLACE "-std=[a-z0-9]+" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    set_source_files_properties(${VVV_C_SRC} PROPERTIES COMPILE_FLAGS -std=c99)

    string(REGEX REPLACE "-std=[a-z0-9+]+" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set_source_files_properties(${VVV_CXX_SRC} PROPERTIES COMPILE_FLAGS -std=c++98)

    # Disable exceptions
    string(REPLACE "-fexceptions" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set_source_files_properties(${VVV_CXX_SRC} PROPERTIES COMPILE_FLAGS -fno-exceptions)

    # Disable RTTI
    string(REPLACE "-frtti" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set_source_files_properties(${VVV_CXX_SRC} PROPERTIES COMPILE_FLAGS -fno-rtti)

    # Dependencies (as needed)
    set_source_files_properties(${FAUDIO_SRC} PROPERTIES COMPILE_FLAGS -std=c99)
    set_source_files_properties(${CHM_SRC} PROPERTIES COMPILE_FLAGS -std=c99)
endif()

# Unfortunately, it doesn't seem like distros package LodePNG
add_library(lodepng-static STATIC ${PNG_SRC})

target_compile_definitions(lodepng-static PRIVATE
    -DLODEPNG_NO_COMPILE_ALLOCATORS
    -DLODEPNG_NO_COMPILE_DISK
)

add_library(c-hashmap-static STATIC ${CHM_SRC})

add_library(sheenbidi-static STATIC ${SBIDI_SRC})

target_compile_definitions(sheenbidi-static PRIVATE
    -DSB_CONFIG_UNITY
)
target_include_directories(sheenbidi-static PRIVATE
    ../third_party/SheenBidi/Headers
)

if(BUNDLE_DEPENDENCIES)
    list(APPEND STATIC_LIBRARIES physfs-static tinyxml2-static lodepng-static c-hashmap-static faudio-static sheenbidi-static)
else()
    list(APPEND STATIC_LIBRARIES lodepng-static c-hashmap-static sheenbidi-static)
endif()

if(BUNDLE_DEPENDENCIES)
    add_library(tinyxml2-static STATIC ${XML2_SRC})
    add_library(physfs-static STATIC ${PFS_SRC})
    if(NINTENDO_DS) # heyyyyy
        # minimize lodepng to just the encoding part
        target_compile_definitions(lodepng-static PRIVATE
            -DLODEPNG_NO_COMPILE_ANCILLARY_CHUNKS
            -DLODEPNG_NO_COMPILE_DECODER
        )
        # don't include zip support in physfs
        target_compile_definitions(physfs-static PRIVATE -DPHYSFS_SUPPORTS_DEFAULT=0)
        # and don't include faudio at all
        list(REMOVE_ITEM STATIC_LIBRARIES faudio-static)
    else()
        target_compile_definitions(physfs-static PRIVATE
            -DPHYSFS_SUPPORTS_DEFAULT=0 -DPHYSFS_SUPPORTS_ZIP=1
        )
        add_library(faudio-static STATIC ${FAUDIO_SRC})
        target_include_directories(
            faudio-static PRIVATE
            ../third_party/FAudio/include
        )
        # Disable FAudio debug stuff in release mode. This needs a generator expression for CMake reasons(TM)
        target_compile_definitions(faudio-static PRIVATE $<$<CONFIG:Release>:FAUDIO_DISABLE_DEBUGCONFIGURATION>)
    endif()
    target_link_libraries(VVVVVV ${STATIC_LIBRARIES})
else()
    target_link_libraries(VVVVVV ${STATIC_LIBRARIES} physfs tinyxml2 FAudio)
endif()


if(MSVC)
    # Statically link Microsoft's runtime library so end users don't have to install it (/MT)
    # Also, build with multiple processors (/MP)
    list(APPEND GLOBAL_COMPILE_FLAGS /MT /MP)
endif()


if(REMOVE_ABSOLUTE_PATHS)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 3.8)
            set(SUPPORTS_DEBUG_PREFIX_MAP TRUE)
        else()
            set(SUPPORTS_DEBUG_PREFIX_MAP FALSE)
        endif()
        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 10.0)
            set(SUPPORTS_FILE_PREFIX_MAP TRUE)
        else()
            set(SUPPORTS_FILE_PREFIX_MAP FALSE)
        endif()
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(SUPPORTS_DEBUG_PREFIX_MAP TRUE)
        if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 8.0)
            set(SUPPORTS_FILE_PREFIX_MAP TRUE)
        else()
            set(SUPPORTS_FILE_PREFIX_MAP FALSE)
        endif()
    else()
        set(SUPPORTS_DEBUG_PREFIX_MAP FALSE)
        set(SUPPORTS_FILE_PREFIX_MAP FALSE)
    endif()

    get_filename_component(REPO_DIR ../ ABSOLUTE)

    # Remove absolute source paths from compiled binary
    if(SUPPORTS_FILE_PREFIX_MAP)
        list(APPEND GLOBAL_COMPILE_FLAGS -ffile-prefix-map=${REPO_DIR}=.)
    elseif(SUPPORTS_DEBUG_PREFIX_MAP)
        list(APPEND GLOBAL_COMPILE_FLAGS -fdebug-prefix-map=${REPO_DIR}=.)
    endif()
endif()


target_compile_options(VVVVVV PRIVATE ${GLOBAL_COMPILE_FLAGS})

foreach(static_library IN LISTS STATIC_LIBRARIES)
    target_compile_options(${static_library} PRIVATE ${GLOBAL_COMPILE_FLAGS})
endforeach(static_library)

if(NINTENDO_DS)
    target_compile_definitions(VVVVVV PRIVATE -Dasm=__asm__) # needed for c99
    target_link_libraries(VVVVVV -lmm9) # add Maxmod
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-exceptions")

    # custom SDL replacement
    add_library(sndsl-static STATIC
        ../third_party/SnDsL/src/main.c
        ../third_party/SnDsL/src/messagebox.c
    )
    target_include_directories(sndsl-static PRIVATE ../third_party/SnDsL/include)
    if(ENABLE_WARNINGS)
        target_compile_options(sndsl-static PRIVATE -Wall)
    endif()
    set(SDL2_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/SnDsL/include)
    set(SDL2_LIBRARIES sndsl-static)

    # tools for preparing nitro files
    find_program(MAGICK magick REQUIRED)
    find_program(FFMPEG ffmpeg REQUIRED)
    find_program(PYTHON NAMES python3 python REQUIRED)
    set(E ${CMAKE_COMMAND} -E)
    set(GRIT ${BLOCKSDS}/tools/grit/grit)
    set(MMUTIL ${BLOCKSDS}/tools/mmutil/mmutil)

    macro(depend_data_files)
        foreach(FILE ${ARGV})
            if (NOT FILE IN_LIST DATA_FILES)
                # filter out any files that aren't actually from the data directory
                string(FIND ${FILE} "data/" IDX)
                if(IDX EQUAL 0)
                    list(APPEND DATA_FILES ${FILE})
                endif()
            endif()
        endforeach()
    endmacro()
    macro(output_nitro_files)
        foreach(FILE ${ARGV})
            if (NOT FILE IN_LIST NITRO_FILES)
                list(APPEND NITRO_FILES ${FILE})
            endif()
        endforeach()
    endmacro()
    macro(add_nitro_file COPY_SOURCE COPY_OUTPUT)
        set(OUT_PATH ${COPY_OUTPUT})
        cmake_path(REMOVE_FILENAME OUT_PATH)
        add_custom_command(
            OUTPUT ${COPY_OUTPUT}
            BYPRODUCTS ${OUT_PATH}
            COMMAND ${E} make_directory ${OUT_PATH}
            COMMAND ${E} copy_if_different ${COPY_SOURCE} ${COPY_OUTPUT}
        )
        depend_data_files(${COPY_SOURCE})
        output_nitro_files(${COPY_OUTPUT})
    endmacro()
    macro(add_nitro_graphic)
        cmake_parse_arguments(IMG "" "SOURCE;OUTPUT" "DEPENDS;MAGICK_ARGS;GRIT_FLAGS" ${ARGV})
        string(REPLACE "nitro/" "prep/" PREP_IMG ${IMG_OUTPUT})
        cmake_path(REPLACE_EXTENSION PREP_IMG ".png")
        cmake_path(REMOVE_FILENAME PREP_IMG OUTPUT_VARIABLE PREP_PATH)
        cmake_path(REMOVE_FILENAME IMG_OUTPUT OUTPUT_VARIABLE OUT_PATH)
        add_custom_command(
            OUTPUT ${IMG_OUTPUT}
            BYPRODUCTS ${PREP_PATH} ${OUT_PATH} ${PREP_IMG}
            DEPENDS ${IMG_SOURCE} ${IMG_DEPENDS}
            COMMAND ${E} make_directory ${PREP_PATH} ${OUT_PATH}
            COMMAND ${MAGICK} ${IMG_SOURCE} ${IMG_MAGICK_ARGS} ${PREP_IMG} VERBATIM
            COMMAND ${GRIT} ${PREP_IMG} ${IMG_GRIT_FLAGS} -o ${IMG_OUTPUT}
        )
        depend_data_files(${IMG_SOURCE} ${IMG_DEPENDS})
        output_nitro_files(${IMG_OUTPUT})
    endmacro()

    set(COMMON_MAGICK_ARGS -background "#FF00FF" -alpha remove)
    set(COMMON_GRIT_FLAGS -ftr -fh! -gT FF00FF)
    set(RESIZE_FLAG -extent "%[fx:2^ceil(log(w)/log(2))]x%[fx:2^ceil(log(h)/log(2))]")

    # instructions to draw star gfx
    set(INSTR_1
        \( +clone -crop 72x24+0+0
            -fill "#FF00FF" -stroke none
                -draw "rectangle 0,0 31,23"
                -draw "rectangle 40,16 71,23"
    )
    # splitting into 2 parts to set a new fill (see below)
    set(INSTR_2
                -draw "rectangle 0,0 1,1"
                -draw "rectangle 10,0 11,1"
                -draw "rectangle 20,0 21,1"
                -draw "rectangle 30,0 31,1"
                
                -draw "rectangle 0,10 1,11"
                -draw "rectangle 10,10 11,11"
                -draw "rectangle 20,10 21,11"
                -draw "rectangle 30,10 31,11"
                
                -draw "rectangle 0,20 1,21"
                -draw "rectangle 10,20 11,21"
                -draw "rectangle 20,20 21,21"
                -draw "rectangle 30,20 31,21"

                -draw "rectangle 40,22 41,23"
                -draw "rectangle 50,22 51,23"
                -draw "rectangle 60,22 61,23"
                -draw "rectangle 70,22 71,23"
        \)
    )
    set(DRAW_STARS
        -repage -104-216 ${INSTR_1} -fill "#555555" ${INSTR_2} -repage +104+216! -flatten
        -repage -176-216 ${INSTR_1} -fill "#222222" ${INSTR_2} -repage +176+216! -flatten
    )

    # tilesets
    add_nitro_graphic(
        SOURCE data/graphics/tiles.png
        OUTPUT nitro/graphics/tiles.grf
        MAGICK_ARGS ${COMMON_MAGICK_ARGS} ${DRAW_STARS}
        GRIT_FLAGS ${COMMON_GRIT_FLAGS} -gt -gB8 -m
    )
    add_nitro_graphic(
        SOURCE data/graphics/tiles2.png
        OUTPUT nitro/graphics/tiles2.grf
        DEPENDS data/graphics/tiles.png
        MAGICK_ARGS
            ${COMMON_MAGICK_ARGS} ${DRAW_STARS}
            # draw some custom tiles for the lab bg
            -fill "rgb(54,26,18)"
                -draw "rectangle 192,96 231,135"
            -fill none -stroke "rgb(215,157,141)" +antialias
                -draw "rectangle 196,100 227,131"
                -draw "rectangle 197,101 226,130"
                -draw "rectangle 200,100 223,131"
                -draw "rectangle 201,101 222,130"
                -draw "rectangle 196,104 227,127"
                -draw "rectangle 197,105 226,126"
            # copy one of the treadmill platforms from the first tileset
            \( data/graphics/tiles.png -crop 32x16+288+0 \) -flatten
        GRIT_FLAGS ${COMMON_GRIT_FLAGS} -gt -gB8 -m
    )
    add_nitro_graphic(
        SOURCE data/graphics/tiles3.png
        OUTPUT nitro/graphics/tiles3.grf
        MAGICK_ARGS ${COMMON_MAGICK_ARGS}
        GRIT_FLAGS ${COMMON_GRIT_FLAGS} -gt -gB8 -m
    )
    # sprite sheets
    foreach(SPRITES sprites flipsprites)
        add_nitro_graphic(
            SOURCE data/graphics/${SPRITES}.png
            OUTPUT nitro/graphics/${SPRITES}.grf
            DEPENDS ${CMAKE_SOURCE_DIR}/nds/sprites_small.png
            MAGICK_ARGS
                -background none ${CMAKE_SOURCE_DIR}/nds/sprites_small.png +append
                -channel RGB -brightness-contrast 100
                ${COMMON_MAGICK_ARGS} ${RESIZE_FLAG}
            GRIT_FLAGS ${COMMON_GRIT_FLAGS} -gb -gB2 -pn2
        )
    endforeach()
    # textures
    foreach(TEXTURE_2BIT
        elephant
        gamecomplete
        levelcomplete
        site site2 site3 site4
        covered
    )
        set(PN $<IF:$<STREQUAL:${TEXTURE_2BIT},covered>,-pn3,-pn2>)
        add_nitro_graphic(
            SOURCE data/graphics/${TEXTURE_2BIT}.png
            OUTPUT nitro/graphics/${TEXTURE_2BIT}.grf
            MAGICK_ARGS ${COMMON_MAGICK_ARGS} ${RESIZE_FLAG}
            GRIT_FLAGS ${COMMON_GRIT_FLAGS} -gb -gB2 ${PN}
        )
    endforeach()
    add_nitro_graphic(
        SOURCE data/graphics/teleporter.png
        OUTPUT nitro/graphics/teleporter.grf
        MAGICK_ARGS
            -background "#FF00FF" -crop 96x96 +repage
            \( -clone 0,1 -flatten \)
            \( -clone 0,2 -flatten \)
            \( -clone 0,3 -flatten \)
            \( -clone 0,4 -flatten \)
            \( -clone 0,5 -flatten \)
            \( -clone 0,6 -flatten \)
            \( -clone 0,7 -flatten \)
            \( -clone 0,8 -flatten \)
            \( -clone 0,9 -flatten \)
            -delete 0-9 +append +repage -crop 480x96 -append ${RESIZE_FLAG}
        GRIT_FLAGS ${COMMON_GRIT_FLAGS} -gb -gB2 -pn3
    )
    add_nitro_graphic(
        SOURCE data/graphics/minimap.png
        OUTPUT nitro/graphics/minimap.grf
        MAGICK_ARGS ${COMMON_MAGICK_ARGS} ${RESIZE_FLAG}
        GRIT_FLAGS ${COMMON_GRIT_FLAGS} -gb -gB8 -pn23
    )
    add_nitro_graphic(
        SOURCE data/graphics/ending.png
        OUTPUT nitro/graphics/ending.grf
        MAGICK_ARGS ${COMMON_MAGICK_ARGS} -filter point -resize 256x192 -extent 256x256
        GRIT_FLAGS ${COMMON_GRIT_FLAGS} -gb -gB4 -pn16
    )
    add_nitro_graphic(
        SOURCE ""
        OUTPUT nitro/graphics/cursors.grf
        MAGICK_ARGS
            -size 16x64 "canvas:#FF00FF"
            -stroke black -fill none +antialias 
            -draw "rectangle 1,1 10,7"
            -draw "rectangle 1,17 10,62"
        GRIT_FLAGS ${COMMON_GRIT_FLAGS} -gt -gB4 -pn2
    )
    add_nitro_graphic(
        SOURCE ""
        OUTPUT nitro/graphics/legend.grf
        DEPENDS ${CMAKE_SOURCE_DIR}/fonts/font.png
        MAGICK_ARGS
            \( ${CMAKE_SOURCE_DIR}/fonts/font.png -crop 8x8+120+472 -repage +0+0 -fill "#454545" +opaque transparent \)
            \( ${CMAKE_SOURCE_DIR}/fonts/font.png -crop 8x8+112+488 -repage +0+8 -fill "#AEFFFF" +opaque transparent \)
            \( +clone -repage +0+16 -fill "#FF0000" +opaque transparent \)
            \( ${CMAKE_SOURCE_DIR}/fonts/font.png -crop 8x8+0+504 -repage +0+24 -fill "#FFFF3C" +opaque transparent \)
            -background transparent -flatten -extent 8x32
            -fill black
            \( +clone -repage -1-1 +opaque transparent \) -insert 0
            \( +clone -repage +0-1 +opaque transparent \) -insert 0
            \( +clone -repage +1-1 +opaque transparent \) -insert 0
            \( +clone -repage -1+0 +opaque transparent \) -insert 0
            \( +clone -repage +1+0 +opaque transparent \) -insert 0
            \( +clone -repage -1+1 +opaque transparent \) -insert 0
            \( +clone -repage +0+1 +opaque transparent \) -insert 0
            \( +clone -repage +1+1 +opaque transparent \) -insert 0
            -flatten
            ${COMMON_MAGICK_ARGS}
        GRIT_FLAGS ${COMMON_GRIT_FLAGS} -gt -gB4 -pn16
    )
    # fonts
    add_nitro_graphic(
        SOURCE ${CMAKE_SOURCE_DIR}/fonts/font.png
        OUTPUT nitro/graphics/font.grf
        MAGICK_ARGS -colors 2 ${COMMON_MAGICK_ARGS} ${RESIZE_FLAG}
        GRIT_FLAGS ${COMMON_GRIT_FLAGS} -gb -gB2 -pn2
    )
    add_nitro_graphic(
        SOURCE ${CMAKE_SOURCE_DIR}/fonts/buttons_8x8.png
        OUTPUT nitro/graphics/buttons_8x8.grf
        MAGICK_ARGS ${COMMON_MAGICK_ARGS} ${RESIZE_FLAG}
        GRIT_FLAGS ${COMMON_GRIT_FLAGS} -gb -gB8 -pn25
    )
    add_nitro_file(${CMAKE_SOURCE_DIR}/fonts/font.fontmeta nitro/graphics/font.fontmeta)
    add_nitro_file(${CMAKE_SOURCE_DIR}/fonts/buttons_8x8.fontmeta nitro/graphics/buttons_8x8.fontmeta)

    # language files/graphics
    set(LANGS_WITH_SMALL_SPRITES ar eo ga pl szl tr uk)
    foreach(LANG ar ca cy de en eo es es_419 es_AR fr ga it ja ko nl pl pt_BR pt_PT ru szl tr uk zh zh_TW)
        if(NOT LANG STREQUAL en)
            foreach(SPRITES sprites flipsprites)
                set(IMG_TRANSLATED ${CMAKE_SOURCE_DIR}/lang/${LANG}/graphics/${SPRITES}.png)
                if(LANG IN_LIST LANGS_WITH_SMALL_SPRITES)
                    set(IMG_TRANSLATED_SMALL ${CMAKE_SOURCE_DIR}/lang/${LANG}/graphics/${SPRITES}_small.png)
                    set(COMPOSE_SMALL
                        \( ${IMG_TRANSLATED_SMALL} -resize "x%[fx:h/26]" -resize 2600% -channel A -threshold 1 \)
                        -gravity northeast
                        -compose dst-out -composite
                        \( ${IMG_TRANSLATED_SMALL} \)
                        -compose src-over -composite
                        -gravity northwest
                    )
                else()
                    set(COMPOSE_SMALL)
                    set(IMG_TRANSLATED_SMALL)
                endif()
                add_nitro_graphic(
                    SOURCE data/graphics/${SPRITES}.png
                    OUTPUT nitro/lang/${LANG}/graphics/${SPRITES}.grf
                    DEPENDS ${IMG_TRANSLATED} ${CMAKE_SOURCE_DIR}/nds/sprites_small.png ${IMG_TRANSLATED_SMALL}
                    MAGICK_ARGS
                        -background none ${CMAKE_SOURCE_DIR}/nds/sprites_small.png +append
                        \( ${IMG_TRANSLATED} -filter box -resize "x%[fx:h/32]" -resize 3200% -channel A -threshold 1 \)
                        -compose dst-out -composite
                        ${IMG_TRANSLATED} -compose src-over -composite
                        ${COMPOSE_SMALL}
                        -channel RGB -brightness-contrast 100
                        ${COMMON_MAGICK_ARGS} ${RESIZE_FLAG}
                    GRIT_FLAGS ${COMMON_GRIT_FLAGS} -gb -gB2 -pn2
                )
            endforeach()
        endif()
        foreach(XML cutscenes meta numbers roomnames roomnames_special strings strings_plural)
            add_nitro_file(${CMAKE_SOURCE_DIR}/lang/${LANG}/${XML}.xml nitro/lang/${LANG}/${XML}.xml)
        endforeach()
    endforeach()

    set(SOUNDS # in the same order as Music.cpp
        jump jump2
        hurt
        souleyeminijingle
        coin
        save
        crumble
        vanish
        blip
        preteleport
        teleport
        crew1 crew2 crew3 crew4 crew5 crew6
        terminal
        gamesaved
        crashing
        blip2
        countdown
        go
        crash
        combine
        newrecord
        trophy
        rescue
    )
    foreach(SOUND ${SOUNDS})
        list(APPEND FFMPEG_SFX_CMDS
            COMMAND ${FFMPEG} -hide_banner -loglevel error -y -i data/sounds/${SOUND}.wav -ar 8000 prep/sounds/${SOUND}.wav
        )
        list(APPEND SOUNDS_SRC data/sounds/${SOUND}.wav)
        list(APPEND SOUNDS_PREPPED prep/sounds/${SOUND}.wav)
    endforeach()
    add_custom_command(
        OUTPUT nitro/soundbank.bin
        DEPENDS ${SOUNDS_SRC}
        BYPRODUCTS prep
        COMMAND ${E} make_directory prep/sounds
        ${FFMPEG_SFX_CMDS}
        COMMAND ${MMUTIL} ${SOUNDS_PREPPED} -d -onitro/soundbank.bin
    )
    depend_data_files(${SOUNDS_SRC})
    output_nitro_files(nitro/soundbank.bin)

    set(MUSIC_TRACKS
        0levelcomplete
        1pushingonwards
        2positiveforce
        3potentialforanything
        4passionforexploring
        5intermission
        6presentingvvvvvv
        7gamecomplete
        8predestinedfate
        9positiveforcereversed
        10popularpotpourri
        11pipedream
        12pressurecooker
        13pacedenergy
        14piercingthesky
        predestinedfatefinallevel
    )
    set(MUSIC_TRACKS_MONO 0levelcomplete 1pushingonwards 2positiveforce 9positiveforcereversed 11pipedream)
    foreach(TRACK ${MUSIC_TRACKS})
        if (TRACK IN_LIST MUSIC_TRACKS_MONO)
            set(USE_MONO -ac 1)
        else()
            set(USE_MONO)
        endif()
        list(FIND MUSIC_TRACKS ${TRACK} TRACK_ID)
        add_custom_command(
            OUTPUT nitro/music/${TRACK_ID}.wav
            DEPENDS data/music/${TRACK}.ogg
            COMMAND ${FFMPEG} -hide_banner -loglevel error -y -i data/music/${TRACK}.ogg -acodec pcm_u8 -ar 8000 ${USE_MONO} -bitexact nitro/music/${TRACK_ID}.wav
        )
        list(APPEND MUSIC_TRACK_SRC data/music/${TRACK}.ogg)
        output_nitro_files(nitro/music/${TRACK_ID}.wav)
    endforeach()
    add_custom_command(
        OUTPUT ${MUSIC_TRACK_SRC}
        BYPRODUCTS nitro/music
        DEPENDS data/vvvvvvmusic.vvv ${CMAKE_SOURCE_DIR}/dump_music.py
        COMMENT "Unpacking vvvvvvmusic.vvv"
        COMMAND ${E} make_directory data/music nitro/music
        COMMAND ${PYTHON} ${CMAKE_SOURCE_DIR}/dump_music.py
    )
    depend_data_files(data/vvvvvvmusic.vvv)

    add_custom_command(
        OUTPUT ${DATA_FILES}
        BYPRODUCTS data
        DEPENDS ${CMAKE_SOURCE_DIR}/data.zip
        COMMENT "Extracting data.zip"
        COMMAND ${E} make_directory data
        COMMAND ${E} chdir data ${E} tar x ${CMAKE_SOURCE_DIR}/data.zip --touch
    )

    add_custom_target(VVVVVV_NITROFS DEPENDS ${NITRO_FILES})

    # these need to exist at project configuration since nds_create_rom checks for them
    execute_process(
        COMMAND ${E} make_directory nitro
        COMMAND ${MAGICK} ${CMAKE_SOURCE_DIR}/icon.ico icon.bmp
    )

    nds_create_rom(VVVVVV
        AUTHOR "Terry Cavanagh"
        ICON ${CMAKE_BINARY_DIR}/icon.bmp
        NITROFS ${CMAKE_BINARY_DIR}/nitro
        ARM7 ${BLOCKSDS}/sys/arm7/main_core/arm7_maxmod.elf
    )
    add_dependencies(VVVVVV_nds VVVVVV_NITROFS)
endif()

# SDL2 Dependency (Detection pulled from FAudio)
if(DEFINED SDL2_INCLUDE_DIRS AND DEFINED SDL2_LIBRARIES)
    message(STATUS "Using pre-defined SDL2 variables SDL2_INCLUDE_DIRS and SDL2_LIBRARIES")
    target_include_directories(VVVVVV SYSTEM PRIVATE "$<BUILD_INTERFACE:${SDL2_INCLUDE_DIRS}>")
    target_link_libraries(VVVVVV ${SDL2_LIBRARIES})
    if(BUNDLE_DEPENDENCIES AND NOT DEFINED NINTENDO_DS)
        target_include_directories(faudio-static SYSTEM PRIVATE "$<BUILD_INTERFACE:${SDL2_INCLUDE_DIRS}>")
        target_link_libraries(faudio-static ${SDL2_LIBRARIES})
    endif()
elseif (EMSCRIPTEN)
    message(STATUS "Using Emscripten SDL2")
    target_compile_options(VVVVVV PUBLIC -sUSE_SDL=2)
    target_link_libraries(VVVVVV -sUSE_SDL=2)
    if(BUNDLE_DEPENDENCIES)
        target_compile_options(faudio-static PUBLIC -sUSE_SDL=2)
        target_link_libraries(faudio-static -sUSE_SDL=2)
    endif()
else()
    # Only try to autodetect if both SDL2 variables aren't explicitly set
    find_package(SDL2 CONFIG)
    if(TARGET SDL2::SDL2)
        message(STATUS "Using TARGET SDL2::SDL2")
        target_link_libraries(VVVVVV SDL2::SDL2)
        if(BUNDLE_DEPENDENCIES)
            target_link_libraries(faudio-static SDL2::SDL2)
        endif()
    elseif(TARGET SDL2)
        message(STATUS "Using TARGET SDL2")
        target_link_libraries(VVVVVV SDL2)
        if(BUNDLE_DEPENDENCIES)
            target_link_libraries(faudio-static SDL2)
        endif()
    else()
        message(STATUS "No TARGET SDL2::SDL2, or SDL2, using variables")
        target_include_directories(VVVVVV SYSTEM PRIVATE "$<BUILD_INTERFACE:${SDL2_INCLUDE_DIRS}>")
        target_link_libraries(VVVVVV ${SDL2_LIBRARIES})
        if(BUNDLE_DEPENDENCIES)
            target_include_directories(faudio-static SYSTEM PRIVATE "$<BUILD_INTERFACE:${SDL2_INCLUDE_DIRS}>")
            target_link_libraries(faudio-static ${SDL2_LIBRARIES})
        endif()
    endif()
endif()

# Yes, more Apple Crap
if(APPLE)
    find_library(FOUNDATION NAMES Foundation)
    find_library(IOKIT NAMES IOKit)
    target_link_libraries(VVVVVV objc ${IOKIT} ${FOUNDATION})
endif()
# But hey, also some Haiku crap
if(HAIKU)
    find_library(BE_LIBRARY be)
    find_library(ROOT_LIBRARY root)
    target_link_libraries(VVVVVV ${BE_LIBRARY} ${ROOT_LIBRARY})
endif()
if(EMSCRIPTEN)
    # 256MB is enough for everybody
    target_link_libraries(VVVVVV -sFORCE_FILESYSTEM=1 -sTOTAL_MEMORY=256MB)
endif()
