#include "SimulationView.h"

#include <limits>
#include <math.h>
#include <map>
#include <vector>
#include <glm/gtx/projection.hpp>


unsigned int g_SphereModelId;
unsigned int g_SphereMaterialId;
unsigned int g_TreeMaterialId;
unsigned int g_FirTreeModelId;
unsigned int g_SphereTextureId;

const float SHIP_SCALE = 0.5f;

Ball* g_Ball;

std::map<int, GameObject*> g_PartialMeshObjects;
std::map<int, GameObject*>::iterator g_PartialMeshObjectsCursor;

SimulationView::SimulationView(){

}

SimulationView::~SimulationView(){
	delete m_PhysicsDebugRenderer;
}

void SimulationView::Initialize(int DemoId){
	m_CameraPosition.Set(0.f, 1.0f, 0.0f);
	m_CameraDirection.Set(0.f, 0.f, 1.f);

	m_FreeMotionMouse = true;

	// Load Models
	unsigned int planeModelId = -1;
	GDP_LoadModel(planeModelId, "assets/models/plane.obj");

	// Load Textures
	unsigned int planeTextureId = -1;
	GDP_LoadTexture(planeTextureId, "assets/textures/grid.png");

	// Create Material
	unsigned int groundMaterialId = -1;
	GDP_CreateMaterial(groundMaterialId, planeTextureId, color(1, 1, 1));

	m_PhysicsDebugRenderer = new PhysicsDebugRenderer();

	float min[3] = { -20.f, -1.f, -20.f };
	float max[3] = { 20.f, 1.f, 20.f };
	AABB* groundAABB = new AABB(min, max);

	Triangle* groundTriangle = new Triangle(Point(-20, 0, 20), Point(-20, -10, -20), Point(20, 0, -20));

	BoundingBox* groundBoundingBox = new BoundingBox();
	groundBoundingBox->centerPoint.Set(0.0f, 0.0f, 0.0f);
	groundBoundingBox->halfExtents.Set(20.0f, 1.0f, 20.0f);
	groundBoundingBox->minPoints.Set(min[0], min[1], min[2]);
	groundBoundingBox->maxPoints.Set(max[0], max[1], max[2]);

	PhysicsObject* physicsGround = m_PhysicsSystem.CreatePhysicsObject(Vector3(0, 0, 0), groundAABB);
	physicsGround->pShape = groundAABB;
	physicsGround->SetMass(-1.f);
	physicsGround->pBoundingBox = groundBoundingBox;

	// Create a sphere
	GDP_LoadModel(g_SphereModelId, "assets/models/sphere.obj");
	GDP_LoadModel(g_FirTreeModelId, "assets/models/Fir_Tree.fbx");

	// Load Textures
	GDP_LoadTexture(g_SphereTextureId, "assets/textures/white.png");

	// Create Material
	GDP_CreateMaterial(g_SphereMaterialId, g_SphereTextureId, color(1, 0, 0));
	GDP_CreateMaterial(g_TreeMaterialId, g_SphereTextureId, color(0, 1, 0));

	//Create a ground plane
	GameObject* ground = GDP_CreateGameObject();
	ground->Renderer.ShaderId = 1;
	ground->Renderer.MaterialId = groundMaterialId;
	ground->Renderer.MeshId = planeModelId;
	ground->Scale = glm::vec3(20, 1, 20);

	m_PhysicsDebugRenderer->AddPhysicsObject(physicsGround);
	//PrepareDemo();

	for (int i = 10; i >= -10; i-=2) {
		Ball* b = CreateBall(Vector3(0, 3, i), 0.98f);
		m_Balls.push_back(*b);
		if (i < 0) b->physicsObject->type = 1 << 6;
		else b->physicsObject->type = 1 << 3;
	}

	//LoadStaticModelToOurAABBEnvironment("assets/models/terrain.obj", Vector3(-40, -160, 400), 1.0f);

	//LoadStaticModelToOurAABBEnvironment("assets/models/Fir_Tree.obj", Vector3(4, 4, 4), 1.f);
	//LoadStaticModelToOurAABBEnvironment("assets/models/de--lorean.obj", Vector3(4, 4, 4), 1.f);


	// Create separate objects composed of all of the triangles within each AABB
	// Hash tied to the id of the mesh we create
	/*const std::map<int, std::vector<Triangle*>> aabb = m_PhysicsSystem.GetAABBStructure();
	std::map<int, std::vector<Triangle*>>::const_iterator aabbIt = aabb.begin();

	for (; aabbIt != aabb.end(); aabbIt++)
	{
		int hashValue = (*aabbIt).first;
		std::vector<Triangle*> triangles = (*aabbIt).second;

		std::vector<glm::vec3> vertices;
		std::vector<int> faces;

		for (int i = 0; i < triangles.size(); i++)
		{
			Triangle* triangle = triangles[i];
			vertices.push_back(triangle->A.GetGLM());
			vertices.push_back(triangle->B.GetGLM());
			vertices.push_back(triangle->C.GetGLM());

			faces.push_back(i * 3);
			faces.push_back(i * 3 + 1);
			faces.push_back(i * 3 + 2);
		}

		unsigned int modelId = -1;
		GDP_CreateModel(modelId, vertices, faces);

		gdp::GameObject* partialMeshGameObject = GDP_CreateGameObject();
		partialMeshGameObject->Position = glm::vec3(0.0f);
		partialMeshGameObject->Renderer.ShaderId = 1;
		partialMeshGameObject->Renderer.MaterialId = g_SphereMaterialId;
		partialMeshGameObject->Renderer.MeshId = modelId;
		partialMeshGameObject->Scale = glm::vec3(1.0f);
		partialMeshGameObject->Enabled = false;

		g_PartialMeshObjects[hashValue] = partialMeshGameObject;
	}

	g_PartialMeshObjectsCursor = g_PartialMeshObjects.begin();

	int check_aabb_gameobjects = 0;

	g_Ball = CreateBall(Vector3(0.0f, 0.0f, 0.0f), 2.0f);

	int breakhere = 0;*/
}

