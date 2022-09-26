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

	void Initialize(int DemoId);
	void Destroy();

	void Update(double dt);
private:
	void Demo1();
	void Demo2();
	void Demo3();

	//void AddGameDataToMap(GameObjectData& data);
	//GameObject* CreateObjectByType(const std::string& type);

	//std::map<std::string, GameObjectData> m_GameObjectDataMap;

	PhysicsSystem m_PhysicsSystem;
	Ball m_ControlledBall;
	Ball m_OtherBall;

	std::vector<Ball> m_Balls;
};
