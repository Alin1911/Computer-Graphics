#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transformari.h"
#include "lab_m1/Tema1/obiecte.h"

using namespace std;
using namespace m1;


Tema1::Tema1()
{
    score = 0;
    fire_rate = 0;
    deltatime1 = 0;
    player = Player(100, 0, true);

    //vector cu gloante
    for (size_t i = 0; i < 10; i++)
        bullets[i] = Bullet();

    //creez 5 obiecte Enemy 
    for (int i = 0; i < 5; i++) {
        inamic1[i] = Enemy();
    }
    angularStep = 0;
    player.angle_bullet = 0;
}

Tema1::~Tema1()
{
}

void Tema1::Init() {

    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetPosition(glm::vec3(0, 0, resolution.y / 2));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    logicSpace.x = 0;
    logicSpace.y = 0;
    logicSpace.width = resolution.x;
    logicSpace.height = resolution.y;
    
    resolutionIx = resolution.x;
    resolutionIy = resolution.y;

    player.axeX = resolution.x/2;
    player.axeY = resolution.y/2;

    glm::vec3 corner = glm::vec3(0, 0, 0);

    //dreptunghi exterior/mapa
    Mesh* dreptunghi_exterior = obiecte::CreateRectangle("dreptunghi_exterior", corner, 1280, 720, glm::vec3(0.5, 0.35, 0.05), true);
    AddMeshToList(dreptunghi_exterior);

    //dreptunghi maro/obstacole
    Mesh* rectangle2 = obiecte::CreateRectangle("rectangle", corner, 150, 20, glm::vec3(0.5, 0.35, 0.05), true);
    AddMeshToList(rectangle2);

    corner = glm::vec3(20, 20, 0);

    //dreptunghi interior/mapa
    Mesh* dreptunghi_interior = obiecte::CreateRectangle("dreptunghi_interior", corner, 1240 , 680, glm::vec3(0.5, 0.5, 0.5),true);
    AddMeshToList(dreptunghi_interior);


    corner = glm::vec3(0, 0, 0);
    player.cx = corner.x + 50 / 2;
    player.cy = corner.y + 50 / 2;

    //dreptunghi verde/hp curent
    Mesh* hp1 = obiecte::CreateRectangle("hp1", corner, 100, 10, glm::vec3(0.2 , 1 , 0), true);
    AddMeshToList(hp1);

    //dreptunghi rosu/hp pierdut
    Mesh* hp2 = obiecte::CreateRectangle("hp2", corner, 100, 10, glm::vec3(1, 0, 0), true);
    AddMeshToList(hp2);

    //patrat albastru/jucator
    Mesh* square3 = obiecte::CreateSquare("square3", corner, 50, glm::vec3(0, 0, 1),true);
    AddMeshToList(square3);

    //dreptunghi negru/glont
    Mesh* bullet_t = obiecte::CreateRectangle("bullet_t", corner, 10, 10, glm::vec3(0, 0, 0), true);
    AddMeshToList(bullet_t);

    //patrat rosu/inamic
    Mesh* square4 = obiecte::CreateSquare("square4", corner, 30, glm::vec3(1, 0, 0), true);
    AddMeshToList(square4);

    //patrat maro/obstacol
    Mesh* square10 = obiecte::CreateSquare("square10", corner, 200, glm::vec3(0.5, 0.35, 0.05), true);
    AddMeshToList(square10);

    // triunghi alb/jucator/inamic
    Mesh* triangle1 = obiecte::CreateTriangle("triangle1", corner, 25, glm::vec3(1, 1, 1),true);
    AddMeshToList(triangle1);

    // triunghi rosu/jucator
    Mesh* triangle2 = obiecte::CreateTriangle("triangle2", corner, 25, glm::vec3(1, 0, 0),true);
    AddMeshToList(triangle2);
}

glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;
 
    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}

void Tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}

void Tema1::FrameStart()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();

    //camera 
    viewSpace = ViewportSpace(0 - resolution.x / 4, 0 - resolution.y / 4, resolution.x * 3 / 2, resolution.y * 3 / 2);
    SetViewportArea(viewSpace, glm::vec3(0, 0, 0), false);

    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    DrawBullet(visMatrix,deltaTimeSeconds);
    DrawPlayer(visMatrix, deltaTimeSeconds);
    DrawEnemy(visMatrix, deltaTimeSeconds);
    DrawMap(visMatrix);
}

void Tema1::FrameEnd()
{
}

