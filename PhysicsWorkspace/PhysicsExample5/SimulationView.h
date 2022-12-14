#pragma once

#include <gdp/Engine.h>
using namespace gdp;

#include <map>
#include <vector>
#include <string>

#include "PhysicsSystem.h"
#include "Ball.h"

typedef glm::vec3 color;

//struct GameObjectData {
//	unsigned int ModelId;
//	unsigned int MaterialId;
//};

class SimulationView {
public:
	SimulationView();
	~SimulationView();

	void Initialize();
	void Destroy();

	void Update();

private:
	//void AddGameDataToMap(GameObjectData& data);
	//GameObject* CreateObjectByType(const std::string& type);

	//std::map<std::string, GameObjectData> m_GameObjectDataMap;

	PhysicsSystem m_PhysicsSystem;
	Ball m_Ball;
};
