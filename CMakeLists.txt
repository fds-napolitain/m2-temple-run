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
        source/BasicIO.hpp source/camera.cpp source/camera.hpp source/component.cpp source/component.hpp
        source/entity.hpp source/entity.cpp source/geometryengine.hpp source/geometryengine.cpp source/mainwidget.hpp source/mainwidget.cpp
        source/mesh.cpp source/mesh.hpp source/scene.cpp source/scene.hpp source/scenegraph.hpp source/scenegraph.cpp
        source/transform.cpp source/transform.hpp
        source/physics/aabb.cpp source/physics/aabb.hpp source/physics/BoundingSphere.cpp source/physics/BoundingSphere.hpp source/physics/collider.cpp
        source/physics/collider.hpp source/physics/intersectdata.cpp source/physics/intersectdata.hpp source/physics/physicobject.cpp source/physics/physicobject.hpp
        source/physics/physicsengine.cpp source/physics/physicsengine.hpp source/physics/plane.cpp source/physics/plane.hpp source/physics/ReferenceCounter.hpp source/TimeStep.hpp source/TargetFPS.cpp source/TargetFPS.hpp)

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