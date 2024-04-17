cmake_minimum_required(VERSION 3.0.0)
project(timestamped_filesystem_manager VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB Sources
    "src/timestamped_filesystem_manager/*.cpp"
    )

file(GLOB Headers
    "src/timestamped_filesystem_manager/*.h"
    )

add_executable(timestamped_filesystem_manager ${Sources} ${Headers})
