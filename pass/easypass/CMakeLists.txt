cmake_minimum_required(VERSION 3.4.3)
project(easypass CXX)
enable_language(C)

set(LLVM_DIR C:/Work/LLVM/build/lib/cmake/llvm)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_a_libs support core irreader scalaropts)

#add_executable(easypass src/easypass.cpp src/easypass.hpp)
add_library(easypass STATIC src/easypass.cpp src/easypass.hpp)
target_link_libraries(easypass ${llvm_a_libs})




