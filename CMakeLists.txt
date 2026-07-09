cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(AIArchitectEngineOmni VERSION 1.2.0)

# Help CMake find Geode when building through GitHub Actions or locally
if(DEFINED ENV{GEODE_SDK})
    message(STATUS "Found GEODE_SDK environment variable: $ENV{GEODE_SDK}")
    list(APPEND CMAKE_PREFIX_PATH "$ENV{GEODE_SDK}")
    list(APPEND CMAKE_PREFIX_PATH "$ENV{GEODE_SDK}/cmake")
    list(APPEND CMAKE_MODULE_PATH "$ENV{GEODE_SDK}/cmake")
endif()

if(DEFINED GEODE_SDK)
    message(STATUS "Found GEODE_SDK CMake variable: ${GEODE_SDK}")
    list(APPEND CMAKE_PREFIX_PATH "${GEODE_SDK}")
    list(APPEND CMAKE_PREFIX_PATH "${GEODE_SDK}/cmake")
    list(APPEND CMAKE_MODULE_PATH "${GEODE_SDK}/cmake")
endif()

find_package(Geode CONFIG REQUIRED)

add_geode_mod(
    ${PROJECT_NAME}
    SOURCES src/main.cpp
    RESOURCES mod.json
)

if(ANDROID)
    target_compile_definitions(${PROJECT_NAME} PRIVATE GEODE_IS_ANDROID)
endif()
