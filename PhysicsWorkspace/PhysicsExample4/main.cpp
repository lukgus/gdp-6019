#include "ParticleSystem.h"
#include <random>
#include <ctime>

void ParticleSystemExample() {
	ParticleSystem particleSystem;
	particleSystem.GenerateParticles(100000);

	Vector3 up(0.0f, 1.0f, 0.0f);

	for (int i = 0; i < 10; i++) {
		particleSystem.CreateParticle(up);
	}

	for (int i = 0; i < 10; i++) {
		particleSystem.Integrate(0.1f);
		particleSystem.PrintParticleInfo();
	}
}

struct Vec {
	Vec() {
		printf("Vec();\n");
	}
	~Vec() {
		printf("~Vec();\n");
	}
	Vec(const Vec& other) {
		printf("Vec(const Vec& other);\n");
	}
	Vec operator=(const Vec& other) {
		printf("Vec operator=(const Vec& other);\n");
	}
};

void VectorExample() {
	std::vector<Vec> m_VecPointers;
	m_VecPointers.resize(4);

	for (int i = 0; i < 8; i++) {
		printf("\n---------\n");
		m_VecPointers.push_back(Vec());
	}
}

int main(int argc, char** argv) {
	// https://en.cppreference.com/w/cpp/numeric/random/srand
	// https://en.cppreference.com/w/cpp/chrono/c/time
	srand(time(0));

	ParticleSystemExample();

	return 0;
}