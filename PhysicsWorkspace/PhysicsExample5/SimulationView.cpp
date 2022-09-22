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
	GameObject* ball = GDP_CreateGameObject();
	ball->Renderer.ShaderId = 1;
	ball->Renderer.MaterialId = sphereMaterialId;
	ball->Renderer.MeshId = sphereModelId;
	ball->Scale = glm::vec3(1, 1, 1);
	ball->Position = glm::vec3(0, 2, 0);

}

void SimulationView::Destroy(){

}

void SimulationView::Update(){

}

//void SimulationView::AddGameDataToMap(GameObjectData& data) {
//}
//
//GameObject* SimulationView::CreateObjectByType(const std::string& type){
//	return nullptr;
//}