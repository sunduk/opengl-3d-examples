﻿cmake_minimum_required (VERSION 3.8)

project ("Examples")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/externals)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/externals/glad/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/externals/glew-2.1.0/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/externals/glfw/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/externals/glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/common)


# Visual Studio filters

########################################################
# Externals
file(GLOB EXTERNALS_GLAD
  "externals/glad/include/glad/glad.h"
  "externals/glad/include/KHR/khrplatform.h"
  "externals/glad/src/glad.c"
)
source_group("Externals/glad" FILES ${EXTERNALS_GLAD})

########################################################
# Resources
file(GLOB RESOURCES
  "resources/shaders/Color.vs"
  "resources/shaders/Color.fs"
  "resources/shaders/Lambert.vs"
  "resources/shaders/Lambert.fs"
  "resources/shaders/LambertTexture.vs"
  "resources/shaders/LambertTexture.fs"
  "resources/shaders/MVP.vs"
)
source_group("Resources/Shaders" FILES ${RESOURCES})

########################################################
# ExamplesMain
file(GLOB EXAMPLES_MAIN 
  "src/Examples_Main.cpp"
  "src/Examples_Main.h"
)
source_group("Examples_Main" FILES ${EXAMPLES_MAIN})

########################################################
# Common
file(GLOB EXAMPLES_COMMON
  "src/common/BoxShape.h"
  "src/common/Camera.h"
  "src/common/Camera.cpp"
  "src/common/DirectionalLight.h"
  "src/common/DirectionalLight.cpp"
  "src/common/GameObject.h"
  "src/common/GameObject.cpp"
  "src/common/Material.h"
  "src/common/Material.cpp"
  "src/common/Mesh.h"
  "src/common/Mesh.cpp"
  "src/common/RenderWindow.h"
  "src/common/RenderWindow.cpp"
  "src/common/Scene.h"
  "src/common/Scene.cpp"
  "src/common/SceneManager.h"
  "src/common/SceneManager.cpp"
  "src/common/Shader.h"
  "src/common/Shader.cpp"
  "src/common/SimpleMesh.h"
  "src/common/SimpleMesh.cpp"
  "src/common/SimpleTransform.h"
  "src/common/SimpleTransform.cpp"
  "src/common/Transform.h"
  "src/common/Transform.cpp"
  "src/common/Vertex.h"
  "src/common/WindowParam.h"
)
source_group("ExamplesCommon" FILES ${EXAMPLES_COMMON})

########################################################
# Example01
file(GLOB EXAMPLE01
  "src/Example01.cpp" 
  "src/Example01.h"
)
source_group("Example01_Window" FILES ${EXAMPLE01})

########################################################
# Example02
file(GLOB EXAMPLE02
  "src/Example02.cpp" 
  "src/Example02.h"
)
source_group("Example02_Triangle" FILES ${EXAMPLE02})

########################################################
# Example03
file(GLOB EXAMPLE03
  "src/Example03.cpp" 
  "src/Example03.h"
)
source_group("Example03_Color" FILES ${EXAMPLE03})

########################################################
# Example04
file(GLOB EXAMPLE04
  "src/Example04.cpp" 
  "src/Example04.h"
)
source_group("Example04_Texture" FILES ${EXAMPLE04})

########################################################
# Example05
file(GLOB EXAMPLE05
  "src/Example05.cpp" 
  "src/Example05.h"
)
source_group("Example05_TextureMixing" FILES ${EXAMPLE05})

########################################################
# Example06
file(GLOB EXAMPLE06
  "src/Example06.cpp" 
  "src/Example06.h"
)
source_group("Example06_Mesh" FILES ${EXAMPLE06})

########################################################
# Example07
file(GLOB EXAMPLE07
  "src/Example07.cpp" 
  "src/Example07.h"
)
source_group("Example07_Shader" FILES ${EXAMPLE07})

########################################################
# Example08
file(GLOB EXAMPLE08
  "src/Example08.cpp" 
  "src/Example08.h"
)
source_group("Example08_Transform" FILES ${EXAMPLE08})

########################################################
# Example09
file(GLOB EXAMPLE09
  "src/Example09.cpp" 
  "src/Example09.h"
)
source_group("Example09_MVP" FILES ${EXAMPLE09})

########################################################
# Example10
file(GLOB EXAMPLE10
  "src/Example10.cpp" 
  "src/Example10.h"
)
source_group("Example10_Scene" FILES ${EXAMPLE10})

add_executable (ExampleMain 
  ${EXTERNALS_GLAD}
  ${RESOURCES}
  ${EXAMPLES_MAIN}
  ${EXAMPLES_COMMON}
  ${EXAMPLE01}
  ${EXAMPLE02}
  ${EXAMPLE03}
  ${EXAMPLE04}
  ${EXAMPLE05}
  ${EXAMPLE06}
  ${EXAMPLE07}
  ${EXAMPLE08}
  ${EXAMPLE09}
  ${EXAMPLE10}
)

target_link_libraries(ExampleMain
  debug ${CMAKE_CURRENT_SOURCE_DIR}/externals/glfw/generated/src/debug/glfw3.lib
  optimized ${CMAKE_CURRENT_SOURCE_DIR}/externals/glfw/generated/src/release/glfw3.lib

  debug ${CMAKE_CURRENT_SOURCE_DIR}/externals/glew-2.1.0/generated/lib/debug/libglew32d.lib
  optimized ${CMAKE_CURRENT_SOURCE_DIR}/externals/glew-2.1.0/generated/lib/release/libglew32.lib

  opengl32.lib
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ExampleMain)