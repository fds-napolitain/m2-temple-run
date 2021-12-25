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
        source/engine/rendering/BasicIO.hpp source/engine/rendering/camera.cpp source/engine/rendering/camera.hpp source/engine/rendering/component.cpp source/engine/rendering/component.hpp
        source/engine/rendering/entity.hpp source/engine/rendering/entity.cpp source/engine/rendering/geometryengine.hpp source/engine/rendering/geometryengine.cpp source/mainwidget.hpp source/mainwidget.cpp
        source/engine/rendering/mesh.cpp source/engine/rendering/mesh.hpp source/engine/rendering/scene.cpp source/engine/rendering/scene.hpp source/engine/rendering/scenegraph.hpp source/engine/rendering/scenegraph.cpp
        source/engine/transform.cpp source/engine/transform.hpp
        source/engine/physics/aabb.cpp source/engine/physics/aabb.hpp source/engine/physics/BoundingSphere.cpp source/engine/physics/BoundingSphere.hpp source/engine/physics/collider.cpp
        source/engine/physics/collider.hpp source/engine/physics/intersectdata.cpp source/engine/physics/intersectdata.hpp
        source/engine/physics/plane.cpp source/engine/physics/plane.hpp source/engine/physics/ReferenceCounter.hpp
        source/engine/TimeStep.hpp source/engine/TargetFPS.cpp source/engine/TargetFPS.hpp
         source/engine/physics/PhysicSystem.cpp source/engine/physics/PhysicSystem.hpp source/game/prefabs/Player.cpp source/game/prefabs/Player.hpp source/game/scenes/SceneMenu.cpp source/game/scenes/SceneGame.cpp source/game/prefabs/Score.cpp source/game/prefabs/Score.hpp source/engine/rendering/Prefabs.cpp source/engine/rendering/Prefabs.hpp source/engine/TimeStep.cpp)

set_target_properties(TempleRun PROPERTIES
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE FALSE
        )
target_link_libraries(TempleRun PUBLIC
        Qt::Core
        Qt::Gui
        Qt::OpenGL
        Qt::Widgets
        )

install(TARGETS TempleRun
        RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
        BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
        LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
        )