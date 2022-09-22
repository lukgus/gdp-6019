#include "SimulationView.h"

SimulationView::SimulationView(){

}

SimulationView::~SimulationView(){

}

void SimulationView::Initialize(){
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

	// Create a sphere
	unsigned int sphereModelId = -1;
	GDP_LoadModel(sphereModelId, "assets/models/sphere.obj");

	// Load Textures
	unsigned int sphereTextureId = -1;
	GDP_LoadTexture(sphereTextureId, "assets/textures/white.png");

	// Create Material
	unsigned int sphereMaterialId = -1;
	GDP_CreateMaterial(sphereMaterialId, sphereTextureId, color(1, 0, 0));

	// Create our ball
	m_Ball.particle = m_PhysicsSystem.CreateParticle(Vector3(0, 10, 0));
	m_Ball.gameObject = GDP_CreateGameObject();
	m_Ball.gameObject->Renderer.ShaderId = 1;
	m_Ball.gameObject->Renderer.MaterialId = sphereMaterialId;
	m_Ball.gameObject->Renderer.MeshId = sphereModelId;
	m_Ball.gameObject->Scale = glm::vec3(1, 1, 1);
}

void SimulationView::Destroy(){

}

void SimulationView::Update() {
	// Typically moved to a UserInput Section
	if (GDP_IsKeyHeldDown('a'))
		m_Ball.particle->ApplyForce(Vector3(1, 0, 0));
	if (GDP_IsKeyHeldDown('d'))
		m_Ball.particle->ApplyForce(Vector3(-1, 0, 0));
	if (GDP_IsKeyHeldDown('w'))
		m_Ball.particle->ApplyForce(Vector3(0, 0, 1));
	if (GDP_IsKeyHeldDown('s'))
		m_Ball.particle->ApplyForce(Vector3(0, 0, -1));

	// Typically in a World Update Step


	// System/Engine update step
	m_PhysicsSystem.UpdateStep(0.01f);

	// Update the Visual object from the Physics object
	Vector3 p = m_Ball.particle->GetPosition();
	m_Ball.gameObject->Position = glm::vec3(p.x, p.y, p.z);
}

//void SimulationView::AddGameDataToMap(GameObjectData& data) {
//}
//
//GameObject* SimulationView::CreateObjectByType(const std::string& type){
//	return nullptr;
//}