# OpenGL 3D Graphics Library

OpenGL 을 기반으로한 3D Graphic Library

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