void Tema1::DrawPlayer(glm::mat3 visMatrix, float deltaTimeSeconds) {
    score += deltaTimeSeconds;

    if ((int)score % 10 == 4) {
        //afisare scor la fiecare 4 secunde
        score = 0;
        printf("Your score is = %d\n", player.point);
    }
    if (player.health_point > 0) {
        modelMatrix = visMatrix * transformari::Translate(0, 0);

        //triunghi alb
        modelMatrix = visMatrix * transformari::Translate(player.axeX, player.axeY);
        modelMatrix *= transformari::Translate(player.cx, player.cy);
        modelMatrix *= transformari::Rotate(glm::radians(225.0));
        modelMatrix *= transformari::Rotate(player.angle_bullet);
        RenderMesh2D(meshes["triangle1"], shaders["VertexColor"], modelMatrix);

        //triunghi rosu
        modelMatrix *= transformari::Rotate(glm::radians(135.0));
        modelMatrix *= transformari::Translate(0, player.cy - 1);
        modelMatrix *= transformari::Rotate(glm::radians(225.0));
        RenderMesh2D(meshes["triangle2"], shaders["VertexColor"], modelMatrix);

        //patrat care se roteste in jurul centrului sau
        modelMatrix = visMatrix * transformari::Translate(player.axeX + player.cx, player.axeY + player.cx);
        angularStep += deltaTimeSeconds * 15;
        modelMatrix *= transformari::Rotate(angularStep);
        modelMatrix *= transformari::Translate(0 - player.cx, 0 - player.cy);
        RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

        if (!player.you_can_shot)
            fire_rate += deltaTimeSeconds;

        if (fire_rate >= 0.5) {
            fire_rate = 0;
            player.you_can_shot = true;
        }
        // bara de viata drepunghi verde
        modelMatrix = visMatrix * transformari::Translate(0, 0);
        modelMatrix *= transformari::Translate(player.axeX + 300, player.axeY + 230);
        modelMatrix *= transformari::Scale(player.health_point / 100, 1);
        RenderMesh2D(meshes["hp1"], shaders["VertexColor"], modelMatrix);
        //dreptunghi rosu
        modelMatrix = visMatrix * transformari::Translate(0, 0);
        modelMatrix = visMatrix * transformari::Translate(player.axeX + 300, player.axeY + 230);
        RenderMesh2D(meshes["hp2"], shaders["VertexColor"], modelMatrix);
    }
    else {
        //finalul jocului
        printf("Your score is = %d\n", player.point);
        printf("Game over!!!\n");
        exit(0);
    }
}

void Tema1::DrawMap(glm::mat3 visMatrix) {
    modelMatrix = visMatrix * transformari::Translate(0, 0);
    //dreptunghi orizontal
    modelMatrix = visMatrix * transformari::Translate(400, 150);
    RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

    //dreptunghi verdical in sus
    modelMatrix *= transformari::Rotate(glm::radians(90.0));
    RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

    //dreptunghi orizontal
    modelMatrix = visMatrix * transformari::Translate(0, 0);
    modelMatrix = visMatrix * transformari::Translate(600, 600);
    RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

    //dreptunghi verdical in jos
    modelMatrix *= transformari::Rotate(glm::radians(270.0));
    RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transformari::Translate(0, 0);

    //patrat dreapta jos
    modelMatrix = visMatrix * transformari::Translate(800, 200);
    RenderMesh2D(meshes["square10"], shaders["VertexColor"], modelMatrix);

    //dreptunghi interior
    modelMatrix = visMatrix * transformari::Translate(0, 0);
    RenderMesh2D(meshes["dreptunghi_interior"], shaders["VertexColor"], modelMatrix);

    //dreptuncghi exterior
    modelMatrix = visMatrix * transformari::Translate(0, 0);
    RenderMesh2D(meshes["dreptunghi_exterior"], shaders["VertexColor"], modelMatrix);
}

void Tema1::Draw_one_enemy(glm::mat3 vismatrix,Enemy& inamicul, float deltatime2) {
    //verific daca inamicul mai e in viata
    //daca da il afisez
    if (inamicul.In_life()) {
        modelMatrix = visMatrix * transformari::Translate(inamicul.x, inamicul.y);
        RenderMesh2D(meshes["triangle1"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);
    }
    else {
        //daca nu verific timoul la care ar trebui sa reapara
        if ((int)deltatime2 >= 10 && !inamicul.In_life()) {
            inamicul.Reset();
            modelMatrix = visMatrix * transformari::Translate(inamicul.x, inamicul.y);
            RenderMesh2D(meshes["triangle1"], shaders["VertexColor"], modelMatrix);
            RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);
        }
    }
}

void Tema1::DrawEnemy(glm::mat3 visMatrix, float deltaTimeSeconds)
{
    deltatime1 += deltaTimeSeconds;
    //afisez inamici
    for(int i = 0; i < 5; i++)
        Draw_one_enemy(visMatrix, inamic1[i], deltatime1);

    if (deltatime1 >= 10)
        deltatime1 = 0;
}

