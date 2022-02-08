#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/camera.h"
#include "lab_m1/Tema2/transform3DD.h"
#include "core/engine.h"
#include "utils/gl_utils.h"
#include <fstream>

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        Tema2();
        ~Tema2();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        
        void Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);

        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        implemented::Cameraa* camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;

        float fov, zNear, zFar;
        float X, Y, Z, angle, endX, endZ;
        float viata, timp;
        int map[10][10], random_nr;
        int camera_type;
        int one_time_var;

    };
}   // namespace m1
