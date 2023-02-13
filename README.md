# opengl-3d-examples

Learn 3D rendering by OpenGL

![](https://github.com/sunduk/opengl-3d-examples/blob/main/doc/triangle.png)

![](https://github.com/sunduk/opengl-3d-examples/blob/main/doc/box.png)

![](https://github.com/sunduk/opengl-3d-examples/blob/main/doc/pyramid.png)


<br/>

## Build(VisualStudio)

> 빌드파일을 생성하려면 **[CMake](https://cmake.org/)** 가 설치되어 있어야 합니다.

### External libraries빌드

#### glew-2.1.0 빌드(최초 한번만 수행)

- */externals/glew-2.1.0/generated* 폴더로 이동
- **run_cmake.bat** 실행
- *generated*폴더에 생성된 **glew.sln** 파일을 더블클릭 하여 열기
- **glew_s**프로젝트를 Debug, Release 모드로 각각 빌드 수행
- 빌드 완료 후 아래 파일들이 생성되는지 확인
```
/externals/glew-2.1.0/generated/lib/Debug/libglew32d.lib
/externals/glew-2.1.0/generated/lib/Release/libglew32.lib
```

#### glfw 빌드(최초 한번만 수행)

- */externals/glfw/generated* 폴더로 이동
- **run_cmake.bat** 실행
- *generated*폴더에 생성된 **GLFW.sln** 파일을 더블클릭 하여 열기
- **glfw**프로젝트를 Debug, Release 모드로 각각 빌드 수행
- 빌드 완료 후 아래 파일들이 생성되는지 확인
```
/externals/glfw/generated/src/Debug/glfw3.lib
/externals/glfw/generated/src/Release/glfw3.lib
```

### 예제 프로젝트 빌드

- */build* 폴더로 이동
- **run_cmake.bat** 실행
- *generated*폴더에 생성된 **Examples.sln** 파일을 더블클릭 하여 열기
- **ExampleMain**프로젝트를 Debug, Release 모드로 각각 빌드 수행
- F5 또는 디버깅 -> 디버깅 시작 메뉴를 눌러 예제 프로그램 실행


<br/>

## External libraries

> 프로젝트에 포함되어 있으므로 별도로 설치할 필요는 없습니다.

| name       | version            | url                                                     | purpose                 |
|------------|--------------------|---------------------------------------------------------|-------------------------|
| glfw       | 3.3.8              | https://github.com/glfw/glfw                            | 윈도우 생성, 이벤트 처리  |
| glew       | 2.1.0              | https://glew.sourceforge.net/                           | OpenGL 확장 기능         |
| glad       | gl:4.6 / gles:2.0  | https://glad.dav1d.de/                                  | OpenGL 드라이버 연동     |
| glm        | 0.9.9              | https://github.com/g-truc/glm                           | 수학 라이브러리          |
| stb_image  | 2.27               | https://github.com/nothings/stb/blob/master/stb_image.h | 이미지 파일 로딩         |

<br/>
