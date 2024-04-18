cmake_minimum_required(VERSION 3.0.0)
project(timestamped_filesystem_manager VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  test_TimestampedFileManager
  ./test/test_TimestampedFileManager.cpp
)
target_link_libraries(
    test_TimestampedFileManager
    GTest::gtest_main
    TimeStampedFileManager
)

include(GoogleTest)
gtest_discover_tests(test_TimestampedFileManager)


include_directories(timestamped_file_manager)
add_subdirectory(timestamped_file_manager)


add_executable(fm_test fm_test.cpp)

target_link_libraries(fm_test TimeStampedFileManager)
