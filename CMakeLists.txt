cmake_minimum_required(VERSION 3.5)
set(PROJECT_NAME gfx)
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES C CXX)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)

if($ENV{GFX_BUILD_EXAMPLES})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
endif()

add_subdirectory(thirdparty/LogCraft)
add_subdirectory(thirdparty/eUtil)
add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glm)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS  "libBuild/src/*.cpp")

if(NOT TARGET ${PROJECT_NAME})
    add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
    target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
    target_include_directories(${PROJECT_NAME} PUBLIC libBuild/hdr )
    target_include_directories(${PROJECT_NAME} PRIVATE 
    thirdparty/LogCraft/libBuild/hdr 
    thirdparty/eUtil/libBuild/hdr 
    thirdparty/glad/include 
    thirdparty/glm
    thirdparty/stb
    )
    target_link_libraries(${PROJECT_NAME} PRIVATE LogCraft eUtil glad glm)
    target_compile_definitions(${PROJECT_NAME} PRIVATE GFX_EXPORTS)
endif()

message(STATUS "GFX build examples: " $ENV{GFX_BUILD_EXAMPLES})

if($ENV{GFX_BUILD_EXAMPLES})
    add_subdirectory(buildtest)
endif()