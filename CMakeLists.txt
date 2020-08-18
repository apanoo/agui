project("agui")

cmake_minimum_required(VERSION 2.8)

## c++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

## SDL2
add_subdirectory(${PROJECT_SOURCE_DIR}/thirdparty/SDL2)
## imgui
add_subdirectory(${PROJECT_SOURCE_DIR}/thirdparty/imgui)
## glad
add_subdirectory(${PROJECT_SOURCE_DIR}/thirdparty/glad)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/thirdparty/SDL2/include
    ${PROJECT_SOURCE_DIR}/thirdparty/glad/include
    ${PROJECT_SOURCE_DIR}/thirdparty/imgui
) 

add_executable("agui"
main.cpp
ui/imgui_impl_opengl3.cpp
ui/imgui_impl_sdl.cpp
)

## link libs
target_link_libraries("agui"
    SDL2
    SDL2main
    glad
    imgui
)