#include <gdp/Engine.h>
#include "SimulationView.h"
using namespace gdp;
SimulationView g_View;

const char* WINDOW_TITLE = "PhysicsExample5";
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

#define SUCCESS 0

void Update() {
	g_View.Update();
}

int main(int argc, char** argv) {

	GDP_Initialize();
	GDP_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
	GDP_UpdateCallback(&Update);

	g_View.Initialize();
	GDP_Run();

	g_View.Destroy();
	GDP_Destroy();

	return SUCCESS;
}
