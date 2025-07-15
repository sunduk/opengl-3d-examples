# opengl-3d-examples

["기초부터 배운다! 3D 게임 프로그래밍" 위키독스 전자책](https://wikidocs.net/book/18000)

- [![책 표지](https://wikidocs.net/images//book/%EC%B1%85%ED%91%9C%EC%A7%80_dTzNIgx_xSAeYIf_RUCtpIE_ltiJYhc_bul7PTp_oPZ4IHz_O2jv5v5_OZoGCJ6_ngTDF5c_vJ6maWF.png)](https://wikidocs.net/book/18000)
- 이 책과 소스코드를 함께 보시면 학습하기에 더 좋습니다.

---



[한글문서(Korean documents)](https://github.com/sunduk/opengl-3d-examples/blob/main/README-ko.md)

Learn 3D rendering by OpenGL

- Making an OpenGL window.
- Drawing triangles, colors and textures.
- Making vertex buffers and index buffers.
- Transform coordinates.
- Making a camera.
- Lambert lighting shader.
- Making a 3D scene.

![](https://github.com/sunduk/opengl-3d-examples/blob/main/doc/triangle.png)

![](https://github.com/sunduk/opengl-3d-examples/blob/main/doc/box.png)

![](https://github.com/sunduk/opengl-3d-examples/blob/main/doc/pyramid.png)

![](https://github.com/sunduk/opengl-3d-examples/blob/main/doc/objloading.png)

<br/>

## Build(VisualStudio)

> You need to install **[CMake](https://cmake.org/)** to generate build files.

### Build external libraries.

#### glew-2.1.0(Performs only once for the first time)

- Move to */externals/glew-2.1.0/generated* folder.
- Execute **run_cmake.bat**.
- Double click **glew.sln** in *generated* folder.
- Build **glew_s** project in Debug and Release mode.
- After the build is complete, check if the following files are created.
```
/externals/glew-2.1.0/generated/lib/Debug/libglew32d.lib
/externals/glew-2.1.0/generated/lib/Release/libglew32.lib
```

#### glfw(Performs only once for the first time)

- Move to */externals/glfw/generated* folder.
- Execute **run_cmake.bat**.
- Double click **GLFW.sln** in *generated* folder.
- Build **glfw** project in Debug and Release mode.
- After the build is complete, check if the following files are created.
```
/externals/glfw/generated/src/Debug/glfw3.lib
/externals/glfw/generated/src/Release/glfw3.lib
```

### Build an example project.

- Move to */build* folder.
- Execute **run_cmake.bat**.
- Double click **Examples.sln** in *build* folder.
- Build **ExampleMain** project in Debug and Release mode.
- Press F5 or Go to Debugging -> Start debug.
- ![](https://github.com/sunduk/opengl-3d-examples/blob/main/doc/menu.png)
- Input an example number and press **_ENTER_** key then it'll execute.


<br/>

## External libraries

> These libraries are included in this project so you don't need to install it separately.

| name       | version            | url                                                     | purpose                 |
|------------|--------------------|---------------------------------------------------------|-------------------------|
| glfw       | 3.3.8              | https://github.com/glfw/glfw                            | Making a window. Event handling. |
| glew       | 2.1.0              | https://glew.sourceforge.net/                           | OpenGL extensions.         |
| glad       | gl:4.6 / gles:2.0  | https://glad.dav1d.de/                                  | OpenGL drivers.     |
| glm        | 0.9.9              | https://github.com/g-truc/glm                           | Math library.          |
| stb_image  | 2.27               | https://github.com/nothings/stb/blob/master/stb_image.h | Loading image files.         |

<br/>
