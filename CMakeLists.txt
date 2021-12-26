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
        source/engine/components/rendering/mesh.cpp source/engine/components/rendering/mesh.hpp source/engine/scene.cpp source/engine/scene.hpp source/engine/scenegraph.hpp source/engine/scenegraph.cpp
        source/engine/transform.cpp source/engine/transform.hpp
        source/engine/physics/aabb.cpp source/engine/physics/aabb.hpp source/engine/physics/BoundingSphere.cpp source/engine/physics/BoundingSphere.hpp source/engine/components/physics/collider.cpp
        source/engine/components/physics/collider.hpp source/engine/physics/intersectdata.cpp source/engine/physics/intersectdata.hpp
        source/engine/physics/plane.cpp source/engine/physics/plane.hpp source/engine/physics/ReferenceCounter.hpp
        source/engine/TimeStep.hpp source/engine/TargetFPS.cpp source/engine/TargetFPS.hpp
        source/engine/physics/PhysicSystem.cpp source/engine/physics/PhysicSystem.hpp source/game/prefabs/Player.cpp source/game/prefabs/Player.hpp
        source/game/prefabs/Score.cpp source/game/prefabs/Score.hpp source/engine/rendering/Prefabs.cpp source/engine/rendering/Prefabs.hpp source/engine/TimeStep.cpp source/game/scenes/SceneGame.cpp source/game/scenes/SceneGame.hpp source/engine/components/events/KeyboardEvents.cpp source/engine/components/events/KeyboardEvents.hpp source/engine/components/rendering/Animation.cpp source/engine/components/rendering/Animation.hpp
        source/engine/rendering/Light.cpp source/engine/rendering/Light.hpp)

set_target_properties(TempleRun PROPERTIES
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE FALSE
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