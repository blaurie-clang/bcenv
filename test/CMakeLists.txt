cmake_minimum_required(VERSION 3.24)

project(
        bcenv_tests
        LANGUAGES C
)

if(PROJECT_IS_TOP_LEVEL)
    find_package(bcenv REQUIRED)
    enable_testing()
endif()

add_executable(${PROJECT_NAME}
        source/bcenv_test.c)

add_test(
        NAME "Initial Setup"
        COMMAND ${PROJECT_NAME}
)

target_link_libraries(${PROJECT_NAME} PRIVATE bcenv)