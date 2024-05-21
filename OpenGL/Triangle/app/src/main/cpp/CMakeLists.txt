
cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.

project("Native")

option(ENABLE_ASAN "enable address sanitizer" ON)


add_definitions(-DXR_USE_PLATFORM_ANDROID
                -DXR_OS_ANDROID
                -D__ANDROID__
                ) #define macro


set(CXX_STANDARD "-std=c++17")



if (MSVC)
    set(CXX_STANDARD "/std:c++latest")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_STANDARD} /W0 /Zc:__cplusplus")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_STANDARD} -fstrict-aliasing -Wno-unknown-pragmas -Wno-unused-function -Wno-deprecated-declarations")
endif()


include_directories(${ANDROID_NDK}/sources/android/native_app_glue)

add_library(native SHARED main.cpp
                          EglManager.cpp
                          Triangle.cpp
                          Shader.cpp
                          Asset.cpp
                          Application.cpp
                          GLEnv.cpp
                          ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)


#android
set(CMAKE_SHARED_LINKER_FLAGS
  "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate"
)


#link all the module
target_link_libraries(
   native PRIVATE
   android log GLESv3 EGL)


