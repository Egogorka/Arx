cmake_minimum_required(VERSION 3.17)
project(Arx)

set(CMAKE_CXX_STANDARD 17)

add_executable(Arx main.cpp
        utility/vector/Vector.h
        utility/vector/Vector.cpp
        assets/segments/l.cpp
        assets/segments/l.h
        src/Drawer.cpp
        src/Drawer.h
        assets/textures/static/l.cpp
        assets/textures/static/l.h
        utility/ndarray/ndArrayBase.h
        utility/ndarray/ndArrayView.h
        utility/ndarray/ndArray.h
        src/drawer/TileSprite.cpp
        src/drawer/TileSprite.h
        assets/tiles.h
        src/Segment.cpp
        src/Segment.h
        src/App.cpp
        src/App.h
        utility/Eventer.h
        assets/textures/dynamic/l.cpp
        assets/textures/dynamic/l.h
        utility/vector/sfConvert.h
        src/components/MultispriteC.h
        include/entt.hpp
        assets/dynamic.h
        src/drawer/TileSystem.cpp
        src/drawer/TileSystem.h
        src/drawer/SpriteSystem.cpp
        src/drawer/SpriteSystem.h
        src/components/LocationC.h
        src/drawer/Multisprite.cpp
        src/systems/ControlsSystem.cpp
        src/systems/ControlsSystem.h
        src/components/PlayerC.h
        src/physics/CollisionC.h
        src/physics/PhysicsSystem.cpp
        src/physics/PhysicsSystem.h
        main.h
        src/physics/GravityC.h
        src/physics/GravitySystem.h src/physics/GravitySystem.cpp










        src/components/CameraLock.h
        src/drawer/CameraSystem.cpp src/drawer/CameraSystem.h)

include_directories(src utility ../Arx)

###########################################
# Nlohmann Json library

include(FetchContent)
FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent.git
        GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

target_link_libraries(Arx PRIVATE sfml-graphics sfml-audio nlohmann_json::nlohmann_json)

###########################################
# SFML

if (WIN32)
    set(SFML_DIR ../SFML-2.5.1/lib/cmake/SFML)
    file(GLOB BINARY_DEP_DLLS "../SFML-2.5.1/bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

target_link_libraries(Arx PRIVATE )

include(FetchContent)

###########################################
#Google tests

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

###########################################
# Google test linkage

option(BUILD_TESTS "Build tests" ON)
enable_testing()

add_executable(
        hello_test
        tests/hello_test.cpp
        tests/json.cpp
        tests/ndarray/ndarray_test.cpp tests/vector/vector_test.cpp)
target_link_libraries(
        hello_test
        gtest_main
        nlohmann_json::nlohmann_json
)

include(GoogleTest)
add_test(GoogleTest hello_test)
gtest_discover_tests(hello_test)
