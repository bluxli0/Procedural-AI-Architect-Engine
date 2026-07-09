cmake_minimum_required(VERSION 3.25)
project(AIArchitectEngineOmni VERSION 1.2.0)

find_package(Geode REQUIRED)

add_geode_mod(
    ${PROJECT_NAME}
    SOURCES src/main.cpp
    RESOURCES mod.json
)

if(CORRESPOND_TO_ANDROID)
    target_compile_definitions(${PROJECT_NAME} PRIVATE GEODE_IS_ANDROID)
endif()
