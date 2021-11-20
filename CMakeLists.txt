# Generated from cube.pro.

cmake_minimum_required(VERSION 3.16)
project(cube LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
  set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/opengl/cube")

find_package(Qt5 COMPONENTS Core)
find_package(Qt5 COMPONENTS Gui)
find_package(Qt5 COMPONENTS Widgets)
find_package(Qt5 COMPONENTS OpenGL)

add_executable(cube
        model/geometryengine.cpp model/geometryengine.hpp
    main.cpp
        view/mainwidget.cpp view/mainwidget.hpp
        textures/textures.qrc shaders/shaders.qrc mesh/mesh.qrc
        model/BasicIO.hpp model/component.cpp model/component.hpp
        model/gameobject.cpp model/gameobject.hpp
        model/transform.cpp model/transform.hpp
        view/scene.cpp view/scene.hpp)
set_target_properties(cube PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE FALSE
)
target_link_libraries(cube PUBLIC
    Qt::Core
    Qt::Gui
    Qt::OpenGL
    Qt::Widgets
)

install(TARGETS cube
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
