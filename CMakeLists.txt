cmake_minimum_required(VERSION 3.24)
project(
        bcenv
        VERSION 0.0.1
        DESCRIPTION ""
        HOMEPAGE_URL ""
        LANGUAGES C
)

set(CMAKE_C_STANDARD 23)

add_library(${PROJECT_NAME} INTERFACE include/bcenv.h)

target_include_directories(
        ${PROJECT_NAME}
        INTERFACE
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include"
)

if(BUILD_TESTING)
    include(CTest)
    add_subdirectory(test)
endif()