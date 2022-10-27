#include "gdp/Engine.h"
#include "SimulationView.h"

#include "Time.h"



// Will look at documentation in a minute.
#include <map>
#include <vector>

int CalculateHash(const Vector3& p)
{
	// xxxyyyzzz
	return ((int)p.x / 10) * 1000000
		+ ((int)p.y / 10) * 1000
		+ ((int)p.z / 10);
}

std::map<int, std::vector<Triangle*>> g_AABB_Map;
void CreateAABBStructure(const Vector3& position, float scale) {

	unsigned int modelId;
	unsigned int unused1, unused2;
	std::vector<glm::vec3> vertices;
	std::vector<int> triangles;
	GDP_GetModelData(modelId, vertices, triangles, unused1, unused2);
	for (int i = 0; i < triangles.size(); i += 3) {
		int indexA = i;
		int indexB = i + 1;
		int indexC = i + 2;

		Vector3 vertexA = Vector3(vertices[indexA]) * scale + position;
		Vector3 vertexB = Vector3(vertices[indexB]) * scale + position;
		Vector3 vertexC = Vector3(vertices[indexC]) * scale + position;
		Triangle* triangle = new Triangle(vertexA, vertexB, vertexC);

		int aabbA = CalculateHash(vertexA);
		int aabbB = CalculateHash(vertexB);
		int aabbC = CalculateHash(vertexC);

		g_AABB_Map[aabbA].push_back(triangle);

		if (aabbB != aabbA)
			g_AABB_Map[aabbB].push_back(triangle);

		if (aabbC != aabbA && aabbC != aabbB)
			g_AABB_Map[aabbC].push_back(triangle);

	}
}

void Update()
{
	// Check each sphere on  your object
	//Foreach collider
	Sphere* a = new Sphere(Point(0), 1.0f);

	Vector3 position = (10, 5, 8);

	int position_hash = CalculateHash(position);
	std::vector<Triangle*> aabb_triangles = g_AABB_Map[position_hash];

}

using namespace gdp;
SimulationView g_View;

const char* WINDOW_TITLE = "PhysicsExample9";
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

#define SUCCESS 0

double g_LastCallOnUpdate;
double g_CurrentTime;

const int MILLISECONDS_IN_A_SECOND = 1000;
const int FRAMES_PER_SECOND = 60;
const double FRAME_RATE = (double)1 / FRAMES_PER_SECOND;

int WaitToUpdate = 0;

void Update() {
	Time::Update();
	double deltaTimeInSeconds = Time::GetUnscaledDeltaTimeSeconds();
	g_CurrentTime += deltaTimeInSeconds;

	// Cap it at 60 FPS
	// Example:
	// 103
	// 107
	// 109
	// 111
	// 112
	// 114
	// 117 >= 116.6666
	// g_LastCallOnUpdate = 117
	// 120
	// 123
	// 127
	// 130
	// 132
	// 135 133.66666
	// g_LastCallOnUpdate = 135
	// g_CurrentTime >= 100 + 16.66666
	// OR Update every 10 update calls
	// OR Update # objects / 10 to update all within 10 update calls.

	if (g_CurrentTime >= g_LastCallOnUpdate + FRAME_RATE) {
	//WaitToUpdate--;
	//if (WaitToUpdate <= 0)
	//{
	//	WaitToUpdate = 10;
		double elapsedUpdateTime = g_CurrentTime - g_LastCallOnUpdate;
		//printf("Updating at %2.3f with %2.3f elapsed\n", g_CurrentTime, elapsedUpdateTime);
		g_LastCallOnUpdate = g_CurrentTime;

		while (elapsedUpdateTime > 0.1) {
			printf("ElapsedUpdateTimeIsTooBig!!!\n");
			g_View.Update(elapsedUpdateTime);
			elapsedUpdateTime -= 0.1;
		}
		g_View.Update(elapsedUpdateTime);
	}
	else {
		//printf(".");
	}
}

void Render() {
	g_View.Render();
}

int main(int argc, char** argv) {

	GDP_Initialize();
	GDP_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
	GDP_UpdateCallback(&Update);
	GDP_RenderCallback(&Render);

	Time::Update();
	g_View.Initialize(3);
	Time::Update();
	GDP_Run();

	g_View.Destroy();
	GDP_Destroy();

	return SUCCESS;
}
