#pragma once

#include "components/simple_scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include <string>
#include <Core/Engine.h>

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };

    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void DrawEnemy(glm::mat3 visMatrix, float deltaTimeSeconds);
        void DrawPlayer(glm::mat3 vismatrix, float deltaTimeSeconds);
        void DrawMap(glm::mat3 visMatrix);
        void Draw_one_enemy(glm::mat3 visMatrix, Enemy& inamicul, float deltatime);
        bool Check_move(float move, bool Xmov, bool Ymov);
        bool Tema1::Corect_interval(float nr, float bot_limit, float top_limit);
        void Tema1::DrawBullet(glm::mat3 visMatrix, float deltaTimeSeconds);
        bool Tema1::Check_bullet_move(float move, bool Xmov, bool Ymove, int j);
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;


        glm::mat3 VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);

        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

    protected:
        glm::mat3 modelMatrix;
        glm::mat3 staticMatrix;
        //unghi pentru rotatie (patrat player)
        float angularStep;
        // timer pentru tragere
        float fire_rate;
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 visMatrix;
        Player player;
        //timpe petru aparitie inamici
        float deltatime1;
        //timer pentru scor
        float score;
        //vector cu inamici
        Enemy inamic1[5];
        //vector cu gloante
        Bullet bullets[10];
        //rezolutia initiala
        float resolutionIx, resolutionIy;
    };
} 