void Tema1::DrawBullet(glm::mat3 visMatrix, float deltaTimeSeconds) {
    //caut gloantele care trebuie afisate
    for (int i = 0; i < 10; i++) {
        if (bullets[i].dmg) {
            //calculez urmatoare aparitie
            bullets[i].x += bullets[i].distX * 5;
            bullets[i].y += bullets[i].distY * 5;
            //afisez
            modelMatrix *= transformari::Translate(bullets[i].x, bullets[i].y);
            modelMatrix *= transformari::Rotate(bullets[i].angle + glm::radians(90.0));
            RenderMesh2D(meshes["bullet_t"], shaders["VertexColor"], modelMatrix);
            //scad timpul
            bullets[i].Time_move(deltaTimeSeconds);
        }
        //verific daca urmatoarea pozite e corecta
        if (!Check_bullet_move(bullets[i].x, true, false, i) || !Check_bullet_move(bullets[i].y, false, true, i))
            bullets[i].Disappear();
    }
}

bool Tema1::Corect_interval(float nr, float bot_limit, float top_limit) {
    // verifica daca un numar apartine unui interval
    if (nr >= bot_limit && nr <= top_limit)
        return true;
    else
        return false;
}

bool Tema1::Check_bullet_move(float move, bool Xmov, bool Ymov, int j) {
    //mutarea are loc pe axa OX
    if (Xmov) {
        //pozitiile inamicilor
        for (int i = 0; i < 10; i++) {
            if (Corect_interval(move, inamic1[i].x - 10, inamic1[i].x + 30) &&
                Corect_interval(bullets[j].y, inamic1[i].y - 10, inamic1[i].y + 30) &&
                inamic1[i].In_life()) {
                inamic1[i].You_lose_your_life();
                player.Scoreup();
                return true;
            }
        }
        //perete mapa
        if (Corect_interval(move, -200, 30) && Corect_interval(bullets[j].y, -200, 720))
            return false;
        if (Corect_interval(move, 1240, 1280) && Corect_interval(bullets[j].y, -200, 720))
            return false;

        //obstacol jos
        if (Corect_interval(move, 360, 555) && Corect_interval(bullets[j].y, 130, 180))
            return false;
        if (Corect_interval(move, 360, 410) && Corect_interval(bullets[j].y, 130, 305))
            return false;

        //obstacol sus
        if (Corect_interval(move, 585, 755) && Corect_interval(bullets[j].y, 580, 625))
            return false;
        if (Corect_interval(move, 585, 630) && Corect_interval(bullets[j].y, 430, 540))
            return false;

        //patrat
        if (Corect_interval(move, 780, 1010) && Corect_interval(bullets[j].y, 180, 410))
            return false;
    }
    //mutarea are loc pe axa OY
    if (Ymov) {
        //poztiile inamicilor
        for (int i = 0; i < 10; i++) {
            if (Corect_interval(bullets[j].x, inamic1[i].x - 10, inamic1[i].x + 30) &&
                Corect_interval(move, inamic1[i].y - 10, inamic1[i].y + 30) &&
                inamic1[i].In_life()) {
                inamic1[i].You_lose_your_life();
                player.Scoreup();
                return true;
            }
        }
        //perete mapa
        if (Corect_interval(bullets[j].x, -200, 1280) && Corect_interval(move, 680, 720))
            return false;
        if (Corect_interval(bullets[j].x, -200, 1280) && Corect_interval(move, -200, 30))
            return false;

        //obstacol jos
        if (Corect_interval(bullets[j].x, 360, 555) && Corect_interval(move, 130, 180))
            return false;
        if (Corect_interval(bullets[j].x, 360, 410) && Corect_interval(move, 130, 305))
            return false;

        //obstacol sus
        if (Corect_interval(bullets[j].x, 585, 755) && Corect_interval(move, 580, 625))
            return false;
        if (Corect_interval(bullets[j].x, 585, 630) && Corect_interval(move, 430, 540))
            return false;

        //patrat
        if (Corect_interval(bullets[j].x, 780, 1010) && Corect_interval(move, 180, 410))
            return false;
    }
    return true;
}

