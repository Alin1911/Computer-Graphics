#include "lab_m1/Tema2/Tema2.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
    fov = 90.0f;
    zNear = 0.01f;
    zFar = 200.0f;
    angle = 0;
    Y = 1;
    viata = 100;
    timp = 3;
    camera_type = 1;
    one_time_var = 0;
    
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    srand(time(0));
    random_nr = rand() % 4;
    switch (random_nr) {
    case 0: {
        int map1[10][10] = {
            0,4,0,0,0,0,0,0,0,0,
            0,2,1,1,1,1,1,1,0,0,
            0,1,0,0,1,0,0,0,1,0,
            0,1,1,2,1,0,0,2,1,0,
            0,1,0,0,1,1,1,1,0,0,
            0,0,1,0,1,0,1,0,0,0,
            0,2,1,1,1,0,1,1,0,0,
            0,0,1,0,0,0,0,1,3,0,
            0,0,1,1,2,2,1,0,0,0,
            0,0,0,0,0,0,0,0,0,0
        };
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                map[i][j] = map1[i][j];
                if (map[i][j] == 3) {
                    X = i;
                    Z = j;
                }
            }
        }
        break;
    }
    case 1: {
        int map1[10][10] = {
            0,0,0,0,0,0,0,0,0,0,
            0,2,1,1,1,1,1,1,0,0,
            0,1,0,0,1,0,0,0,1,4,
            0,1,1,2,1,0,0,2,1,0,
            0,1,0,0,1,1,1,1,0,0,
            0,2,1,1,1,0,1,1,0,0,
            0,3,1,0,0,0,0,1,0,0,
            0,0,1,1,2,2,0,0,0,0,
            0,0,1,1,2,1,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,

        };
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                map[i][j] = map1[i][j];
                if (map[i][j] == 3) {
                    X = i;
                    Z = j;
                }
            }
        }
        break;
    }
    case 2: {
        int map1[10][10] = {
            0,0,0,0,0,0,0,0,0,0,
            0,2,1,1,1,1,1,1,0,0,
            0,1,0,0,1,0,0,1,1,0,
            0,1,1,2,1,0,0,2,1,0,
            4,1,1,1,1,1,1,1,1,0,
            0,0,1,0,1,0,1,1,1,0,
            0,2,1,1,1,0,1,1,0,0,
            0,2,1,1,0,0,1,1,3,0,
            0,0,1,1,2,2,1,1,0,0,
            0,0,0,0,0,0,0,0,0,0
        };
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                map[i][j] = map1[i][j];
                if (map[i][j] == 3) {
                    X = i;
                    Z = j;
                }
            }
        }
        break;
    }
    case 3: {
        int map1[10][10] = {
            0,0,0,0,0,0,0,0,0,0,
            0,3,1,1,1,1,1,1,0,0,
            0,1,0,0,1,0,0,1,1,0,
            0,1,1,2,1,0,0,2,1,0,
            0,1,1,1,1,1,1,1,1,0,
            0,0,1,0,1,0,1,1,1,0,
            0,2,1,1,1,0,2,2,0,0,
            0,2,1,1,0,0,1,1,1,4,
            0,0,1,1,2,2,1,1,0,0,
            0,0,0,0,0,0,0,0,0,0
        };
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                map[i][j] = map1[i][j];
                if (map[i][j] == 3) {
                    X = i;
                    Z = j;
                }
            }
        }
        break;
    }
    }

    renderCameraTarget = false;

    camera = new implemented::Cameraa();
    camera->Set(glm::vec3(4 * X - 19, Y + 2.5, 4 * Z - 19), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0,  1), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1, 0,  1), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 1,  1), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1, 1,  1), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1, 0,  0), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 1,  0), glm::vec3(1, 1, 1), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1, 1,  0), glm::vec3(1, 0, 1), glm::vec3(0.2, 0.8, 0.6)),
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4
        };
        CreateMesh("cube_verde", vertices, indices);
    }
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0,  1), glm::vec3(0, 1, 1), glm::vec3(1, 0.0, 0.0)),
            VertexFormat(glm::vec3(1, 0,  1), glm::vec3(1, 0, 1), glm::vec3(1, 0.0, 0.0)),
            VertexFormat(glm::vec3(0, 1,  1), glm::vec3(0, 0, 1), glm::vec3(1, 0.0, 0.0)),
            VertexFormat(glm::vec3(1, 1,  1), glm::vec3(1, 0, 1), glm::vec3(1, 0.0, 0.0)),
            VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0, 1, 1), glm::vec3(1, 0.0, 0.0)),
            VertexFormat(glm::vec3(1, 0,  0), glm::vec3(1, 0, 1), glm::vec3(1, 0.0, 0.0)),
            VertexFormat(glm::vec3(0, 1,  0), glm::vec3(1, 1, 1), glm::vec3(1, 0.0, 0.0)),
            VertexFormat(glm::vec3(1, 1,  0), glm::vec3(1, 0, 1), glm::vec3(1, 0.0, 0.0))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4
        };
        CreateMesh("cube_rosu", vertices, indices);
    }
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0,  1), glm::vec3(0, 1, 1), glm::vec3(0, 1.0, 0.0)),
            VertexFormat(glm::vec3(1, 0,  1), glm::vec3(1, 0, 1), glm::vec3(0, 1.0, 0.0)),
            VertexFormat(glm::vec3(0, 1,  1), glm::vec3(0, 0, 1), glm::vec3(0, 1.0, 0.0)),
            VertexFormat(glm::vec3(1, 1,  1), glm::vec3(1, 0, 1), glm::vec3(0, 1.0, 0.0)),
            VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0, 1, 1), glm::vec3(0, 1.0, 0.0)),
            VertexFormat(glm::vec3(1, 0,  0), glm::vec3(1, 0, 1), glm::vec3(0, 1.0, 0.0)),
            VertexFormat(glm::vec3(0, 1,  0), glm::vec3(1, 1, 1), glm::vec3(0, 1.0, 0.0)),
            VertexFormat(glm::vec3(1, 1,  0), glm::vec3(1, 0, 1), glm::vec3(0, 1.0, 0.0))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4
        };
        CreateMesh("cube_verde_win", vertices, indices);
    }
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0,  1), glm::vec3(0, 1, 1), glm::vec3(0.3, 0.2, 1.4)),
            VertexFormat(glm::vec3(1, 0,  1), glm::vec3(1, 0, 1), glm::vec3(0.3, 0.2, 1.4)),
            VertexFormat(glm::vec3(0, 1,  1), glm::vec3(0, 0, 1), glm::vec3(0.3, 0.2, 1.4)),
            VertexFormat(glm::vec3(1, 1,  1), glm::vec3(1, 0, 1), glm::vec3(0.3, 0.2, 1.4)),
            VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0, 1, 1), glm::vec3(0.3, 0.2, 1.4)),
            VertexFormat(glm::vec3(1, 0,  0), glm::vec3(1, 0, 1), glm::vec3(0.3, 0.2, 1.4)),
            VertexFormat(glm::vec3(0, 1,  0), glm::vec3(1, 1, 1), glm::vec3(0.3, 0.2, 1.4)),
            VertexFormat(glm::vec3(1, 1,  0), glm::vec3(1, 0, 1), glm::vec3(0.3, 0.2, 1.4)),
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4
        };
        CreateMesh("cube_perete", vertices, indices);
    }
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0,  1), glm::vec3(0, 1, 1), glm::vec3(0.0, 0.0, 1.0)),
            VertexFormat(glm::vec3(1, 0,  1), glm::vec3(1, 0, 1), glm::vec3(0.0, 0.0, 1.0)),
            VertexFormat(glm::vec3(0, 1,  1), glm::vec3(0, 0, 1), glm::vec3(0.0, 0.0, 1.0)),
            VertexFormat(glm::vec3(1, 1,  1), glm::vec3(1, 0, 1), glm::vec3(0.0, 0.0, 1.0)),
            VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0, 1, 1), glm::vec3(0.0, 0.0, 1.0)),
            VertexFormat(glm::vec3(1, 0,  0), glm::vec3(1, 0, 1), glm::vec3(0.0, 0.0, 1.0)),
            VertexFormat(glm::vec3(0, 1,  0), glm::vec3(1, 1, 1), glm::vec3(0.0, 0.0, 1.0)),
            VertexFormat(glm::vec3(1, 1,  0), glm::vec3(1, 0, 1), glm::vec3(0.0, 0.0, 1.0)),
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4
        };
        CreateMesh("cube_albastru", vertices, indices);
    }
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0,  1), glm::vec3(0, 1, 1), glm::vec3(0.72, 0.45, 0.2)),
            VertexFormat(glm::vec3(1, 0,  1), glm::vec3(1, 0, 1), glm::vec3(0.72, 0.45, 0.2)),
            VertexFormat(glm::vec3(0, 1,  1), glm::vec3(0, 0, 1), glm::vec3(0.72, 0.45, 0.2)),
            VertexFormat(glm::vec3(1, 1,  1), glm::vec3(1, 0, 1), glm::vec3(0.72, 0.45, 0.2)),
            VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0, 1, 1), glm::vec3(0.72, 0.45, 0.2)),
            VertexFormat(glm::vec3(1, 0,  0), glm::vec3(1, 0, 1), glm::vec3(0.72, 0.45, 0.2)),
            VertexFormat(glm::vec3(0, 1,  0), glm::vec3(1, 1, 1), glm::vec3(0.72, 0.45, 0.2)),
            VertexFormat(glm::vec3(1, 1,  0), glm::vec3(1, 0, 1), glm::vec3(0.72, 0.45, 0.2)),
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4
        };
        CreateMesh("cube_crem", vertices, indices);
    }    projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, zNear, zFar);

}
void Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
    //ex3
    unsigned int VAO = 0;
    // TODO(student): Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO = 0;
    // TODO(student): Create the VBO and bind it			
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // TODO(student): Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    unsigned int IBO = 0;
    // TODO(student): Create the IBO and bind it
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // TODO(student): Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // ========================================================================
    // This section demonstrates how the GPU vertex shader program
    // receives data. It will be learned later, when GLSL shaders will be
    // introduced. For the moment, just think that each property value from
    // our vertex format needs to be sent to a certain channel, in order to
    // know how to receive it in the GLSL vertex shader.

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // TODO(student): Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    if (GetOpenGLError() == GL_INVALID_OPERATION)
    {
        cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
        cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
    }

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
}

