cmake_minimum_required(VERSION 3.9)
project(gpu_programming)

set(OpenCL_INCLUDE_DIR "C:/Program Files/NVIDIA\ GPU\ Computing\ Toolkit/CUDA/v9.2/include")
set(OpenCL_LIBRARY "C:/Program Files/NVIDIA\ GPU\ Computing\ Toolkit/CUDA/v9.2/lib/x64/OpenCL.lib")

find_package(OpenCL REQUIRED)

include_directories(${OpenCL_INCLUDE_DIRS})

link_libraries(${OpenCL_LIBRARY})

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCL_LIBRARY})