void SimulationView::Destroy() {

}



int CalculateHashValue(float x, float y, float z)
{
	int hashValue = 0;

	assert(x + 128 > 0);
	assert(y + 300 > 0);
	assert(z + 128 > 0);

	hashValue += floor(x + 128) / 100 * 10000;
	hashValue += floor(y + 300) / 100 * 100;
	hashValue += floor(z + 128) / 100;
	return hashValue;
}

int CalculateHashValue(const Vector3& v)
{
	return CalculateHashValue(v.x, v.y, v.z);
}

void SimulationView::LoadStaticModelToOurAABBEnvironment(const std::string& filepath, const Vector3& position, float scale)
{
	// GalacticaOriginal_ASCII_no_text.ply
	unsigned int m_ShipModelId = -1;
	GDP_LoadModel(m_ShipModelId, filepath.c_str());

	std::vector<glm::vec3> vertices;
	std::vector<int> triangles;

	unsigned int unused1, unused2;
	printf("Starting to load Large Model...\n");
	GDP_GetModelData(m_ShipModelId, vertices, triangles, unused1, unused2);
	printf("Done loading large model!\n");
	Vector3 minPoints = Vector3(FLT_MAX, FLT_MAX, FLT_MAX);
	Vector3 maxPoints = Vector3(FLT_MIN, FLT_MIN, FLT_MIN);
	glm::vec3 pos = position.GetGLM();
	for (int i = 0; i < vertices.size(); i++) {
		glm::vec3& vertex = vertices[i];
		//vertex *= scale;
		vertex += pos;

		if (minPoints.x > vertex.x)
			minPoints.x = vertex.x;
		if (minPoints.y > vertex.y)
			minPoints.y = vertex.y;
		if (minPoints.z > vertex.z)
			minPoints.z = vertex.z;

		if (maxPoints.x < vertex.x)
			maxPoints.x = vertex.x;
		if (maxPoints.y < vertex.y)
			maxPoints.y = vertex.y;
		if (maxPoints.z < vertex.z)
			maxPoints.z = vertex.z;
	}

	printf("MinPoints: (%.2f, %.2f, %.2f)\nMaxPoints: (%.2f, %.2f, %.2f)\n",
		minPoints.x, minPoints.y, minPoints.z,
		maxPoints.x, maxPoints.y, maxPoints.z);

	/** For rendering purposes only.. **/
	m_BigShipGamObject = GDP_CreateGameObject();
	m_BigShipGamObject->Position = pos;
	m_BigShipGamObject->Renderer.ShaderId = 1;
	m_BigShipGamObject->Renderer.MaterialId = g_SphereMaterialId;
	m_BigShipGamObject->Renderer.MeshId = m_ShipModelId;
	m_BigShipGamObject->Scale = glm::vec3(1.0f);
	m_BigShipGamObject->Enabled = true;
	/** End for rendering only **/

	for (int i = 0; i < triangles.size(); i+= 3)
	{
		Point a = Point(vertices[i] + pos);
		Point b = Point(vertices[i + 1] + pos);
		Point c = Point(vertices[i + 2] + pos);

		int hashA = CalculateHashValue(a);
		int hashB = CalculateHashValue(b);
		int hashC = CalculateHashValue(c);

		//printf("(%.2f, %.2f, %.2f) -> %d\n", a.x, a.y, a.z, hashA);
		//printf("(%.2f, %.2f, %.2f) -> %d\n", b.x, b.y, b.z, hashB);
		//printf("(%.2f, %.2f, %.2f) -> %d\n", c.x, c.y, c.z, hashC);

		Triangle* newTriangle = new Triangle(a, b, c);

		//m_PhysicsSystem.AddTriangleToOctTree(newTriangle);

		m_PhysicsSystem.AddTriangleToAABBCollisionCheck(hashA, newTriangle);

		if (hashA != hashB)
			m_PhysicsSystem.AddTriangleToAABBCollisionCheck(hashB, newTriangle);

		if (hashC != hashB && hashC != hashA)
			m_PhysicsSystem.AddTriangleToAABBCollisionCheck(hashC, newTriangle);
	}

}

