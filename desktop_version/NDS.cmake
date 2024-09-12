# cmake_minimum_required(VERSION 2.8.12...3.5)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR armv5te)
set(NDS TRUE)

# Check for BlocksDS toolchain environment variables and apply defaults if necessary
if(DEFINED ENV{BLOCKSDS})
	set(BLOCKSDS "$ENV{BLOCKSDS}")
else()
	set(BLOCKSDS "/opt/blocksds/core")
endif()
if(DEFINED ENV{WONDERFUL_TOOLCHAIN})
	set(WONDERFUL "$ENV{WONDERFUL_TOOLCHAIN}")
else()
	set(WONDERFUL "/opt/wonderful")
endif()

# Set compilers/linker
set(ANE ${WONDERFUL}/toolchain/gcc-arm-none-eabi/bin/arm-none-eabi)
set(CMAKE_C_COMPILER ${ANE}-gcc)
set(CMAKE_CXX_COMPILER ${ANE}-g++)
# Linker needs BLOCKSDS environment variable to be exported
set(CMAKE_C_LINK_EXECUTABLE "${CMAKE_COMMAND} -E env BLOCKSDS=${BLOCKSDS} <CMAKE_C_COMPILER> <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_COMMAND} -E env BLOCKSDS=${BLOCKSDS} <CMAKE_C_COMPILER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
# Extra BlocksDS tools
set(NDSTOOL ${BLOCKSDS}/tools/ndstool/ndstool)
set(BIN2C ${BLOCKSDS}/tools/bin2c/bin2c)
set(GRIT ${BLOCKSDS}/tools/grit/grit)
set(MMUTIL ${BLOCKSDS}/tools/mmutil/mmutil)

# Set default compiler/linker flags for NDS projects
set(ARCH "-mthumb -mcpu=arm946e-s+nofp")
set(SPECS ${BLOCKSDS}/sys/crts/ds_arm9.specs)
set(LIBNDS ${BLOCKSDS}/libs/libnds)
set(CMAKE_C_FLAGS_INIT "-std=gnu17 ${ARCH} -O2 -ffunction-sections -fdata-sections -specs=${SPECS}")
set(CMAKE_C_STANDARD_LIBRARIES "-lnds9 -lc")
set(CMAKE_C_STANDARD_INCLUDE_DIRECTORIES ${LIBNDS}/include)
set(CMAKE_C_OUTPUT_EXTENSION .o)
set(CMAKE_CXX_FLAGS_INIT "-std=gnu++17 ${ARCH} -O2 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -specs=${SPECS}")
set(CMAKE_CXX_STANDARD_LIBRARIES "-lnds9 -lstdc++ -lc")
set(CMAKE_CXX_OUTPUT_EXTENSION .o)
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${LIBNDS}/include)
set(CMAKE_EXE_LINKER_FLAGS_INIT "-L${LIBNDS}/lib")

# Set the find root to BlocksDS's libs folder
set(CMAKE_FIND_ROOT_PATH ${BLOCKSDS}/libs)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

function(add_nds_rom target)
	cmake_parse_arguments(arg "" "TITLE;SUBTITLE;AUTHOR;ICON" "NITRO_DIRS;DEPENDS" ${ARGN})
	
	if(NOT arg_TITLE)
		set(arg_TITLE ${target})
	endif()
	if(NOT arg_AUTHOR)
		set(arg_AUTHOR "Built with BlocksDS")
	endif()
	if(arg_SUBTITLE)
		set(FULL_TITLE "${arg_TITLE}\;${arg_SUBTITLE}\;${arg_AUTHOR}")
	else()
		set(FULL_TITLE "${arg_TITLE}\;${arg_AUTHOR}")
	endif()

	if(NOT arg_ICON)
		set(arg_ICON ${BLOCKSDS}/sys/icon.bmp)
	endif()
	
	if (arg_NITRO_DIRS)
		set(NITROFS_ARG -d ${arg_NITRO_DIRS})
	endif()
	
	set(ROM ${target}.nds)
	
	set(NDSTOOL_ARGS
		-c ${ROM}
		-7 ${BLOCKSDS}/sys/default_arm7/arm7.elf
		-9 ${target}
		-b ${arg_ICON} "${FULL_TITLE}"
		${NITROFS_ARG}
	)

	add_custom_target(${ROM} ALL
		DEPENDS ${target} ${arg_NITRO_DIRS} ${arg_DEPENDS} ${arg_ICON}
		COMMAND ${NDSTOOL} ${NDSTOOL_ARGS} VERBATIM
		COMMENT "Building NDS rom ${ROM}"
	)
endfunction()

function(add_grit_rule)
	cmake_parse_arguments(arg "" "OUTDIR" "FLAGS;SOURCES" ${ARGN})
	
	if ("-fh!" IN_LIST arg_FLAGS)
	set(HEADER_OUT 0)
	else()
	set(HEADER_OUT 1)
	endif()
	
	set(EXT ".s")
	if ("-ftc" IN_LIST arg_FLAGS)
		set(EXT ".c")
	elseif("-ftb" IN_LIST arg_FLAGS)
		set(EXT ".bin")
	elseif("-ftB" IN_LIST arg_FLAGS)
		set(EXT "")
	elseif("-ftg" IN_LIST arg_FLAGS)
		set(EXT ".gbfs")
	elseif("-ftr" IN_LIST arg_FLAGS)
		set(EXT ".grf")
	endif()

	foreach(FILE ${arg_SOURCES})
		get_filename_component(NAME_PART ${FILE} NAME_WE)
		set(OUTNAME ${arg_OUTDIR}/${NAME_PART})

		if (${EXT} EQUAL "" OR ${EXT} EQUAL ".bin")
			set(OUTFILES
				${OUTNAME}.img${EXT}
				${OUTNAME}.map${EXT}
				${OUTNAME}.meta${EXT}
				${OUTNAME}.pal${EXT}
			)
		else()
			set(OUTFILES ${OUTNAME}${EXT})
		endif()
		if(HEADER_OUT)
			set(OUTFILES ${OUTFILES} ${OUTNAME}.h)
		endif()
		
		add_custom_command(
			OUTPUT ${OUTFILES}
			DEPENDS ${FILE}
			COMMAND ${GRIT} ${FILE} ${arg_FLAGS} -o${OUTNAME}
			VERBATIM
		)
	endforeach()
endfunction()