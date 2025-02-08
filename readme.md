# OpenGL 3D Graphics Library

## Require
CMake

## Build
```shell
mkdir build
cd build
cmake ..
cmake --build . -j 16
```

## Run
```shell
./opengl_engine
```

## Key Input
이동 - ```WASD, 방향키```<br>
메뉴창 열기 - ```ESC```<br>
좌표 점 표시/제거 - ```C```<br>
시점 전환 - ```마우스```

## 구현 기능
Scene 을 이용한 Object 의 랜더링<br>
Mesh 가 가지고 있는 데이터에 따라 세이더를 동적 컴파일 후 사용<br>
퐁 쉐이딩<br>
Framebuffer 를 이용한 그림자 구현<br>
Framebuffer 를 이용한 HDR