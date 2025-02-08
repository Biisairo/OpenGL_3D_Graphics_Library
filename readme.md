# BLOOMING GRACE 김동윤 과제

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

## 구현 설명

### 사용 언어
C++
#### 사용한 이유
다른 고수준 언어들이 정신적으로도 물리적으로도 계승하고 있는 언어라고 생각합니다.<br>
C++ 과같은 저수준의 언어를 공부하며 기본적인 CS 를 익힐 수 있었습니다.<br>
이번 과제에서는 OpenGL 이 구현된 C 를 원횔하게 사용할 수 있는 언어로써 선택하였으며<br>
개인적으로는 많은것이 자동으로 처리되는 고수준의 언어보다<br>
직접 컨트롤해야 할 필요가 있는 저수준의 언어를 좋아하기에 선택하였습니다.

### 사용 라이브러리
OpenGL
- GLFW, GLAD, GLM
- OpenGL 관련 라이브러리
#### 사용한 이유
비록 지금은 Windows 의 DirectX 나 Mac 의 Metal 만큼 많이 쓰이지는 않지만<br>
vulkan 을 포함해 4개의 그래픽 라이브러리 중 가장 처음 나온 라이브러리이고<br>
기본적인 그래픽스 기술을 습득하고 이번 과제를 해결하기에 충분히 문제가 없을 것 같다고 생각하여 선택하였습니다.

Dear ImGui
- GUI 라이브러리
#### 사용한 이유
Mesh 추가, 제거, 제어를 위한 컨트롤 패널을 만드는데 사용하였습니다.<br>
해당 기능을 직관적으로 구현하기 위한 Gui 라이브러리가 필요했고<br>
이를 위해 사용할 수있는 가장 간단한 라이브러리가고 생각하여 선택하였습니다.

### 개발 환경
- 2020 M1 MacBook Air
- Sonoma 14.1.2
#### 사용한 이유
성인이 된 후로 Windows 가 아닌 Mac 을 계속 사용 해 왔으며<br>
현재도 Windows 컴퓨터는 회사에서, 집에서는 Mac 북을 사용하고 있습니다.<br>
지금은 Windows 컴퓨터보다 Mac 을 사용하는것이 더 편하여 사용하고 있으며<br>
Windows 의 WSL 과 달리 추가 설정없이 Terminal 을 이용해<br>
cli tool 을 편하게 사용할 수 있다는 점에서 계속 사용하고있습니다.