bool Tema1::Check_move(float move,bool Xmov, bool Ymov) {
    //mutarea are loc pe axa OX
    if (Xmov) {
        //pozitiile inamicilor
        for (int i = 0; i < 10; i++) {
            if (Corect_interval(move, inamic1[i].x - 50, inamic1[i].x + 30) &&
                Corect_interval(player.axeY, inamic1[i].y - 50, inamic1[i].y + 30) &&
                inamic1[i].In_life()) {
                player.You_lose_your_life();
                inamic1[i].You_lose_your_life();
                player.Scoreup();
                return true;
            }
        }
        //perete mapei
        if (Corect_interval(move, 0, 30) && Corect_interval(player.axeY, 0, 720))
            return false;
        if (Corect_interval(move, 1200, 1280) && Corect_interval(player.axeY, 0, 720))
            return false;

        //obstacol stanga jos
        if (Corect_interval(move, 320, 555) && Corect_interval(player.axeY, 90, 180))
            return false;
        if (Corect_interval(move, 320, 410) && Corect_interval(player.axeY, 90, 305))
            return false;
        
        //obstacol sus
        if (Corect_interval(move, 545, 755) && Corect_interval(player.axeY, 540, 625))
            return false;
        if (Corect_interval(move, 545, 630) && Corect_interval(player.axeY, 390, 540))
            return false;

        //obstacol dreapta jos
        if (Corect_interval(move, 740, 1010) && Corect_interval(player.axeY, 140, 410))
            return false;
    }
    //mutarea are loc pe axa OY
    if (Ymov) {
        //poztiile inamicilor
        for (int i = 0; i < 10; i++) {
            if (Corect_interval(player.axeX, inamic1[i].x - 50, inamic1[i].x + 30) &&
                Corect_interval(move, inamic1[i].y - 50, inamic1[i].y + 30) &&
                inamic1[i].In_life()) {
                player.You_lose_your_life();
                inamic1[i].You_lose_your_life();
                player.Scoreup();
                return true;
            }
        }
        //perete mapa
        if (Corect_interval(player.axeX, 0, 1280) && Corect_interval(move, 640, 720))
            return false;
        if (Corect_interval(player.axeX, 0, 1280) && Corect_interval(move, 0, 30))
            return false;

        //obstacol stanga jos
        if (Corect_interval(player.axeX, 320, 555) && Corect_interval(move, 90, 180))
            return false;
        if (Corect_interval(player.axeX, 320, 410) && Corect_interval(move, 90, 305))
            return false;

        //obstacol sus
        if (Corect_interval(player.axeX, 545, 755) && Corect_interval(move, 540, 625))
            return false;
        if (Corect_interval(player.axeX, 545, 630) && Corect_interval(move, 390, 540))
            return false;

        //obstacol dreapta jos
        if (Corect_interval(player.axeX, 740, 1010) && Corect_interval(move, 140, 410))
            return false;
    }
    return true;
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    //miscare in dreapta
    if (window->KeyHold(GLFW_KEY_D)) {
        if (Check_move(player.axeX + deltaTime * 90, true, false)) {
            player.axeX += deltaTime * 90;
            logicSpace.x += deltaTime * 90;
        }
    }
    //miscare in stanga
    if (window->KeyHold(GLFW_KEY_A)) {
        if (Check_move(player.axeX - deltaTime * 90, true, false)) {
            player.axeX -= deltaTime * 90;
            logicSpace.x -= deltaTime * 90;
        }
    }
    //miscare in sus
    if (window->KeyHold(GLFW_KEY_W)) {
        if (Check_move(player.axeY + deltaTime * 90, false, true)) {
            player.axeY += deltaTime * 90;
            logicSpace.y += deltaTime * 90;
        }
    }
    //miscare in jos
    if (window->KeyHold(GLFW_KEY_S)) {
        if (Check_move(player.axeY - deltaTime * 90, false, true)) {
            logicSpace.y -= deltaTime * 90;
            player.axeY -= deltaTime * 90;
        }
    }
}

void Tema1::OnKeyPress(int key, int mods)
{
}

void Tema1::OnKeyRelease(int key, int mods)
{
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    //calculez unghiul pentru orientarea jucatorului
    glm::ivec2 resolution = window->GetResolution();
    double _X = mouseX - player.axeX + (resolutionIx - resolution.x) / 2 + logicSpace.x;
    double _Y = mouseY - player.axeY + (resolutionIy - resolution.y) / 2 + logicSpace.y;
    player.angle_bullet = 3.5 * M_PI  - atan2(_Y, _X);

}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{

    glm::ivec2 resolution = window->GetResolution();
    if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
        if (player.you_can_shot) {
            //daca jucatorul poate trage
            //caulculez traiectoria glonutului
            float x, y;
            float dist = glm::sqrt((mouseY - player.axeY) * (mouseY - player.axeY) + (mouseX - player.axeX) * (mouseX - player.axeX));
            x = dist / player.axeX;
            y = dist / player.axeY;
            for (int i = 0; i < 10; i++) {
                //fiacre glont are un timp cat poate parcurge o anumita distanta
                if (bullets[i].time < 0.0)
                    bullets[i].Disappear();
                //caut glontul nefolosit si ii dau coordonatele corespunzatoare
                if (!bullets[i].dmg) {
                    bullets[i].angle = player.angle_bullet;
                    bullets[i].Reset(player.axeX, player.axeY, x, y);
                    break;
                }
            }
            player.you_can_shot = false;
        }
    }
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}