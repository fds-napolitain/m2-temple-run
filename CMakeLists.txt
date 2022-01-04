# Generated from TempleRun.pro.

cmake_minimum_required(VERSION 3.16)
project(TempleRun LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()
set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/opengl/TempleRun")

find_package(Qt5 COMPONENTS Core)
find_package(Qt5 COMPONENTS Gui)
find_package(Qt5 COMPONENTS Widgets)
find_package(Qt5 COMPONENTS OpenGL)

add_executable(TempleRun main.cpp textures/textures.qrc models/models.qrc shaders/shaders.qrc
        source/engine/rendering/BasicIO.hpp source/engine/rendering/camera.cpp source/engine/rendering/camera.hpp source/engine/components/component.cpp source/engine/components/component.hpp
        source/engine/rendering/entity.hpp source/engine/rendering/entity.cpp source/engine/rendering/geometryengine.hpp source/engine/rendering/geometryengine.cpp source/mainwidget.hpp source/mainwidget.cpp
        source/engine/rendering/mesh.cpp source/engine/rendering/mesh.hpp source/engine/rendering/scene.cpp source/engine/rendering/scene.hpp source/game/scenegraph.hpp source/game/scenegraph.cpp
        source/engine/transform.cpp source/engine/transform.hpp
        source/engine/components/physics/collider/aabb.cpp source/engine/components/physics/collider/aabb.hpp source/engine/components/physics/collider/BoundingSphere.cpp source/engine/components/physics/collider/BoundingSphere.hpp source/engine/components/physics/collider.cpp
        source/engine/components/physics/collider.hpp source/engine/physics/intersectdata.cpp source/engine/physics/intersectdata.hpp
        source/engine/physics/plane.cpp source/engine/physics/plane.hpp source/engine/physics/ReferenceCounter.hpp
        source/engine/TimeStep.hpp source/engine/TargetFPS.cpp source/engine/TargetFPS.hpp
        source/engine/physics/PhysicSystem.cpp source/engine/physics/PhysicSystem.hpp source/game/Player.cpp source/game/Player.hpp source/engine/rendering/Light.cpp source/engine/rendering/Light.hpp source/engine/components/rendering/Animation.cpp source/engine/components/rendering/Animation.hpp)

set_target_properties(TempleRun PROPERTIES
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE TRUE
        )

target_link_libraries(TempleRun PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::OpenGL
        Qt5::Widgets
        )

install(TARGETS TempleRun
        RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
        BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
        LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
        )