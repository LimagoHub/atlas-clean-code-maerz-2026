cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)

set(gtest_force_shared_crt ON CACHE BOOL "")
add_subdirectory(google)
set_target_properties(gtest      PROPERTIES FOLDER Dependencies)
set_target_properties(gmock      PROPERTIES FOLDER Dependencies)
set_target_properties(gtest_main PROPERTIES FOLDER Dependencies)
set_target_properties(gmock_main PROPERTIES FOLDER Dependencies)
set_target_properties(gmock_main gtest_main PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)

set(TEST_SOURCES
    main.cpp
    test_generators.cpp
    test_factories.cpp
    test_builder.cpp
    test_stopwatch.cpp
)

add_executable(VectorFillerTest ${TEST_SOURCES})

target_include_directories(VectorFillerTest PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(VectorFillerTest
    GTest::gtest
    GTest::gmock
)

add_test(NAME VectorFillerTest COMMAND VectorFillerTest)

set_target_properties(VectorFillerTest PROPERTIES FOLDER Tests)

set_target_properties(VectorFillerTest PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>"
)
