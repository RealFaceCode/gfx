cmake_minimum_required(VERSION 3.5)
set(PROJECT_NAME glad)
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES C CXX)

if(NOT TARGET ${PROJECT_NAME})
    add_library(${PROJECT_NAME} STATIC "src/glad.c")
    target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
    target_include_directories(${PROJECT_NAME} PUBLIC include)
endif()
