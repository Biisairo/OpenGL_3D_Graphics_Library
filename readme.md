# OpenGL 3D Graphics Library

목표 : OpenGL 을 기반으로한 3D Graphic Library 제작

<img src="https://github.com/user-attachments/assets/ad9a6850-8066-4f58-a740-d0d7fbc34dbd" height=500>
<img src="https://github.com/user-attachments/assets/864d611f-68c6-454d-92cd-9dcc9d3478a5" height=500>

## Device
실제 OpenGL 관련 함수들이 불려지는 클래스
### Todo
- [x] Mesh 등록
- [x] Uniform Buffer
- [x] Program 컴파일
- [ ] 기능 분리
- [ ] Texture
- [ ] Frame Buffer
- [ ] Shadow

## IResourceID
IObject3D 객체의 ID 값을 할당해주는 인터페이스

## IObject3D
공간상에 올라가는 모든 객체의 인터페이스

## Mesh
Vertex 정보 및 Object 특성을 담고있는 클래스

## Material
Mesh 의 물질정보를 담고있는 클래스

## Camera
View, Position matrix 를 생성해주는 카메라 클래스

## Light
빛 정보를 담고있는 클래스

## Scene
실제 랜더되는 Render Scene
