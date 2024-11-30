cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME gfx)
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES C CXX)

if($ENV{GFX_BUILD_EXAMPLES})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
endif()

include(FetchContent)

set(EUTIL_LIB_DIR "${CMAKE_SOURCE_DIR}/thirdparty/eUtil")
set(LOGCRAFT_LIB_DIR "${CMAKE_SOURCE_DIR}/thirdparty/LogCraft")
set(GLM_LIB_DIR "${CMAKE_SOURCE_DIR}/thirdparty/glm")
set(ASSIMP_LIB_DIR "${CMAKE_SOURCE_DIR}/thirdparty/assimp")

set(EUTIL_REPO_URL "https://github.com/RealFaceCode/eUtil.git")
set(LOGCRAFT_REPO_URL "https://github.com/RealFaceCode/LogCraft.git")
set(GLM_REPO_URL "https://github.com/g-truc/glm.git")
set(ASSIMP_REPO_URL "https://github.com/assimp/assimp.git")

if(NOT EXISTS "${EUTIL_LIB_DIR}/CMakeLists.txt")
    message(STATUS "Library 'eUtil' not found. Fetching...")

    FetchContent_Declare(
        eUtil
        GIT_REPOSITORY ${EUTIL_REPO_URL}
        GIT_TAG main
        SOURCE_DIR ${EUTIL_LIB_DIR}
    )

    if(NOT eUtil_POPULATED)
        FetchContent_Populate(eUtil)
    endif()

    message(STATUS "Library 'eUtil' fetched.")
else()
    message(STATUS "Library 'eUtil' already exists.")
    message(STATUS "Try to fetch updates...")

    execute_process(
        COMMAND git pull
        WORKING_DIRECTORY ${EUTIL_LIB_DIR}
    )
endif()

if(NOT EXISTS "${LOGCRAFT_LIB_DIR}/CMakeLists.txt")
    message(STATUS "Library 'LogCraft' not found. Fetching...")

    FetchContent_Declare(
        LogCraft
        GIT_REPOSITORY ${LOGCRAFT_REPO_URL}
        GIT_TAG main
        SOURCE_DIR ${LOGCRAFT_LIB_DIR}
    )

    if(NOT LogCraft_POPULATED)
        FetchContent_Populate(LogCraft)
    endif()

    message(STATUS "Library 'LogCraft' fetched.")
else()
    message(STATUS "Library 'LogCraft' already exists.")
    message(STATUS "Try to fetch updates...")

    execute_process(
        COMMAND git pull
        WORKING_DIRECTORY ${LOGCRAFT_LIB_DIR}
    )
endif()

if(NOT EXISTS "${GLM_LIB_DIR}/CMakeLists.txt")
    message(STATUS "Library 'glm' not found. Fetching...")

    FetchContent_Declare(
        glm
        GIT_REPOSITORY ${GLM_REPO_URL}
        GIT_TAG
        SOURCE_DIR ${GLM_LIB_DIR}
    )

    if(NOT glm_POPULATED)
        FetchContent_Populate(glm)
    endif()

    message(STATUS "Library 'glm' fetched.")
else()
    message(STATUS "Library 'glm' already exists.")
    message(STATUS "Try to fetch updates...")

    execute_process(
        COMMAND git pull
        WORKING_DIRECTORY ${GLM_LIB_DIR}
    )
endif()

if(NOT EXISTS "${ASSIMP_LIB_DIR}/CMakeLists.txt")
    message(STATUS "Library 'assimp' not found. Fetching...")
    FetchContent_Declare(
        assimp
        GIT_REPOSITORY ${ASSIMP_REPO_URL}
        GIT_TAG 
        SOURCE_DIR ${ASSIMP_LIB_DIR}
    )

    if(NOT assimp_POPULATED)
        FetchContent_Populate(assimp)
    endif()

    message(STATUS "Library 'assimp' fetched.")
else()
    message(STATUS "Library 'assimp' already exists.")
    message(STATUS "Try to fetch updates...")

    execute_process(
        COMMAND git pull
        WORKING_DIRECTORY ${ASSIMP_LIB_DIR}
    )
endif()

if(NOT TARGET assimp)
    set(ASSIMP_INSTALL OFF)
    set(ASSIMP_WARNINGS_AS_ERRORS OFF)
    add_subdirectory(${ASSIMP_LIB_DIR} ${CMAKE_CURRENT_BINARY_DIR}/assimp)
endif()

if(NOT TARGET glad)
    add_subdirectory(thirdpartynongit/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
endif()

if(NOT TARGET glm)
    add_subdirectory(${GLM_LIB_DIR} ${CMAKE_CURRENT_BINARY_DIR}/glm)
endif()

if(NOT TARGET eUtil)
    add_subdirectory(${EUTIL_LIB_DIR} ${CMAKE_CURRENT_BINARY_DIR}/eUtil)
endif()

if(NOT TARGET LogCraft)
    add_subdirectory(${LOGCRAFT_LIB_DIR} ${CMAKE_CURRENT_BINARY_DIR}/LogCraft)
endif()

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS  "libBuild/src/*.cpp")

if(NOT TARGET ${PROJECT_NAME})
    add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
    target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
    target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_SOURCE_DIR}/libBuild/hdr
    )
    target_include_directories(${PROJECT_NAME} 
    PRIVATE ${LOGCRAFT_LIB_DIR}/libBuild/hdr 
    PRIVATE ${EUTIL_LIB_DIR}/libBuild/hdr 
    PRIVATE ${CMAKE_SOURCE_DIR}/thirdpartynongit/glad/include 
    PRIVATE ${GLM_LIB_DIR}
    PRIVATE ${CMAKE_SOURCE_DIR}/thirdpartynongit/stb
    PRIVATE ${ASSIMP_LIB_DIR}/include
    )
    target_link_libraries(${PROJECT_NAME} PRIVATE LogCraft eUtil glad glm assimp)
    target_compile_definitions(${PROJECT_NAME} PRIVATE GFX_EXPORTS)
endif()

message(STATUS "GFX build examples: " $ENV{GFX_BUILD_EXAMPLES})

if($ENV{GFX_BUILD_EXAMPLES})
    add_subdirectory(buildtest)
endif()