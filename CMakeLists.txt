cmake_minimum_required (VERSION 3.8)

project ("MultiByteAndWideChar")

message(${CMAKE_CURRENT_SOURCE_DIR})

set(FAKELIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/fakelib)
include_directories(${FAKELIB_DIR}/include)

add_definitions(-DDEBUG_FAKELIB)

#add_subdirectory(fakelib)
add_subdirectory(fakelib/libiconv-1.14 libiconv-1.14.build)

# 将源代码添加到此项目的可执行文件。
add_executable (MultiByteAndWideChar "MultiByteAndWideChar.cpp"
${FAKELIB_DIR}/include/vlocale.h
${FAKELIB_DIR}/include/vmbswcs.h
${FAKELIB_DIR}/include/vmbswcs.cpp
)

# TODO: 如有需要，请添加测试并安装目标。
