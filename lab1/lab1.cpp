#include "lab_m1/lab1/lab1.h"
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

Lab1::Lab1()
{   
    // TODO(student): Never forget to initialize class variables!
    R = 0;
    G = 0;
    B = 0;
    swich_obj = 0;
    X = 0;
    Y = 0;
    Z = 0;
    move_obj = 0;
    rote_X = 3;
    rote_Y = 3;
    unghi = 0;
}


Lab1::~Lab1()
{
}


void Lab1::Init()
{
    // Load a mesh from file into GPU memory. We only need to do it once,
    // no matter how many times we want to draw this mesh.
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;

        Mesh* bunnymash = new Mesh("bunny");
        bunnymash->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "animals"), "bunny.obj");
        meshes[bunnymash->GetMeshID()] = bunnymash;

        Mesh* archmash = new Mesh("Archer");
        archmash->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "characters\\archer"), "Archer.fbx");
        meshes[archmash->GetMeshID()] = archmash;

        Mesh* mesh_sphere = new Mesh("sphere");
        mesh_sphere->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh_sphere->GetMeshID()] = mesh_sphere;
    }

    // TODO(student): Load some more meshes. The value of RESOURCE_PATH::MODELS
    // is actually a path on disk, go there and you will find more meshes.

}


void Lab1::FrameStart()
{
}
 

void Lab1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->props.resolution;

    // Sets the clear color for the color buffer

    // TODO(student): Generalize the arguments of `glClearColor`.
    // You can, for example, declare three variables in the class header,
    // that will store the color components (red, green, blue).
    glClearColor(R, G, B, 1);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    // Render the object
    RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

    // Render the object again but with different properties
    RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

    // TODO(student): We need to render (a.k.a. draw) the mesh that
    // was previously loaded. We do this using `RenderMesh`. Check the
    // signature of this function to see the meaning of its parameters.
    // You can draw the same mesh any number of times.
    if(swich_obj == 0 )
        RenderMesh(meshes["bunny"], glm::vec3(3, 1, 0), glm::vec3(0.05f));
    else if(swich_obj == 1)
        RenderMesh(meshes["Archer"], glm::vec3(3, 1, 0), glm::vec3(0.01f));
    else
        RenderMesh(meshes["sphere"], glm::vec3(3, 1, 0));
    
    RenderMesh(meshes["Archer"], glm::vec3(0 + X, 0 + Y, -3 + Z), glm::vec3(0.01f));

    //bonus ex6
    unghi += 0.3;

    if (unghi > 360.0f)
        unghi = 0.0f;

    float radian = glm::radians(unghi);
    float raza = glm::distance(3.0, 0.0);
    rote_X = 0 + (raza * cosf(radian));
    rote_Y = 0 + (raza * sinf(radian));

    RenderMesh(meshes["sphere"], glm::vec3(rote_X, rote_Y, -3));
}


void Lab1::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab1::OnInputUpdate(float deltaTime, int mods)
{
    // Treat continuous update based on input

    // TODO(student): Add some key hold events that will let you move
    // a mesh instance on all three axes. You will also need to
    // generalize the position used by `RenderMesh`.
    //ex 5
    if (move_obj == 1){
        if (window->KeyHold(GLFW_KEY_D)) {
            X += 60 * deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_A)) {
            X -= 60 * deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_E)) {
            Y += 60 * deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_Q)) {
            Y -= 60 * deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_W)) {
            Z += 60 * deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_S)) {
            Z -= 60 * deltaTime;
        }
    }

}


void Lab1::OnKeyPress(int key, int mods)
{
    // Add key press event
    // ex3 am implementat daca apesi din noi pe F revine la normal 
    // si iar poti schimba
    if (key == GLFW_KEY_F) {
        // TODO(student): Change the values of the color components.
        R++;
        G++;
        if (R >= 2 || G >= 2) {
            R = 0;
            G = 0;
        }
    }
    // pentru a schimba obiectul afisat ex4
    if (key == GLFW_KEY_G) {
        swich_obj++;
        if (swich_obj > 2) 
            swich_obj = 0;
    }
    //cazul cand dormi sa mutam un obiect ex5 ( am pus tasta M pentru ca nu mereu vreau sa mut acel obiect)
    if (key == GLFW_KEY_M) {
        move_obj++;
        if (move_obj > 1)
            move_obj = 0;

    }
    // TODO(student): Add a key press event that will let you cycle
    // through at least two meshes, rendered at the same position.
    // You will also need to generalize the mesh name used by `RenderMesh`.

}


void Lab1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void Lab1::OnWindowResize(int width, int height)
{
    // Treat window resize event
}