void SimulationView::CreateTree(const Vector3& position, float scale) {
	unsigned int unused1, unused2;
	std::vector<glm::vec3> vertices;
	std::vector<int> triangles;
	GDP_GetModelData(g_FirTreeModelId, vertices, triangles, unused1, unused2);

	// Create our mesh inside the physics system
	for (int i = 0; i < triangles.size(); i += 3) {
		int indexA = i;
		int indexB = i + 1;
		int indexC = i + 2;

		// HACK to save time from fixing the vertices returned from the GDP Graphics library
		if (indexA + 2 >= vertices.size()) {
			printf("Skipping creating a triangle!\n");
			continue;
		}

		Vector3 vertexA = Vector3(vertices[indexA]) * scale + position;
		Vector3 vertexB = Vector3(vertices[indexB]) * scale + position;
		Vector3 vertexC = Vector3(vertices[indexC]) * scale + position;

		Triangle* triangle = new Triangle(vertexA, vertexB, vertexC);
		PhysicsObject* trianglePhysObj = m_PhysicsSystem.CreatePhysicsObject(position, triangle);
		trianglePhysObj->SetMass(-1.f);
	}

	// Create 1 Instance of the tree to be rendered
	// While creating number of triangles x instances of Triangles
	// for collision detection.
	gdp::GameObject* tree = GDP_CreateGameObject();
	tree->Position = glm::vec3(position.x, position.y, position.z);
	tree->Renderer.ShaderId = 1;
	tree->Renderer.MaterialId = g_TreeMaterialId;
	tree->Renderer.MeshId = g_FirTreeModelId;
	tree->Scale = glm::vec3(1.0f) * scale;

}

Ball* SimulationView::CreateBall(const Vector3& position, float scale) {
	Sphere* otherSphere = new Sphere(Point(0.0f, 0.0f, 0.0f), scale);

	Ball* newBall = new Ball();
	newBall->physicsObject = m_PhysicsSystem.CreatePhysicsObject(position, otherSphere);
	newBall->gameObject = GDP_CreateGameObject();
	newBall->gameObject->Position = position.GetGLM();
	newBall->gameObject->Renderer.ShaderId = 1;
	newBall->gameObject->Renderer.MaterialId = g_SphereMaterialId;
	newBall->gameObject->Renderer.MeshId = g_SphereModelId;
	newBall->gameObject->Scale = glm::vec3(1, 1, 1) * scale;

	// Create a bounding box around our ball.
	//Vector3 halfExtents = m_BallBoundingBox.halfExtents;
	//newBall.physicsObject->pBoundingBox = &m_BallBoundingBox;
	//newBall.physicsObject->pBoundingBox->halfExtents = halfExtents * scale;

	//m_PhysicsDebugRenderer->AddPhysicsObject(newBall.physicsObject);

	return newBall;
}

