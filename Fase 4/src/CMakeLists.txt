cmake_minimum_required(VERSION 3.9)

# Project Name
PROJECT(Fase4)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(engine ./engine/engine.cpp)
add_executable(generator ./generator/generator.cpp)

add_library(
    utils_lib
    ./utils/ponto.cpp
    ./utils/ponto.hpp
    ./utils/figura.cpp
    ./utils/figura.hpp
    ./utils/matriz.cpp
    ./utils/matriz.hpp
)

add_library(
    pugixml_lib
    ./pugixml/src/pugixml.cpp
    ./pugixml/src/pugixml.hpp
    ./pugixml/src/pugiconfig.hpp
)

add_library(
    figures_lib
    ./generator/plane.cpp
    ./generator/box.cpp
    ./generator/sphere.cpp
    ./generator/cone.cpp
    ./generator/torus.cpp
    ./generator/roof.cpp
    ./generator/piramid.cpp
    ./generator/parallelepiped.cpp
    ./generator/bezier.cpp
)

# Associate libraries with executables
target_link_libraries(generator utils_lib figures_lib)
target_link_libraries(engine utils_lib figures_lib pugixml_lib)

# Find OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/pugixml/src)

if(WIN32)
    message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})
    set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")

    if(NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
        message(ERROR ": GLUT not found")
    endif(NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")

    if (NOT EXISTS "${TOOLKITS_FOLDER}/glew/GL/glew.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glew/glew32.lib")
        message(ERROR ": GLEW not found")
    endif (NOT EXISTS "${TOOLKITS_FOLDER}/glew/GL/glew.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glew/glew32.lib")

    if (NOT EXISTS "${TOOLKITS_FOLDER}/devil/IL/il.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/devil/IL/il.h")
        message(ERROR ": DevIL not found")
    endif (NOT EXISTS "${TOOLKITS_FOLDER}/devil/IL/il.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/devil/IL/il.h")

    include_directories(${TOOLKITS_FOLDER}/glut ${TOOLKITS_FOLDER}/glew ${TOOLKITS_FOLDER}/devil)
    target_link_libraries(engine ${OPENGL_LIBRARIES} 
        ${TOOLKITS_FOLDER}/glut/glut32.lib
        ${TOOLKITS_FOLDER}/glew/glew32.lib
        ${TOOLKITS_FOLDER}/devil/devIL.lib
        pugixml_lib)

    target_link_libraries(generator ${OPENGL_LIBRARIES} ${TOOLKITS_FOLDER}/glut/glut32.lib
        ${TOOLKITS_FOLDER}/glew/glew32.lib
        pugixml_lib)

    if (EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll"  AND EXISTS "${TOOLKITS_FOLDER}/glew/glew32.dll" AND EXISTS "${TOOLKITS_FOLDER}/devil/IL/il.h")
        file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
        file(COPY ${TOOLKITS_FOLDER}/devil/devil.dll DESTINATION ${CMAKE_BINARY_DIR})
        file(COPY ${TOOLKITS_FOLDER}/glew/glew32.dll DESTINATION ${CMAKE_BINARY_DIR})
    endif(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll"  AND EXISTS "${TOOLKITS_FOLDER}/glew/glew32.dll" AND EXISTS "${TOOLKITS_FOLDER}/devil/IL/il.h")

else(WIN32)
    # Linux and Mac specific configurations
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")
    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIR})
    link_directories(${GLUT_LIBRARY_DIRS})
    add_definitions(${GLUT_DEFINITIONS})

    find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS})

    # Find DevIL
    find_package(DevIL REQUIRED)
    include_directories(${IL_INCLUDE_DIR})

    target_link_libraries(engine PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${IL_LIBRARIES})
    target_link_libraries(generator PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

    if(NOT GLUT_FOUND)
        message(ERROR ": GLUT not found!")
    endif(NOT GLUT_FOUND)
endif(WIN32)

