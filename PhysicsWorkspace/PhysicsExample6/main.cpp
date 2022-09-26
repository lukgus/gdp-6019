#include <gdp/Engine.h>
#include "SimulationView.h"

#include "Time.h"

using namespace gdp;
SimulationView g_View;

const char* WINDOW_TITLE = "PhysicsExample6";
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

	//if (g_CurrentTime >= g_LastCallOnUpdate + FRAME_RATE) {
	WaitToUpdate--;
	if (WaitToUpdate <= 0)
	{
		WaitToUpdate = 10;
		double elapsedUpdateTime = g_CurrentTime - g_LastCallOnUpdate;
		printf("Updating at %2.3f with %2.3f elapsed\n", g_CurrentTime, elapsedUpdateTime);
		g_LastCallOnUpdate = g_CurrentTime;

		g_View.Update(elapsedUpdateTime);
	}
	else {
		printf(".");
	}
}

int main(int argc, char** argv) {

	GDP_Initialize();
	GDP_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
	GDP_UpdateCallback(&Update);

	Time::Update();
	g_View.Initialize();
	Time::Update();
	GDP_Run();

	g_View.Destroy();
	GDP_Destroy();

	return SUCCESS;
}
