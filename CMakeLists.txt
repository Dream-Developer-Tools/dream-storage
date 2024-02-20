cmake_minimum_required(VERSION 3.26)
project(dstorage)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_ENABLE_EXPORTS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()


add_library(dstorage src/dstorage.cpp
        src/tokens.h
        src/objects/dstorageobjects.cpp
        src/objects/dstorageobjects.h
        src/objects/buffer/frombuffer.cpp
        src/objects/buffer/frombuffer.h
        src/objects/buffer/tobuffer.cpp
        src/objects/buffer/tobuffer.h)

# add executable to dstorage target
add_executable(dstorage_test test/main.cpp)
target_link_libraries(dstorage_test dstorage)
target_include_directories(dstorage_test PRIVATE src)
# make sure that in debug mode dstorage_test is the default target
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT dstorage_test)
