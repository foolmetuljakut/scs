cmake_minimum_required(VERSION 3.12)
project(strategic_combat_simulation)
include(CTest)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always -Wall -Werror -Wfatal-errors -Wno-pragma-once-outside-header")

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "src/*.cpp" "src/*.hpp"
)
file(GLOB_RECURSE LIB_FILES CONFIGURE_DEPENDS
    "src/*.cpp" "src/*.hpp"
)
list(FILTER LIB_FILES EXCLUDE REGEX ".*/main\\.cpp$")
file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS
    "test/*.cpp" "test/*.hpp"
)

option(ENABLE_SANITIZER "Build with Address and Undefined Behavior Sanitizers" OFF)
option(ENABLE_COVERAGE "Build with Coverage for gcov/lcov" OFF)

if(ENABLE_SANITIZER)
    message(STATUS "Enabling Address and UB Sanitizers")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -g -fno-omit-frame-pointer")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address,undefined")
endif()

if(ENABLE_COVERAGE)
    message(STATUS "Enabling Coverage Generation")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0")
endif()

# App
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} PRIVATE
    spdlog fmt config++ m
)
target_link_options(${PROJECT_NAME} PRIVATE
    -Wl,--as-needed
    -Wl,--no-undefined
)

# Tests
find_package(Catch2 3 REQUIRED)
include(Catch)
add_executable(${PROJECT_NAME}_tests ${LIB_FILES} ${TEST_FILES})
target_include_directories(${PROJECT_NAME}_tests PRIVATE src)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE
    Catch2::Catch2WithMain
    spdlog fmt config++ m
)
target_link_options(${PROJECT_NAME}_tests PRIVATE
    -Wl,--as-needed
)
if(ENABLE_COVERAGE)
    target_link_options(${PROJECT_NAME}_tests PRIVATE --coverage)
endif()

# Register test binary instead of discovery to avoid NOT_BUILT issues
enable_testing()
add_test(
    NAME ${PROJECT_NAME}_tests
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_tests
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

