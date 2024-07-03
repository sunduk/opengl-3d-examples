cmake_minimum_required (VERSION 3.8)

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
  "resources/shaders/VertexColor.vs"
  "resources/shaders/VertexColor.fs"
  "resources/shaders/Color.vs"
  "resources/shaders/Color.fs"
  "resources/shaders/ColorTexture.vs"
  "resources/shaders/ColorTexture.fs"
  "resources/shaders/Texture.vs"
  "resources/shaders/Texture.fs"
  "resources/shaders/Lambert.vs"
  "resources/shaders/Lambert.fs"
  "resources/shaders/HalfLambert.vs"
  "resources/shaders/HalfLambert.fs"
  "resources/shaders/HalfLambertTexture.vs"
  "resources/shaders/HalfLambertTexture.fs"
  "resources/shaders/Rim.vs"
  "resources/shaders/Rim.fs"
  "resources/shaders/RimTexture.vs"
  "resources/shaders/RimTexture.fs"
  "resources/shaders/Outline.vs"
  "resources/shaders/Outline.fs"
  "resources/shaders/OutlineTexture.vs"
  "resources/shaders/Thickness.vs"
  "resources/shaders/Thickness.fs"
  "resources/shaders/ThicknessHalfLambert.vs"
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
  "src/common/CatmullRomSpline.h"
  "src/common/CatmullRomSpline.cpp"
  "src/common/Hermite.h"
  "src/common/Hermite.cpp"
  "src/common/HermiteSpline.h"
  "src/common/HermiteSpline.cpp"
  "src/common/BezierSpline.h"
  "src/common/BezierSpline.cpp"
  "src/common/Bezier.h"
  "src/common/Bezier.cpp"
  "src/common/Line.h"
  "src/common/Line.cpp"
  "src/common/LineShape.h"
  "src/common/LineShape.cpp"
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
  "src/common/ObjLoader.h"
  "src/common/ObjLoader.cpp"
)
source_group("ExamplesCommon" FILES ${EXAMPLES_COMMON})

########################################################
# Example00
file(GLOB EXAMPLE00
  "src/Example00.cpp" 
  "src/Example00.h"
)
source_group("Example00_Test" FILES ${EXAMPLE00})

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

########################################################
# Example11
file(GLOB EXAMPLE11
  "src/Example11.cpp" 
  "src/Example11.h"
)
source_group("Example11_ObjLoading" FILES ${EXAMPLE11})

########################################################
# Example12
file(GLOB EXAMPLE12
  "src/Example12.cpp" 
  "src/Example12.h"
)
source_group("Example12_Shader" FILES ${EXAMPLE12})

########################################################
# Example13
file(GLOB EXAMPLE13
  "src/Example13.cpp" 
  "src/Example13.h"
)
source_group("Example13_Curve" FILES ${EXAMPLE13})

add_executable (ExampleMain 
  ${EXTERNALS_GLAD}
  ${RESOURCES}
  ${EXAMPLES_MAIN}
  ${EXAMPLES_COMMON}
  ${EXAMPLE00}
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
  ${EXAMPLE11}
  ${EXAMPLE12}
  ${EXAMPLE13}
)

target_link_libraries(ExampleMain
  debug ${CMAKE_CURRENT_SOURCE_DIR}/externals/glfw/generated/src/debug/glfw3.lib
  optimized ${CMAKE_CURRENT_SOURCE_DIR}/externals/glfw/generated/src/release/glfw3.lib

  debug ${CMAKE_CURRENT_SOURCE_DIR}/externals/glew-2.1.0/generated/lib/debug/libglew32d.lib
  optimized ${CMAKE_CURRENT_SOURCE_DIR}/externals/glew-2.1.0/generated/lib/release/libglew32.lib

  opengl32.lib
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ExampleMain)