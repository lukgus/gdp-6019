#include "SimulationView.h"

#include <limits>
#include <math.h>
#include <map>
#include <vector>
unsigned int g_SphereModelId;
unsigned int g_SphereMaterialId;
unsigned int g_TreeMaterialId;
unsigned int g_FirTreeModelId;
unsigned int g_SphereTextureId;

const float SHIP_SCALE = 0.5f;


SimulationView::SimulationView(){

}

SimulationView::~SimulationView(){
	delete m_PhysicsDebugRenderer;
}

void SimulationView::Initialize(int DemoId){
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

	//float min[3] = { -20.f, -1.f, -20.f };
	//float max[3] = { 20.f, 1.f, 20.f };
	//AABB* groundAABB = new AABB(min, max);

	//Triangle* groundTriangle = new Triangle(Point(-20, 0, 20), Point(-20, -10, -20), Point(20, 0, -20));

	//BoundingBox* groundBoundingBox = new BoundingBox();
	//groundBoundingBox->centerPoint.Set(0.0f, 0.0f, 0.0f);
	//groundBoundingBox->halfExtents.Set(20.0f, 1.0f, 20.0f);
	//groundBoundingBox->minPoints.Set(min[0], min[1], min[2]);
	//groundBoundingBox->maxPoints.Set(max[0], max[1], max[2]);

	//PhysicsObject* physicsGround = m_PhysicsSystem.CreatePhysicsObject(Vector3(0, 0, 0), groundAABB);
	//physicsGround->pShape = groundAABB;
	//physicsGround->SetMass(-1.f);
	//physicsGround->pBoundingBox = groundBoundingBox;

	//// Create a ground plane
	//GameObject* ground = GDP_CreateGameObject();
	//ground->Renderer.ShaderId = 1;
	//ground->Renderer.MaterialId = groundMaterialId;
	//ground->Renderer.MeshId = planeModelId;
	//ground->Scale = glm::vec3(20, 1, 20);

	//m_PhysicsDebugRenderer->AddPhysicsObject(physicsGround);
	//PrepareDemo();

	//LoadOurShip("assets/models/BigShip.obj");

	CreateBall(Vector3(0.0f, 50.0f, 0.0f), 2.0f);

	int breakhere = 0;
}

void SimulationView::Destroy() {

}



int CalculateHashValue(float x, float y, float z)
{
	int hashValue = 0;

	hashValue += floor(x * SHIP_SCALE + 30) / 10 * 10000;
	hashValue += floor(y * SHIP_SCALE + 10) / 10 * 100;
	hashValue += floor(z * SHIP_SCALE + 60) / 10;
	return hashValue;
}

int CalculateHashValue(const Vector3& v)
{
	return CalculateHashValue(v.x, v.y, v.z);
}