void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
    if (camera_type == 0) {
        //fp
        camera->distanceToTarget = 2;
        if (one_time_var == 1) {
            camera->MoveForward(2);
            one_time_var = 0;
        }
    }
    else {
        //tp
        X = camera->GetTargetPosition().x;
        Z = camera->GetTargetPosition().z;
        if (one_time_var == 0) {
            camera->MoveForward(-2);
            one_time_var = 1;
        }
        camera->distanceToTarget = 3;
    
        glm::mat4 modelMatrix = glm::mat4(1);

        modelMatrix *= transform3DD::Translate(X, Y, Z);
        glm::mat4 trunchi = modelMatrix;

        modelMatrix *= transform3DD::Scale(0.75, 1.5 , 0.5);
        RenderMesh(meshes["cube_verde"], shaders["VertexNormal"], modelMatrix);

        glm::mat4 brat_dreapta = trunchi * transform3DD::Translate(0.8, 0.5, 0);
        brat_dreapta *= transform3DD::Scale(0.5, 1, 0.5);
        RenderMesh(meshes["cube_verde"], shaders["VertexNormal"], brat_dreapta);

        brat_dreapta = trunchi * transform3DD::Translate(0.8 , 0, 0);
        brat_dreapta *= transform3DD::Scale(0.5, 0.45, 0.5);
        RenderMesh(meshes["cube_crem"], shaders["VertexNormal"], brat_dreapta);

        glm::mat4 brat_stanga = trunchi * transform3DD::Translate(-0.55, 0.5, 0);
        brat_stanga *= transform3DD::Scale(0.5, 1, 0.5);
        RenderMesh(meshes["cube_verde"], shaders["VertexNormal"], brat_stanga);
        brat_stanga = trunchi * transform3DD::Translate(-0.55, 0, 0);
        brat_stanga *= transform3DD::Scale(0.5, 0.45, 0.5);
        RenderMesh(meshes["cube_crem"], shaders["VertexNormal"], brat_stanga);

        glm::mat4 cap = trunchi * transform3DD::Translate(0, 1.55, 0);
        cap *= transform3DD::Scale(0.75, 0.55, 0.5);
        RenderMesh(meshes["cube_crem"], shaders["VertexNormal"], cap);

        glm::mat4 picior_dreapta = trunchi * transform3DD::Translate(0, -1.05, 0);
        picior_dreapta *= transform3DD::Scale(0.35, 1, 0.5);
        RenderMesh(meshes["cube_albastru"], shaders["VertexNormal"], picior_dreapta);

        glm::mat4 picior_stanga = trunchi * transform3DD::Translate(0.4, -1.05, 0);
        picior_stanga *= transform3DD::Scale(0.35, 1, 0.5);
        RenderMesh(meshes["cube_albastru"], shaders["VertexNormal"], picior_stanga);
    }

    {
        if (camera_type == 0) {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transform3DD::Translate(camera->GetTargetPosition().x, camera->GetTargetPosition().y, camera->GetTargetPosition().z);
            modelMatrix *= transform3DD::Scale(0.1, 0.1, 0.1);
            RenderMesh(meshes["cube_albastru"], shaders["VertexNormal"], modelMatrix);
        }
    }
    {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                glm::mat4 modelMatrix = glm::mat4(1) * transform3DD::Translate(-40 , 0, -40);
                modelMatrix *= transform3DD::Translate(8 * i, 0, 8 * j);
                modelMatrix *= transform3DD::Scale(7.95, 0.01, 7.95);
                RenderMesh(meshes["cube_rosu"], shaders["VertexNormal"], modelMatrix);

                switch (map[i][j]) {
                case 0: {
                    glm::mat4 modelMatrix = glm::mat4(1) * transform3DD::Translate(-40, 0, -40);
                    modelMatrix *= transform3DD::Translate(8 * i, 0, 8 * j);
                    modelMatrix *= transform3DD::Scale(7.95, 15, 7.95);
                    RenderMesh(meshes["cube_perete"], shaders["VertexNormal"], modelMatrix);
                    break;
                }
                case 1: {
                    //pot trece
                    continue;
                    break;
                }
                case 2: {
                    //inamic
                    continue;
                    break;
                }
                case 3: {
                    //pozitie initiala
                    continue;
                    break;
                }
                case 4: {
                    glm::mat4 modelMatrix = glm::mat4(1) * transform3DD::Translate(-40, 0, -40);
                    modelMatrix *= transform3DD::Translate(8 * i, 0, 8 * j);
                    modelMatrix *= transform3DD::Scale(7.95, 0.02, 7.95);
                    RenderMesh(meshes["cube_verde_win"], shaders["VertexNormal"], modelMatrix);
                    continue;
                    break;
                }
                default: {
                    continue;
                    break;
                }
                }

            }
        }

    }
}


void Tema2::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();

    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    float cameraSpeed = 2.0f;
    if (camera_type == 1) {
        if (window->KeyHold(GLFW_KEY_W)) {
            camera->MoveForward(deltaTime * cameraSpeed);

        }

        if (window->KeyHold(GLFW_KEY_A)) {
            camera->TranslateRight(-deltaTime * cameraSpeed);

        }

        if (window->KeyHold(GLFW_KEY_S)) {
            camera->MoveForward(-deltaTime * cameraSpeed);

        }

        if (window->KeyHold(GLFW_KEY_D)) {
            camera->TranslateRight(deltaTime * cameraSpeed);

        }
    }

}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_T)
    {
        renderCameraTarget = !renderCameraTarget;
    }
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
            renderCameraTarget = false;
            camera->RotateFirstPerson_OX(-sensivityOX * deltaX);
            camera->RotateFirstPerson_OY(-sensivityOY * deltaY);
            angle = deltaX;
            camera_type = 0;
        }

        if (window->GetSpecialKeyState() == 0) {
            renderCameraTarget = true;
            camera->RotateThirdPerson_OX(sensivityOX * deltaX);
            camera->RotateThirdPerson_OY(sensivityOY * deltaY);
            camera_type = 1;

        }
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
