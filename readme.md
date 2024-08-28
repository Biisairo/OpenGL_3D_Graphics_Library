우선순위
mesh, camera, light
object
vertexbuffer manater
shader manager
pipeline manager
framebuffer manager
uniform block manager

Rendering System
{
	handling buffer
		handling vertex buffer
			make vertex buffer
			update vertex buffer
			delete vertex buffer
		handling framebuffer

	handling texture

	handling shader
		handling shader program
		handling uniform

	handling scene hierarchy
		handling object hierarchy transform
	
	handling camera
		handling camera matrix and put it to uniform
	
	handling light, shadow, fog


	draw call

	handling status
		render mode, depth test

	rendering pipeline

	rendering optimize
		optimize draw call
		culling
		lod
		memory manage
	
	effect
		post processing
		effect
			particle
			fog
			PBR
}

// shader manager
{
	shader 들을 관리
	shader 들을 컴파일하여 id 로 들고있는다
	이후 pipeline 을 만들 때 id 를 전달

	모든 shader 는 같은 인풋을 가지도록 하여 복잡도를 줄인다
	대신 shader code 내부에서 없을때의 예외코드를 잘 작성
	rendering systemp 에서 특정 인자가 없는 경우 전달을 잘 하도록 맞추기
}

// pipeline manager
{
	shader manager 에서 shader id 를 받아서 pipeline 을 만든다
	만들어진 각각의 pipeline 을 들고있는다
	이후 render 과정에서 pipeline 을 가져다가 사용

	uniform buffer 를 전달 할 수 있도록 한다
}

framebuffer manager
{
	랜더링 되는 프래임버퍼 및 texture 관리
}

vertex buffer manager
{
	각 mesh 에서 전달되는 값 관리
	없는 인자는 shader 에 맞게 이곳에서 관리한다
}

uniform block manager
{
	특정 program 에 맞게 인자가 들어갈 수 있도록 한다

	program 의 멤버변수로? - 고민
}

scene manager
{
	load scene

	save scene
}

material, texture manager
{
	물체의 material 과 texture 관리...?
}

// mesh
{
	mat4x4 model
	vec3 position

	parent
	children
	
	vector<vec4> vertex
	vector<uint> index
	vector<vec3> normal
	vector<vec2> UV
	vector<vec4> color
}

// camera
{
	mat4x4 model
	vec3 position

	e_camera_type camera_type
	- camera 중심
	- player 중심
	e_projection_type projection_type
	- perspective
	- ortho

	mat4x4 projection
	mat4x4 view

	vec3 up
	vec3 right

	float min_dist
	float max_dist
}

light
{
	mat4x4 model
	vec3 position

	vec4 color

	vec3 direction
	float angle
	float 기타 여러 값들
}

object
{
	parent
	children
}

control 은 window 에 종속
window 는 glfw 의 변수
glfw 는 opengl library
window 는 device 내에 있어야함
device - 외부 class 에 key 별로 연결되는 값 필요
key 의 경우 enum 으로 변환
각 key, button 및 콜백의 인자들을 전부 변수화?
아후 control 에 변수 전달 - contol 이 알아서 처리
mouse move 는? - delta time 과 offset 값을 저장, 사용할때마다 초기화, 사용안하면 더해짐