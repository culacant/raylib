#include <raylib.h>
#include <rlgl.h>
#include <stdio.h>
#include <stdlib.h>

void model_draw_normals(Model model)
{
    for(int i=0;i<model.meshCount;i++)
    {
        Vector3 *vertices = (Vector3*)model.meshes[i].animVertices;
        Vector3 *normals = (Vector3*)model.meshes[i].animNormals;
        for(int j=0;j<model.meshes[i].vertexCount;j++)
        {
            if(j%2)
                normals[j] = Vector3Normalize(normals[j]);
            DrawLine3D(vertices[j],Vector3Add(vertices[j],normals[j]),BLUE);
        }
    }
}

void dump_model(Model model)
{
    printf("Dumping model info\n");
    printf("meshcount: \t %i\n",model.meshCount);
    for(int i=0;i<model.meshCount;i++)
    {
        printf("Mesh info %i\n",i);
        printf("vertexCount: \t %i\n",model.meshes[i].vertexCount);
        printf("triangleCount: \t %i\n",model.meshes[i].triangleCount);
        printf("vaoId: \t %i\n",model.meshes[i].vaoId);
        for(int j=0;j<7;j++)
            printf("vboId[%i]: \t %i\n",j,model.meshes[i].vboId[j]);
        printf("boncnt \t %i\n",model.boneCount);
    }
}

int main()
{
    int screenWidth = 800;
    int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [models] example - obj model loading");
/*
    Model iqm = LoadIQM("guy.iqm");
    rlLoadMesh(&iqm.meshes[0],false);
*/
    Camera camera = {{ 3.0f, 3.0f, 3.0f }, { 0.0f, 1.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f };
    Model mrfixit = LoadModel("mrfixit.iqm");
    for(int i=0;i<mrfixit.boneCount;i++)
        printf("BONE %i\t:%s\n",i,mrfixit.bones[i].name);
    int animcnt = 0;
    ModelAnimation *anims = LoadModelAnimations("mrfixit.iqm",&animcnt);
//    return 0;
    Shader shader = LoadShader("vertex.vs","fragment.fs");
    /*
    int posetransloc = GetShaderLocation(shader,"weights");
    SetShaderValueV(shader, posetransloc, const void *value, UNIFORM_VEC3, count);
    */
    for(int i=0;i<mrfixit.materialCount;i++)
    {
        mrfixit.materials[i].shader = shader;
    }
    int frame = 0;
    /*
    int animcnt = 0;
    ModelAnimation *anims = LoadModelAnimations("mrfixit.iqm",&animcnt);
    */
    Vector3 position = { 0.0f, 0.0f, 0.0f };
    SetTargetFPS(60);
    SetCameraMode(camera, CAMERA_FIRST_PERSON);
    while (!WindowShouldClose())
    {
        UpdateCamera(&camera);
        if(IsKeyDown(KEY_SPACE))
        {
            frame++;
            UpdateModelAnimation(mrfixit,anims[0],frame);
        }
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
                DrawModel(mrfixit, position, 1.0f, WHITE);
                DrawGrid(10, 1.0f);
                DrawGizmo(position);
            EndMode3D();
            DrawText("(c) Dwarf 3D model by David Moreno", screenWidth - 200, screenHeight - 20, 10, GRAY);
            DrawFPS(10, 10);
        EndDrawing();
    }
//    UnloadTexture(texture);
    UnloadModel(mrfixit);
    CloseWindow();
    return 0;
}
