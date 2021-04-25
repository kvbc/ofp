cmake_minimum_required(VERSION 3.0.2)

project(ofp)

set(CMAKE_C_FLAGS "-Wno-switch \
	-Wno-maybe-uninitialized \
	-Wall \
	-O2 -s")
set(CMAKE_CXX_FLAGS "")
set(CMAKE_EXE_LINKER_FLAGS "")

# add_executable(${PROJECT_NAME} argument.c mem.c ofp.c option.c parser.c state.c)

add_library(${PROJECT_NAME} STATIC argument.c mem.c option.c parser.c state.c)
