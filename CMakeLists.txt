cmake_minimum_required(VERSION 3.14)
project(Variant18ZeroOrderExtrapolator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

include(FetchContent)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(core
    Point.cpp
    PiecewiseLinearApproximation.cpp
    Segment.cpp
)

target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if(MSVC)
    target_compile_options(core PUBLIC
        $<$<COMPILE_LANGUAGE:CXX>:/utf-8>
    )
endif()

add_executable(variant18_app
    main.cpp
)

target_link_libraries(variant18_app PRIVATE core)

add_executable(tests
    tests.cpp
)

target_include_directories(tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(tests
    PRIVATE
    core
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
