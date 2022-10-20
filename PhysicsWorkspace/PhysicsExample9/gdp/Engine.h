#pragma once

#ifdef GDP_EXPORTS
#define GDPENGINE_API __declspec(dllexport)
#else
#define GDPENGINE_API __declspec(dllimport)
#endif

#include "GameObject.h"
#include <vector>
#include "Model.h"

namespace gdp
{
    extern "C" {
        // Engine
        GDPENGINE_API void GDP_Initialize();
        GDPENGINE_API void GDP_Destroy();
        GDPENGINE_API void GDP_UpdateCallback(void (*Callback)(void));
        GDPENGINE_API void GDP_RenderCallback(void (*Callback)(void));
        GDPENGINE_API void GDP_Run();
        GDPENGINE_API void GDP_CreateWindow(
            const char* title, const int width, const int height);

        // Assets
        GDPENGINE_API void GDP_LoadTexture(
            unsigned int& id, const char* filepath);
        GDPENGINE_API void GDP_LoadModel(
            unsigned int& id, const char* filepath);
        GDPENGINE_API void GDP_GetModelData(unsigned int id,
            std::vector<glm::vec3>& vertices, std::vector<int>& triangles,
            unsigned int& numTriangles, unsigned int& vbo);
        GDPENGINE_API void GDP_CreateMaterial(
            unsigned int& id, unsigned int textureId, const glm::vec3& color);
        GDPENGINE_API void GDP_CreateShaderProgramFromFiles(
            unsigned int& id, unsigned int& shaderProgramId, 
            const char* vertexShader, const char* fragmentShader);

        // Game World
        GDPENGINE_API GameObject* GDP_CreateGameObject();
        GDPENGINE_API void GDP_SetCameraTarget(GameObject* go);

        // User Input
        GDPENGINE_API bool GDP_IsKeyHeldDown(unsigned char key);
        GDPENGINE_API bool GDP_IsKeyPressed(unsigned char key);
        GDPENGINE_API bool GDP_IsKeyReleased(unsigned char key);
        GDPENGINE_API void GDP_GetMousePosition(int& x, int& y);
        GDPENGINE_API bool GDP_GetMouseButtonState(int button, int& state);
    }
}