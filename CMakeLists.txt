cmake_minimum_required(VERSION 3.11)
if(NOT DEFINED CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
     set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
endif()
include(FetchContent)

# set the project name
project(check_signature VERSION 1.0 LANGUAGES C)
set(SOURCE_FILES main.c)

FetchContent_Declare (
 mbedtls
  GIT_REPOSITORY https://github.com/ARMmbed/mbedtls.git
  GIT_TAG        v2.26.0
)
FetchContent_MakeAvailable(mbedtls)
configure_file(config.h ${mbedtls_SOURCE_DIR}/include/mbedtls/ COPYONLY)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} mbedtls)

install (TARGETS check_signature RUNTIME DESTINATION bin)
