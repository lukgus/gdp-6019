#include "SimulationView.h"

#include <limits>

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

	float min[3] = { -20.f, -1.f, -20.f };
	float max[3] = { 20.f, 1.f, 20.f };
	AABB* groundAABB = new AABB(min, max);

	Triangle* groundTriangle = new Triangle(Point(-20, 0, 20), Point(-20, -10, -20), Point(20, 0, -20));

	BoundingBox* groundBoundingBox = new BoundingBox();
	groundBoundingBox->centerPoint.Set(0.0f, 0.0f, 0.0f);
	groundBoundingBox->halfExtents.Set(20.0f, 1.0f, 20.0f);
	groundBoundingBox->minPoints.Set(min[0], min[1], min[2]);
	groundBoundingBox->maxPoints.Set(max[0], max[1], max[2]);

	PhysicsObject* physicsGround = m_PhysicsSystem.CreatePhysicsObject(Vector3(0, 0, 0), groundTriangle);
	physicsGround->pShape = groundTriangle;
	physicsGround->SetMass(-1.f);
	physicsGround->pBoundingBox = groundBoundingBox;

	// Create a ground plane
	GameObject* ground = GDP_CreateGameObject();
	ground->Renderer.ShaderId = 1;
	ground->Renderer.MaterialId = groundMaterialId;
	ground->Renderer.MeshId = planeModelId;
	ground->Scale = glm::vec3(20, 1, 20);




	m_PhysicsDebugRenderer->AddPhysicsObject(physicsGround);
	PrepareDemo();
}

void SimulationView::Destroy() {

}

void SimulationView::PrepareDemo() {

	// Create a sphere
	unsigned int sphereModelId = -1;
	GDP_LoadModel(sphereModelId, "assets/models/sphere.obj");

	// Load Textures
	unsigned int sphereTextureId = -1;
	GDP_LoadTexture(sphereTextureId, "assets/textures/white.png");

	// Create Material
	unsigned int sphereMaterialId = -1;
	GDP_CreateMaterial(sphereMaterialId, sphereTextureId, color(1, 0, 0));


	Vector3 minPoints = Vector3(FLT_MAX, FLT_MAX, FLT_MAX);
	Vector3 maxPoints = Vector3(FLT_MIN, FLT_MIN, FLT_MIN);

	unsigned int unused1, unused2;
	std::vector<glm::vec3> vertices = GDP_GetModelData(sphereModelId, unused1, unused2);
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

	Sphere* controlledSphere = new Sphere(Point(0.0f, 0.0f, 0.0f), 1.0f);
	Sphere* otherSphere = new Sphere(Point(0.0f, 0.0f, 0.0f), 1.0f);

	// Create our controlled ball
	m_ControlledBall.physicsObject = m_PhysicsSystem.CreatePhysicsObject(Vector3(0, 10, 0), controlledSphere);
	m_ControlledBall.gameObject = GDP_CreateGameObject();
	m_ControlledBall.gameObject->Renderer.ShaderId = 1;
	m_ControlledBall.gameObject->Renderer.MaterialId = sphereMaterialId;
	m_ControlledBall.gameObject->Renderer.MeshId = sphereModelId;
	m_ControlledBall.gameObject->Scale = glm::vec3(1, 1, 1);

	// Create our other ball
	m_OtherBall.physicsObject = m_PhysicsSystem.CreatePhysicsObject(Vector3(3, 10, 0), otherSphere);
	m_OtherBall.gameObject = GDP_CreateGameObject();
	m_OtherBall.gameObject->Renderer.ShaderId = 1;
	m_OtherBall.gameObject->Renderer.MaterialId = sphereMaterialId;
	m_OtherBall.gameObject->Renderer.MeshId = sphereModelId;
	m_OtherBall.gameObject->Scale = glm::vec3(1, 1, 1);

	// Create a bounding box around our ball.
	m_ControlledBall.physicsObject->pBoundingBox = &m_BallBoundingBox;
	m_OtherBall.physicsObject->pBoundingBox = &m_BallBoundingBox;

	m_PhysicsDebugRenderer->AddPhysicsObject(m_OtherBall.physicsObject);
	m_PhysicsDebugRenderer->AddPhysicsObject(m_ControlledBall.physicsObject);
}

void SimulationView::Update(double dt) {
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

	// Typically in a World Update Step

	// System/Engine update step
	m_PhysicsSystem.UpdateStep(dt);

	// Update the Visual object from the Physics object
	if (m_ControlledBall.physicsObject != nullptr)
	{
		Vector3 p = m_ControlledBall.physicsObject->GetPosition();
		m_ControlledBall.gameObject->Position = glm::vec3(p.x, p.y, p.z);
	}

	if (m_OtherBall.physicsObject != nullptr)
	{
		Vector3 p = m_OtherBall.physicsObject->GetPosition();
		m_OtherBall.gameObject->Position = glm::vec3(p.x, p.y, p.z);
	}

	for (int i = 0; i < m_Balls.size(); i++) {
		Vector3 p = m_Balls[i].physicsObject->GetPosition();
		m_Balls[i].gameObject->Position = glm::vec3(p.x, p.y, p.z);
	}
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