void SimulationView::PrepareDemo() {

	//std::vector<glm::vec3> vertices;
	//std::vector<int> triangles;

	//unsigned int unused1, unused2;

	//GDP_GetModelData(g_SphereModelId, vertices, triangles, unused1, unused2);
	//Vector3 minPoints = Vector3(FLT_MAX, FLT_MAX, FLT_MAX);
	//Vector3 maxPoints = Vector3(FLT_MIN, FLT_MIN, FLT_MIN);
	//for (int i = 0; i < vertices.size(); i++) {
	//	glm::vec3& vertex = vertices[i];

	//	if (minPoints.x > vertex.x)
	//		minPoints.x = vertex.x;
	//	if (minPoints.y > vertex.y)
	//		minPoints.y = vertex.y;
	//	if (minPoints.z > vertex.z)
	//		minPoints.z = vertex.z;

	//	if (maxPoints.x < vertex.x)
	//		maxPoints.x = vertex.x;
	//	if (maxPoints.y < vertex.y)
	//		maxPoints.y = vertex.y;
	//	if (maxPoints.z < vertex.z)
	//		maxPoints.z = vertex.z;
	//}

	//// Calculate the point halfway between the minPoints, and maxPoints
	//Vector3 halfExtents = (maxPoints - minPoints) / 2.f;
	//Vector3 centerPoint = minPoints + halfExtents;

	//printf("Minimum Points: (%.2f, %.2f, %.2f)\n",
	//	minPoints.x,
	//	minPoints.y,
	//	minPoints.z);
	//printf("Maximum Points: (%.2f, %.2f, %.2f)\n",
	//	maxPoints.x,
	//	maxPoints.y,
	//	maxPoints.z);
	//printf("Half Extents: (%.2f, %.2f, %.2f)\n",
	//	halfExtents.x,
	//	halfExtents.y,
	//	halfExtents.z);
	//printf("Center Point: (%.2f, %.2f, %.2f)\n",
	//	centerPoint.x,
	//	centerPoint.y,
	//	centerPoint.z);

	//m_BallBoundingBox.centerPoint = centerPoint;
	//m_BallBoundingBox.halfExtents = halfExtents;
	//m_BallBoundingBox.maxPoints = maxPoints;
	//m_BallBoundingBox.minPoints = minPoints;


	Sphere* controlledSphere = new Sphere(Point(0.0f, 0.0f, 0.0f), 1.0f);

	//// Create our controlled ball
	m_ControlledBall.physicsObject = m_PhysicsSystem.CreatePhysicsObject(Vector3(1, 25, 0), controlledSphere);
	m_ControlledBall.gameObject = GDP_CreateGameObject();
	m_ControlledBall.gameObject->Renderer.ShaderId = 1;
	m_ControlledBall.gameObject->Renderer.MaterialId = g_SphereMaterialId;
	m_ControlledBall.gameObject->Renderer.MeshId = g_SphereModelId;
	m_ControlledBall.gameObject->Scale = glm::vec3(1, 1, 1);

	//// Create a bounding box around our ball.
	//m_ControlledBall.physicsObject->pBoundingBox = &m_BallBoundingBox;

	//m_PhysicsDebugRenderer->AddPhysicsObject(m_ControlledBall.physicsObject);

	//CreateTree(Vector3(0.0f), 0.025f);
	//CreateTree(Vector3(-10.0f, 0.0f, -10.0f), 0.025f);
	//CreateTree(Vector3(-10.0f, 0.0f,  10.0f), 0.025f);
	//CreateTree(Vector3( 10.0f, 0.0f, -10.0f), 0.025f);
	//CreateTree(Vector3( 10.0f, 0.0f,  10.0f), 0.025f);

	//for (int i = -20; i < 20; i+=3) {
	//	for (int j = -20; j < 20; j+=3) {
	//		CreateBall(Vector3(i, 20, j), 0.1f);
	//	}
	//}	
}

bool isClicked = false;
int MouseStaticPosX = 400;
int MouseStaticPosY = 400;



