#include "SimulationView.h"

SimulationView::SimulationView(){

}

SimulationView::~SimulationView(){

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

	// Create a ground plane
	GameObject* ground = GDP_CreateGameObject();
	ground->Renderer.ShaderId = 1;
	ground->Renderer.MaterialId = groundMaterialId;
	ground->Renderer.MeshId = planeModelId;
	ground->Scale = glm::vec3(20, 1, 20);

	if (DemoId == 1)
		Demo1();
	else if (DemoId == 2)
		Demo2();
	else if (DemoId == 3)
		Demo3();
}

void SimulationView::Destroy(){

}

void SimulationView::Demo1() {

	// Create a sphere
	unsigned int sphereModelId = -1;
	GDP_LoadModel(sphereModelId, "assets/models/sphere.obj");

	// Load Textures
	unsigned int sphereTextureId = -1;
	GDP_LoadTexture(sphereTextureId, "assets/textures/white.png");

	// Create Material
	unsigned int sphereMaterialId = -1;
	GDP_CreateMaterial(sphereMaterialId, sphereTextureId, color(1, 0, 0));

	// Create our controlled ball
	m_ControlledBall.particle = m_PhysicsSystem.CreateParticle(Vector3(-3, 1, 0));
	m_ControlledBall.gameObject = GDP_CreateGameObject();
	m_ControlledBall.gameObject->Renderer.ShaderId = 1;
	m_ControlledBall.gameObject->Renderer.MaterialId = sphereMaterialId;
	m_ControlledBall.gameObject->Renderer.MeshId = sphereModelId;
	m_ControlledBall.gameObject->Scale = glm::vec3(1, 1, 1);

	// Create our other ball
	m_OtherBall.particle = m_PhysicsSystem.CreateParticle(Vector3(3, 1, 0));
	m_OtherBall.gameObject = GDP_CreateGameObject();
	m_OtherBall.gameObject->Renderer.ShaderId = 1;
	m_OtherBall.gameObject->Renderer.MaterialId = sphereMaterialId;
	m_OtherBall.gameObject->Renderer.MeshId = sphereModelId;
	m_OtherBall.gameObject->Scale = glm::vec3(1, 1, 1);

	// Create a spring
	Spring* mySpring = new Spring(m_ControlledBall.particle, m_OtherBall.particle, 1, 6);
	m_PhysicsSystem.AddSpring(mySpring);
}

