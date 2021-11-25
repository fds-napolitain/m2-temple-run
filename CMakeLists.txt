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
        source/BasicIO.h source/BasicIO.hpp source/camera.cpp source/camera.h source/component.cpp source/component.h
        source/entity.h source/entity.cpp source/geometryengine.h source/geometryengine.cpp source/mainwidget.h source/mainwidget.cpp
        source/mesh.cpp source/mesh.h source/rien.h source/scene.cpp source/scene.h source/scenegraph.h source/scenegraph.cpp
        source/transform.cpp source/transform.h
        source/physics/aabb.cpp source/physics/aabb.h source/physics/BoundingSphere.cpp source/physics/BoundingSphere.h source/physics/collider.cpp
        source/physics/collider.h source/physics/intersectdata.cpp source/physics/intersectdata.h source/physics/physicobject.cpp source/physics/physicobject.h
        source/physics/physicsengine.cpp source/physics/physicsengine.h source/physics/plane.cpp source/physics/plane.h source/physics/ReferenceCounter.h)

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
