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
        source/engine/utilities/BasicIO.hpp source/engine/entity/camera.cpp source/engine/entity/camera.hpp source/engine/components/component.cpp source/engine/components/component.hpp
        source/engine/entity/entity.hpp source/engine/entity/entity.cpp source/engine/system/rendering/geometryengine.hpp source/engine/system/rendering/geometryengine.cpp source/mainwidget.hpp source/mainwidget.cpp
        source/engine/components/rendering/mesh.cpp source/engine/components/rendering/mesh.hpp source/engine/system/rendering/scene.cpp source/engine/system/rendering/scene.hpp source/game/scenegraph.hpp source/game/scenegraph.cpp
        source/engine/transform.cpp source/engine/transform.hpp
        source/engine/components/physics/collider/aabb.cpp source/engine/components/physics/collider/aabb.hpp source/engine/components/physics/collider/BoundingSphere.cpp source/engine/components/physics/collider/BoundingSphere.hpp source/engine/components/physics/collider.cpp
        source/engine/components/physics/collider.hpp source/engine/system/physics/intersectdata.cpp source/engine/system/physics/intersectdata.hpp
        source/engine/system/physics/plane.cpp source/engine/system/physics/plane.hpp source/engine/utilities/ReferenceCounter.hpp
        source/engine/TimeStep.hpp source/engine/TargetFPS.cpp source/engine/TargetFPS.hpp
        source/engine/system/physics/PhysicSystem.cpp source/engine/system/physics/PhysicSystem.hpp source/game/Player.cpp source/game/Player.hpp source/engine/entity/Light.cpp source/engine/entity/Light.hpp source/engine/components/rendering/Animation.cpp source/engine/components/rendering/Animation.hpp)

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