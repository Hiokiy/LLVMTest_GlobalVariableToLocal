cmake_minimum_required(VERSION 3.4.3)
project(Power2ToLShift CXX)
enable_language(C)

set(LLVM_DIR C:/Work/LLVM/build/lib/cmake/llvm)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_a_libs support core irreader scalaropts)

#add_executable(Power2ToLShift src/Power2ToLShift.cpp src/Power2ToLShift.hpp)
add_library(Power2ToLShift STATIC src/Power2ToLShift.cpp src/Power2ToLShift.hpp)
target_link_libraries(Power2ToLShift ${llvm_a_libs})