void SimulationView::LoadOurShip(const std::string& filepath)
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
	for (int i = 0; i < vertices.size(); i++) {
		glm::vec3& vertex = vertices[i];

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

	m_BigShipGamObject = GDP_CreateGameObject();
	m_BigShipGamObject->Position = glm::vec3(0, 0, 0);
	m_BigShipGamObject->Renderer.ShaderId = 1;
	m_BigShipGamObject->Renderer.MaterialId = g_SphereMaterialId;
	m_BigShipGamObject->Renderer.MeshId = m_ShipModelId;
	m_BigShipGamObject->Scale = glm::vec3(1.0f) * SHIP_SCALE;// *scale;


	for (int i = 0; i < triangles.size(); i+= 3)
	{
		Point a = Point(vertices[i]) * SHIP_SCALE;
		Point b = Point(vertices[i]) * SHIP_SCALE;
		Point c = Point(vertices[i]) * SHIP_SCALE;

		int hashA = CalculateHashValue(a);
		int hashB = CalculateHashValue(b);
		int hashC = CalculateHashValue(c);

		//printf("(%.2f, %.2f, %.2f) -> %d\n", a.x, a.y, a.z, hashA);
		//printf("(%.2f, %.2f, %.2f) -> %d\n", b.x, b.y, b.z, hashB);
		//printf("(%.2f, %.2f, %.2f) -> %d\n", c.x, c.y, c.z, hashC);

		Triangle* newTriangle = new Triangle(a, b, c);

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

void SimulationView::CreateBall(const Vector3& position, float scale) {
	Sphere* otherSphere = new Sphere(Point(0.0f, 0.0f, 0.0f), scale);

	Ball newBall;
	newBall.physicsObject = m_PhysicsSystem.CreatePhysicsObject(position, otherSphere);
	newBall.gameObject = GDP_CreateGameObject();
	newBall.gameObject->Renderer.ShaderId = 1;
	newBall.gameObject->Renderer.MaterialId = g_SphereMaterialId;
	newBall.gameObject->Renderer.MeshId = g_SphereModelId;
	newBall.gameObject->Scale = glm::vec3(1, 1, 1) * scale;

	// Create a bounding box around our ball.
	//Vector3 halfExtents = m_BallBoundingBox.halfExtents;
	//newBall.physicsObject->pBoundingBox = &m_BallBoundingBox;
	//newBall.physicsObject->pBoundingBox->halfExtents = halfExtents * scale;

	//m_PhysicsDebugRenderer->AddPhysicsObject(newBall.physicsObject);

	m_Balls.push_back(newBall);
}

void SimulationView::PrepareDemo() {

	// Create a sphere
	GDP_LoadModel(g_SphereModelId, "assets/models/sphere.obj");
	GDP_LoadModel(g_FirTreeModelId, "assets/models/Fir_Tree.fbx");

	// Load Textures
	GDP_LoadTexture(g_SphereTextureId, "assets/textures/white.png");

	// Create Material
	GDP_CreateMaterial(g_SphereMaterialId, g_SphereTextureId, color(1, 0, 0));
	GDP_CreateMaterial(g_TreeMaterialId, g_SphereTextureId, color(0, 1, 0));

	std::vector<glm::vec3> vertices;
	std::vector<int> triangles;

	unsigned int unused1, unused2;

	GDP_GetModelData(g_SphereModelId, vertices, triangles, unused1, unused2);
	Vector3 minPoints = Vector3(FLT_MAX, FLT_MAX, FLT_MAX);
	Vector3 maxPoints = Vector3(FLT_MIN, FLT_MIN, FLT_MIN);
	for (int i = 0; i < vertices.size(); i++) {
		glm::vec3& vertex = vertices[i];

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

	// Calculate the point halfway between the minPoints, and maxPoints
	Vector3 halfExtents = (maxPoints - minPoints) / 2.f;
	Vector3 centerPoint = minPoints + halfExtents;

	printf("Minimum Points: (%.2f, %.2f, %.2f)\n",
		minPoints.x,
		minPoints.y,
		minPoints.z);
	printf("Maximum Points: (%.2f, %.2f, %.2f)\n",
		maxPoints.x,
		maxPoints.y,
		maxPoints.z);
	printf("Half Extents: (%.2f, %.2f, %.2f)\n",
		halfExtents.x,
		halfExtents.y,
		halfExtents.z);
	printf("Center Point: (%.2f, %.2f, %.2f)\n",
		centerPoint.x,
		centerPoint.y,
		centerPoint.z);

	m_BallBoundingBox.centerPoint = centerPoint;
	m_BallBoundingBox.halfExtents = halfExtents;
	m_BallBoundingBox.maxPoints = maxPoints;
	m_BallBoundingBox.minPoints = minPoints;

	// ShaderProgram = 1
	// VertexShader = 2
	// FragShader = 3

	// ShaderProgram 4
	// VertexShader 5
	// FragShader 6
	
	// Create our ground

	//Sphere* controlledSphere = new Sphere(Point(0.0f, 0.0f, 0.0f), 1.0f);

	//// Create our controlled ball
	//m_ControlledBall.physicsObject = m_PhysicsSystem.CreatePhysicsObject(Vector3(1, 25, 0), controlledSphere);
	//m_ControlledBall.gameObject = GDP_CreateGameObject();
	//m_ControlledBall.gameObject->Renderer.ShaderId = 1;
	//m_ControlledBall.gameObject->Renderer.MaterialId = g_SphereMaterialId;
	//m_ControlledBall.gameObject->Renderer.MeshId = g_SphereModelId;
	//m_ControlledBall.gameObject->Scale = glm::vec3(1, 1, 1);

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

void SimulationView::Update(double dt) {
	if (GDP_IsKeyHeldDown('a')) {
		m_BigShipGamObject->Scale = glm::vec3(0.0f);
	}
	else if (GDP_IsKeyHeldDown('s')) {
		m_BigShipGamObject->Scale = glm::vec3(1.0f) * SHIP_SCALE;
	}

	return;


	// Typically moved to a UserInput Section
	if (m_ControlledBall.physicsObject != nullptr)
	{
		if (GDP_IsKeyHeldDown('a'))
			m_ControlledBall.physicsObject->ApplyForce(Vector3(1, 0, 0) * 15.0f);
		if (GDP_IsKeyHeldDown('d'))
			m_ControlledBall.physicsObject->ApplyForce(Vector3(-1, 0, 0) * 15.0f);
		if (GDP_IsKeyHeldDown('w'))
			m_ControlledBall.physicsObject->ApplyForce(Vector3(0, 0, 1) * 15.0f);
		if (GDP_IsKeyHeldDown('s'))
			m_ControlledBall.physicsObject->ApplyForce(Vector3(0, 0, -1) * 15.0f);
	}


	// Update the Visual object from the Physics object
	if (m_ControlledBall.physicsObject != nullptr)
	{
		Vector3 p = m_ControlledBall.physicsObject->GetPosition();
		m_ControlledBall.gameObject->Position = glm::vec3(p.x, p.y, p.z);
	}

	for (int i = 0; i < m_Balls.size(); i++) {
		Vector3 p = m_Balls[i].physicsObject->GetPosition();
		m_Balls[i].gameObject->Position = glm::vec3(p.x, p.y, p.z);
	}

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