void SimulationView::Demo2() {
	// Create a sphere
	unsigned int sphereModelId = -1;
	GDP_LoadModel(sphereModelId, "assets/models/sphere.obj");

	// Create a block
	unsigned int blockModelId = -1;
	GDP_LoadModel(blockModelId, "assets/models/block.obj");

	// Load Textures
	unsigned int sphereTextureId = -1;
	GDP_LoadTexture(sphereTextureId, "assets/textures/white.png");

	// Create Material
	unsigned int sphereMaterialId = -1;
	GDP_CreateMaterial(sphereMaterialId, sphereTextureId, color(1, 0, 0));
	unsigned int blockMaterialId = -1;
	GDP_CreateMaterial(blockMaterialId, sphereTextureId, color(0, 0, 0));

	// Create a block
	Particle* blockParticle = m_PhysicsSystem.CreateParticle(Vector3(0, 10, 0));
	blockParticle->SetMass(-1.f);
	GameObject* go = GDP_CreateGameObject();
	go->Renderer.ShaderId = 1;
	go->Renderer.MaterialId = blockMaterialId;
	go->Renderer.MeshId = blockModelId;
	go->Scale = glm::vec3(1, 1, 1);
	Vector3 p = blockParticle->GetPosition();
	go->Position = glm::vec3(p.x, p.y, p.z);

	// Create our controlled ball
	m_ControlledBall.particle = m_PhysicsSystem.CreateParticle(Vector3(0, 8, 0));
	m_ControlledBall.gameObject = GDP_CreateGameObject();
	m_ControlledBall.gameObject->Renderer.ShaderId = 1;
	m_ControlledBall.gameObject->Renderer.MaterialId = sphereMaterialId;
	m_ControlledBall.gameObject->Renderer.MeshId = sphereModelId;
	m_ControlledBall.gameObject->Scale = glm::vec3(1, 1, 1);

	// Create a spring
	Spring* mySpring = new Spring(m_ControlledBall.particle, blockParticle, 30, 5);
	m_PhysicsSystem.AddSpring(mySpring);
}
void SimulationView::Demo3() {
	// Create a sphere
	unsigned int sphereModelId = -1;
	GDP_LoadModel(sphereModelId, "assets/models/sphere.obj");

	// Create a block
	unsigned int blockModelId = -1;
	GDP_LoadModel(blockModelId, "assets/models/block.obj");

	// Load Textures
	unsigned int sphereTextureId = -1;
	GDP_LoadTexture(sphereTextureId, "assets/textures/white.png");

	// Create Material
	unsigned int sphereMaterialId = -1;
	GDP_CreateMaterial(sphereMaterialId, sphereTextureId, color(1, 0, 0));
	unsigned int blockMaterialId = -1;
	GDP_CreateMaterial(blockMaterialId, sphereTextureId, color(0, 0, 0));

	// Create our 2 blocks
	Particle* blockParticle1 = m_PhysicsSystem.CreateParticle(Vector3(-5, 10, 0));
	blockParticle1->SetMass(-1.f);
	GameObject* go1 = GDP_CreateGameObject();
	go1->Renderer.ShaderId = 1;
	go1->Renderer.MaterialId = blockMaterialId;
	go1->Renderer.MeshId = blockModelId;
	go1->Scale = glm::vec3(1, 1, 1);
	Vector3 p1 = blockParticle1->GetPosition();
	go1->Position = glm::vec3(p1.x, p1.y, p1.z);

	Particle* blockParticle2 = m_PhysicsSystem.CreateParticle(Vector3(5, 10, 0));
	blockParticle2->SetMass(-1.f);
	GameObject* go2 = GDP_CreateGameObject();
	go2->Renderer.ShaderId = 1;
	go2->Renderer.MaterialId = blockMaterialId;
	go2->Renderer.MeshId = blockModelId;
	go2->Scale = glm::vec3(1, 1, 1);
	Vector3 p2 = blockParticle2->GetPosition();
	go2->Position = glm::vec3(p2.x, p2.y, p2.z);

	// Create our controlled ball
	Ball a, b, c, d;
	a.particle = m_PhysicsSystem.CreateParticle(Vector3(-3, 5, 0));
	a.gameObject = GDP_CreateGameObject();
	a.gameObject->Renderer.ShaderId = 1;
	a.gameObject->Renderer.MaterialId = sphereMaterialId;
	a.gameObject->Renderer.MeshId = sphereModelId;
	a.gameObject->Scale = glm::vec3(1, 1, 1);

	b.particle = m_PhysicsSystem.CreateParticle(Vector3(-1, 4, 0));
	b.gameObject = GDP_CreateGameObject();
	b.gameObject->Renderer.ShaderId = 1;
	b.gameObject->Renderer.MaterialId = sphereMaterialId;
	b.gameObject->Renderer.MeshId = sphereModelId;
	b.gameObject->Scale = glm::vec3(1, 1, 1);

	c.particle = m_PhysicsSystem.CreateParticle(Vector3(1, 4, 0));
	c.gameObject = GDP_CreateGameObject();
	c.gameObject->Renderer.ShaderId = 1;
	c.gameObject->Renderer.MaterialId = sphereMaterialId;
	c.gameObject->Renderer.MeshId = sphereModelId;
	c.gameObject->Scale = glm::vec3(1, 1, 1);

	d.particle = m_PhysicsSystem.CreateParticle(Vector3(3, 5, 0));
	d.gameObject = GDP_CreateGameObject();
	d.gameObject->Renderer.ShaderId = 1;
	d.gameObject->Renderer.MaterialId = sphereMaterialId;
	d.gameObject->Renderer.MeshId = sphereModelId;
	d.gameObject->Scale = glm::vec3(1, 1, 1);

	m_Balls.push_back(a);
	m_Balls.push_back(b);
	m_Balls.push_back(c);
	m_Balls.push_back(d);

	// Create our spring
	Spring* a1 = new Spring(blockParticle1, a.particle,		50.f, 2.15f);
	Spring* ab = new Spring(a.particle,		b.particle,		50.f, 2.15f);
	Spring* bc = new Spring(b.particle,		c.particle,		50.f, 2.15f);
	Spring* cd = new Spring(c.particle,		d.particle,		50.f, 2.15f);
	Spring* d2 = new Spring(d.particle,		blockParticle2, 50.f, 2.15f);

	m_PhysicsSystem.AddSpring(a1);
	m_PhysicsSystem.AddSpring(ab);
	m_PhysicsSystem.AddSpring(bc);
	m_PhysicsSystem.AddSpring(cd);
	m_PhysicsSystem.AddSpring(d2);

	m_ControlledBall = a;
}


void SimulationView::Update(double dt) {
	// Typically moved to a UserInput Section
	if (m_ControlledBall.particle != nullptr)
	{
		if (GDP_IsKeyHeldDown('a'))
			m_ControlledBall.particle->ApplyForce(Vector3(1, 0, 0) * 5.0f);
		if (GDP_IsKeyHeldDown('d'))
			m_ControlledBall.particle->ApplyForce(Vector3(-1, 0, 0) * 5.0f);
		if (GDP_IsKeyHeldDown('w'))
			m_ControlledBall.particle->ApplyForce(Vector3(0, 0, 1) * 5.0f);
		if (GDP_IsKeyHeldDown('s'))
			m_ControlledBall.particle->ApplyForce(Vector3(0, 0, -1) * 5.0f);
	}

	// Typically in a World Update Step

	// System/Engine update step
	m_PhysicsSystem.UpdateStep(dt);

	// Update the Visual object from the Physics object
	if (m_ControlledBall.particle != nullptr)
	{
		Vector3 p = m_ControlledBall.particle->GetPosition();
		m_ControlledBall.gameObject->Position = glm::vec3(p.x, p.y, p.z);
	}

	if (m_OtherBall.particle != nullptr)
	{
		Vector3 p = m_OtherBall.particle->GetPosition();
		m_OtherBall.gameObject->Position = glm::vec3(p.x, p.y, p.z);
	}

	for (int i = 0; i < m_Balls.size(); i++) {
		Vector3 p = m_Balls[i].particle->GetPosition();
		m_Balls[i].gameObject->Position = glm::vec3(p.x, p.y, p.z);
	}
}

//void SimulationView::AddGameDataToMap(GameObjectData& data) {
//}
//
//GameObject* SimulationView::CreateObjectByType(const std::string& type){
//	return nullptr;
//}