void SimulationView::Update(double dt) {
	m_PrevMouseX = m_CurrMouseX;
	m_PrevMouseY = m_CurrMouseY;
	GDP_GetMousePosition(m_CurrMouseX, m_CurrMouseY);
	int deltaMouseX = 0;
	int deltaMouseY = 0;

	if (GDP_IsKeyHeldDown('1')) {
		m_FreeMotionMouse = true;
	}
	else if (GDP_IsKeyHeldDown('2')) {
		MouseStaticPosX = m_CurrMouseX;
		MouseStaticPosY = m_CurrMouseY;
		glutSetCursor(GLUT_CURSOR_NONE);
		m_FreeMotionMouse = false;
	}

	if (m_FreeMotionMouse)
	{
		deltaMouseX = m_CurrMouseX - m_PrevMouseX;
		deltaMouseY = m_CurrMouseY - m_PrevMouseY;

		int state = 0;
		if (!m_IsMouseDown && GDP_GetMouseButtonState(0, state)) {
			m_IsMouseDown = true;
			m_MouseDownX = m_CurrMouseX;
			m_MouseDownY = m_CurrMouseY;

			// Fixes jumping across the screen from the previous position
			// being where the user last pressed the mouse
			m_PrevMouseX = m_MouseDownX;
			m_PrevMouseY = m_MouseDownY;

			deltaMouseX = m_CurrMouseX - m_PrevMouseX;
			deltaMouseY = m_CurrMouseY - m_PrevMouseY;
		}
		if (m_IsMouseDown && !GDP_GetMouseButtonState(0, state)) {
			m_IsMouseDown = false;
		}
	}
	else
	{
		// NOTE: SetCursorPos triggers a mouse motion!
		// NOTE: SetCursorPos is setting the mouse position according to the 
		//		 mouse position in the Window/Monitor 
		//       While we are calculating the delta positions based on the window
		// NOTE: 23 was discovered to be the size of the bar at the top of the window.

		glutWarpPointer(MouseStaticPosX, MouseStaticPosY);

		deltaMouseX = m_CurrMouseX - MouseStaticPosX;
		deltaMouseY = m_CurrMouseY - MouseStaticPosY;
	}

	//printf("%d %d -> %d %d\n", m_CurrMouseX, m_CurrMouseY, deltaMouseX, deltaMouseY);

	const float rotateSpeed = 0.01f;
	m_HorizontalAngle -= deltaMouseX * rotateSpeed;

	// PI defined as 3.14 ...
	// PI/2 = 90degrees
	// PI = 180 degrees
	// PI3/2 = 270 degrees
	// PI*2 = 360 degrees	~6.28...


	const float moveSpeed = 5.0f;


	m_CameraDirection.x = sin(m_HorizontalAngle);
	m_CameraDirection.z = cos(m_HorizontalAngle);
	m_CameraDirection.y -= deltaMouseY * rotateSpeed;

	Vector3 forwardVector(m_CameraDirection.x, 0.0f, m_CameraDirection.z);
	Vector3 rightVector(
		glm::cross(forwardVector.GetGLM(), glm::vec3(0, 1, 0))
	);

	if (GDP_IsKeyHeldDown('w')) {
		m_CameraPosition += forwardVector * moveSpeed * dt;
	}
	if (GDP_IsKeyHeldDown('a')) {
		m_CameraPosition -= rightVector * moveSpeed * dt;
	}
	if (GDP_IsKeyHeldDown('s')) {
		m_CameraPosition -= forwardVector * moveSpeed * dt;
	}
	if (GDP_IsKeyHeldDown('d')) {
		m_CameraPosition += rightVector * moveSpeed * dt;
	}


	SetCameraPosition(m_CameraPosition.GetGLM());
	SetCameraFacingDirection(m_CameraDirection.GetGLM());

	bool ClosestObject = GDP_IsKeyHeldDown('x');
	bool FirstObject = GDP_IsKeyHeldDown('z');


	if (ClosestObject || FirstObject) {
		if (!isClicked) {
			isClicked = true;

			// 1. Mouse Position
			// - X & Y Position with top Left origin (0,0)
			//   down is +iveY
			// 
			// 2. Viewport: Window Information 
			// - Width & Height of your window OpenGL Context
			// 
			// 3. Projection Matrix built from your perspective
			// - Field of View has to equal the value used for Rendering
			// - Aspect Ratio built from the width & height
			// - zNearPlane distance
			// - zFarPlane distance
			// 
			// 4. View Matrix is built from the camera transform
			// - Camera Position
			// - Camera Orientation (includes Up direction)


			int width = 1200;
			int height = 800;


			// 1. Cursor Position on the Screen
			glm::vec3 cursorPositionOnScreenSpace (
				m_CurrMouseX,				// X is fine from left to right
				height - m_CurrMouseY,	// Since Y is origin at the top, and positive as it goes down the screen
									// we need to fix it like this.
				1.f
			);


			// 2. Viewport: Window Information
			glm::vec4 viewport = glm::vec4(0, 0, width, height);


			// 3 Projection Matrix
			glm::mat4 projectionMatrix = glm::perspective(
				glm::radians(45.0f),			// Field of View
				(float)width / (float)height,	// Aspect Ratio
				0.1f,							// zNear plane
				1.0f							// zFar plane
			);

			glm::mat4 viewMatrix = glm::lookAt(
				m_CameraPosition.GetGLM(),				// Position of the Camera
				m_CameraPosition.GetGLM() + m_CameraDirection.GetGLM(),			// Target view point
				glm::vec3(0, 1, 0)				// Up direction
			);


			if (!m_FreeMotionMouse) {
				cursorPositionOnScreenSpace.x = width / 2;
				cursorPositionOnScreenSpace.y = height / 2;
			}


			// Calculate our position in world space
			glm::vec3 pointInWorldSpace = glm::unProject(
				cursorPositionOnScreenSpace, 
				viewMatrix, 
				projectionMatrix, 
				viewport
			);


			// Using the point in World space and the Camera Position
			// We can calculate a direction to use for a Ray

			// This debug info should tell us our ray is facing the wrong way.
			//CreateBall(m_CameraPosition, .2f);
			//CreateBall(pointInWorldSpace, .1f);


			// This should be the fix:
			// Make pointInWorldSpace a direction instead
			glm::vec3 direction = pointInWorldSpace - m_CameraPosition.GetGLM();

			

			Ray ray(m_CameraPosition, direction);


			PhysicsObject* hitObject;

			//printf("CameraPosition: %.2f, %.2f, %.2f\nDirection: %.2f, %.2f, %.2f\n",
			//	m_CameraPosition.x, m_CameraPosition.y, m_CameraPosition.z,
			//	m_CameraDirection.x, m_CameraDirection.y, m_CameraDirection.z
			//);



			if (FirstObject && m_PhysicsSystem.RayCastFirstFound(ray, &hitObject)) {
				hitObject->ApplyForce(Vector3(0.0f, 2000.0f, 0.0f));
			}

			if (ClosestObject && m_PhysicsSystem.RayCastClosest(ray, &hitObject)) {
				hitObject->ApplyForce(Vector3(0.0f, 2000.0f, 0.0f));
			}

			// MASK EXAMPLE
			//unsigned char flags = 0;
			//if (ClosestObject)
			//	flags |= 1 << 6;
			//else if (FirstObject)
			//	flags |= 1 << 3;
			//if (m_PhysicsSystem.RayCastClosest(ray, &hitObject, flags)) {
			//	hitObject->ApplyForce(Vector3(0.0f, 2000.0f, 0.0f));
			//}


			//std::vector<PhysicsObject*> hitList = m_PhysicsSystem.RayCastAll(ray);
			//for (int i = 0; i < hitList.size(); i++) {
			//	hitList[i]->ApplyForce(Vector3(0.0f, 2000.0f, 0.0f));
			//}


			//Vector3 debugPoint = m_CameraPosition + cursorPositionOnScreenSpace;
			//CreateBall(debugPoint, .01f);
			//printf("\n");
			//printf("Debug: (%.2f, %.2f, %.2f)\n", debugPoint.x, debugPoint.y, debugPoint.z);
			//printf("MousePosition: (%d, %d)\n", m_CurrMouseX, m_CurrMouseY);
			//printf("viewport: %d %d %d %d\n", 0, 0, width, height);
			//printf("Point: (%.2f, %.2f, %.2f)\n", cursorPositionOnScreenSpace.x, cursorPositionOnScreenSpace.y, cursorPositionOnScreenSpace.z);
		}
	}
	else {
		isClicked = false;
	}

	//if (GDP_IsKeyHeldDown('a')) {
	//	m_BigShipGamObject->Scale = glm::vec3(0.0f);
	//}
	//else if (GDP_IsKeyHeldDown('s')) {
	//	m_BigShipGamObject->Scale = glm::vec3(1.0f) * SHIP_SCALE;
	//}

	//if (GDP_IsKeyPressed('1')) {
	//	m_BigShipGamObject->Enabled = !m_BigShipGamObject->Enabled;
	//}


	//if (GDP_IsKeyHeldDown('4')) {
	//	g_Ball->gameObject->Enabled = false;
	//}
	//if (GDP_IsKeyHeldDown('5')) {
	//	g_Ball->gameObject->Enabled = true;
	//}

	//if (GDP_IsKeyPressed('2')) {
	//	(*g_PartialMeshObjectsCursor).second->Enabled = false;
	//	g_PartialMeshObjectsCursor++;
	//	if (g_PartialMeshObjectsCursor == g_PartialMeshObjects.end()) {
	//		g_PartialMeshObjectsCursor = g_PartialMeshObjects.begin();
	//	}
	//	(*g_PartialMeshObjectsCursor).second->Enabled = true;
	//}

	//// Typically moved to a UserInput Section
	//if (g_Ball)
	//{
	//	if (GDP_IsKeyHeldDown('a'))
	//		g_Ball->gameObject->Position += glm::vec3(25.0f, 0.0f, 0.0f) * (float)dt;
	//	if (GDP_IsKeyHeldDown('d'))
	//		g_Ball->gameObject->Position += glm::vec3(-25.0f, 0.0f, 0.0f) * (float)dt;
	//	if (GDP_IsKeyHeldDown('w'))
	//		g_Ball->gameObject->Position += glm::vec3(0.0f, 0.0f, 25.0f) * (float)dt;
	//	if (GDP_IsKeyHeldDown('s'))
	//		g_Ball->gameObject->Position += glm::vec3(0.0f, 0.0f, -25.0f) * (float)dt;
	//	if (GDP_IsKeyHeldDown('e'))
	//		g_Ball->gameObject->Position += glm::vec3(0.0f, 25.0f, 0.0f) * (float)dt;
	//	if (GDP_IsKeyHeldDown('q'))
	//		g_Ball->gameObject->Position += glm::vec3(0.0f, -25.0f, 0.0f) * (float)dt;

	//	for (auto meshObjectIt = g_PartialMeshObjects.begin();
	//		meshObjectIt != g_PartialMeshObjects.end();
	//		meshObjectIt++)
	//	{
	//		meshObjectIt->second->Enabled = false;
	//	}

	//	int hashValue = CalculateHashValue(g_Ball->gameObject->Position);
	//	printf("%d\n", hashValue);


	//	// THIS will insert a pair if it does not exist
	//	// Which is what we do not want.
	//	// g_PartialMeshObjects[hashValue]->Enabled = true;

	//	auto resultIt = g_PartialMeshObjects.find(hashValue);
	//	if (resultIt != g_PartialMeshObjects.end())
	//	{
	//		if (resultIt->second != nullptr)
	//			resultIt->second->Enabled = true;
	//	}
	//}


	//// Update the Visual object from the Physics object
	//if (m_ControlledBall.physicsObject != nullptr)
	//{
	//	Vector3 p = m_ControlledBall.physicsObject->GetPosition();
	//	m_ControlledBall.gameObject->Position = glm::vec3(p.x, p.y, p.z);
	//}

	//for (int i = 0; i < m_Balls.size(); i++) {
	//	Vector3 p = m_Balls[i].physicsObject->GetPosition();
	//	m_Balls[i].gameObject->Position = glm::vec3(p.x, p.y, p.z);
	//}

	for (int i = 0; i < m_Balls.size(); i++) {
		Vector3 p = m_Balls[i].physicsObject->GetPosition();
		m_Balls[i].gameObject->Position = glm::vec3(p.x, p.y, p.z);
	}

}

void SimulationView::PhysicsUpdate(double dt)
{
	// System/Engine update step
	m_PhysicsSystem.UpdateStep(dt);

}

void SimulationView::Render() {
	m_PhysicsDebugRenderer->Render();
}

//void SimulationView::AddGameDataToMap(GameObjectData& data) {
//}
//
//GameObject* SimulationView::CreateObjectByType(const std::string& type){
//	return nullptr;
//}