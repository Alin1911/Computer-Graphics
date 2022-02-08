#include "lab_m1/lab5/lab5.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab5::Lab5()
{
    left = -10.0f;
    right = 10.0f;
    top = 5.0f;
    bottom = -5.0;
    fov = 60.0f;
    zNear = 0.01f;
    zFar = 200.0f;
    index = 0;
}


Lab5::~Lab5()
{
}


void Lab5::Init()
{
    renderCameraTarget = false;

    camera = new implemented::Camera();
    camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    camera1 = new implemented::Camera();
    camera1->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    camera2 = new implemented::Camera();
    camera2->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    camera3 = new implemented::Camera();
    camera3->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // TODO(student): After you implement the changing of the projection
    // parameters, remove hardcodings of these parameters
    projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, zNear, zFar);

}


void Lab5::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Lab5::Update(float deltaTimeSeconds)
{
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(0, 1, 0));

        RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0.5f, 0));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(1, 0, 0));
        RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, 0.5f, 0));
        RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
    }

    // TODO(student): Draw more objects with different model matrices.
    // Attention! The `RenderMesh()` function overrides the usual
    // `RenderMesh()` that we've been using up until now. This new
    // function uses the view matrix from the camera that you just
    // implemented, and the local projection matrix.

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(6, 1.0f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.6f));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(65.0f), glm::vec3(1, 0, 0));
        RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(10, 2.0f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(2.0f));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(40.0f), glm::vec3(0, 1, 1));
        RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
    }

    // Render the camera target. This is useful for understanding where
    // the rotation point is, when moving in third-person camera mode.
    if (renderCameraTarget)
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
    }
}


void Lab5::FrameEnd()
{
    if (index == 0)
        DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
    if (index == 1)
        DrawCoordinateSystem(camera1->GetViewMatrix(), projectionMatrix);
    if (index == 2)
        DrawCoordinateSystem(camera2->GetViewMatrix(), projectionMatrix);
    if (index == 3)
        DrawCoordinateSystem(camera3->GetViewMatrix(), projectionMatrix);
}


void Lab5::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    if(index == 0)
        glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    if (index == 1)
        glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera1->GetViewMatrix()));
    if (index == 2)
        glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera2->GetViewMatrix()));
    if (index == 3)
        glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera3->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab5::OnInputUpdate(float deltaTime, int mods)
{
    float cameraSpeed = 2.0f;
    // move the camera only if MOUSE_RIGHT button is pressed
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {

        if (window->KeyHold(GLFW_KEY_W)) {
            // TODO(student): Translate the camera forward
            camera->TranslateForward(deltaTime * cameraSpeed);

        }

        if (window->KeyHold(GLFW_KEY_A)) {
            // TODO(student): Translate the camera to the left
            camera->TranslateRight(-deltaTime * cameraSpeed);

        }

        if (window->KeyHold(GLFW_KEY_S)) {
            // TODO(student): Translate the camera backward
            camera->TranslateForward(-deltaTime * cameraSpeed);

        }

        if (window->KeyHold(GLFW_KEY_D)) {
            // TODO(student): Translate the camera to the right
            camera->TranslateRight(deltaTime * cameraSpeed);

        }

        if (window->KeyHold(GLFW_KEY_Q)) {
            // TODO(student): Translate the camera downward
            camera->TranslateUpward(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_E)) {
            // TODO(student): Translate the camera upward
            camera->TranslateUpward(deltaTime * cameraSpeed);
        }

        // TODO(student): Change projection parameters. Declare any extra
        // variables you might need in the class header. Inspect this file
        // for any hardcoded projection arguments (can you find any?) and
        // replace them with those extra variables.
    }

    {
        if (window->KeyHold(GLFW_KEY_UP) && ortho) {
            top += deltaTime;
            bottom -= deltaTime;
            projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
        }
        if (window->KeyHold(GLFW_KEY_DOWN) && ortho) {
            top -= deltaTime;
            bottom += deltaTime;
            projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
        }
        if (window->KeyHold(GLFW_KEY_RIGHT) && ortho) {
            right += deltaTime;
            left -= deltaTime;
            projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
        }
        if (window->KeyHold(GLFW_KEY_LEFT) && ortho) {
            right -= deltaTime;
            left += deltaTime;
            projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
        }

        // cresc FOV
        if (window->KeyHold(GLFW_KEY_L)) {
            fov += deltaTime * cameraSpeed;
            if(!ortho)
                projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, zNear, zFar);
        }
        // scad FOV
        if (window->KeyHold(GLFW_KEY_K)) {
            fov += deltaTime * cameraSpeed;
            if(!ortho)
                projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, zNear, zFar);
        }
    }

}


void Lab5::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_T)
    {
        renderCameraTarget = !renderCameraTarget;
    }
    // TODO(student): Switch projections

    //proiectie ortografica
    if (key == GLFW_KEY_O) {
        ortho = true;
        projectionMatrix = glm::ortho(left, top, bottom, top, zNear, zFar);
    }

    //proiectie perspectiva
    if (key == GLFW_KEY_P)
    {
        projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, zNear, zFar);
        ortho = false;
    }

    //bonus
    //am creat 4 obiecte tip camera
    // si le-am pozitionat diferit
    if (key == GLFW_KEY_Z) {

        index++;
        if (index == 4)
            index = 0;
        printf("Te afli pe camera %d\n", index);
        if (index == 0) {
            //camera inittiala din laborator
            camera->Set(glm::vec3(0, 2, 3.5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
        }
        if (index == 1) {
            camera1->Set(glm::vec3(0, 10, 3.5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
            camera1->RotateFirstPerson_OY(-RADIANS(10));
        }
        if (index == 2) {
            camera2->Set(glm::vec3(15, 10, -3.5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
            camera2->RotateFirstPerson_OX(-0.2);
            camera2->RotateFirstPerson_OY(-0.3);
        }
        if (index == 3) {
            camera3->Set(glm::vec3(-15, 10, 3.5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
            camera3->RotateFirstPerson_OX(-0.1);
            camera3->RotateFirstPerson_OY(-0.3);
        }
    }
}


void Lab5::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab5::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            renderCameraTarget = false;
            // TODO(student): Rotate the camera in first-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateFirstPerson_OX(-sensivityOX * deltaX);
            camera->RotateFirstPerson_OY(-sensivityOY * deltaY);
        }

        if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
            renderCameraTarget = true;
            // TODO(student): Rotate the camera in third-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateFirstPerson_OX(sensivityOX * deltaX);
            camera->RotateFirstPerson_OY(sensivityOY * deltaY);

        }
    }
}


void Lab5::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab5::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab5::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab5::OnWindowResize(int width, int height)
{
}
