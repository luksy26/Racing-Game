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
    miniMapScale = 0.1f;
    carsScaleFactor = 1.0f / miniMapScale;
    orthoLeft = -16.0f * miniMapScale;
    orthoRight = -orthoLeft;
    orthoUp = 9.0f * miniMapScale;
    orthoDown = -orthoUp;
    fillTerrain = true;
    terrainComplexity = 15;
}


Tema2::~Tema2()
{
}

void Tema2::Init()
{   
    txCar = tzCar = 0;
    speed = turnSpeed = 1.0f;
    enemySpeed = 0.95f;
    for (int i = 0; i < 10; ++i) {
        txEnemies[i] = tzEnemies[i] = 0;
    }
    carHeight = 0.015f;
    carWidth = 0.03f;
    carLength = 0.0525f;
    angOyCar = 27.5f;
    {
        points[0] = glm::vec3(-9.91, 0, 0.25);
        points[1] = glm::vec3(-9, 0, 2);
        points[2] = glm::vec3(-7.62, 0, 3.32);
        points[3] = glm::vec3(-5.98, 0, 2.76);
        points[4] = glm::vec3(-4.49, 0, 3.61);
        points[5] = glm::vec3(-3.48, 0, 5);
        points[6] = glm::vec3(-1.9, 0, 5.6);
        points[7] = glm::vec3(-0.52, 0, 5.22);
        points[8] = glm::vec3(1.68, 0, 4.95);
        points[9] = glm::vec3(3.49, 0, 4.36);
        points[10] = glm::vec3(5.17, 0, 3.27);
        points[11] = glm::vec3(6.96, 0, 3.81);
        points[12] = glm::vec3(8.34, 0, 2.72);
        points[13] = glm::vec3(8.96, 0, 1.34);
        points[14] = glm::vec3(8.49, 0, -0.41);
        points[15] = glm::vec3(8.72, 0, -1.68);
        points[16] = glm::vec3(7.84, 0, -2.89);
        points[17] = glm::vec3(6.15, 0, -3.25);
        points[18] = glm::vec3(4.52, 0, -3);
        points[19] = glm::vec3(3.05, 0, -2.33);
        points[20] = glm::vec3(1.34, 0, -1.61);
        points[21] = glm::vec3(-0.75, 0, -1.95);
        points[22] = glm::vec3(-1.73, 0, -3.15);
        points[23] = glm::vec3(-2.55, 0, -4.2);
        points[24] = glm::vec3(-4.6, 0, -4.27);
        points[25] = glm::vec3(-5.8, 0, -3.37);
        points[26] = glm::vec3(-6.24, 0, -2.02);
        points[27] = glm::vec3(-7.95, 0, -1.69);
        points[28] = glm::vec3(-8.93, 0, -1.2);

        glm::vec3 treePosExterior[30], treePosInterior[30];
        for (int i = 0; i < 28; ++i) {
            treePosExterior[i] = points[i] + 0.25f * cross(points[i + 1] - points[i], glm::vec3(0, 1, 0));
            treePosInterior[i] = points[i] - 0.25f * cross(points[i + 1] - points[i], glm::vec3(0, 1, 0));
            exteriorPoints[i] = points[i] + 0.15f * cross(points[i + 1] - points[i], glm::vec3(0, 1, 0));
            interiorPoints[i] = points[i] - 0.15f * cross(points[i + 1] - points[i], glm::vec3(0, 1, 0));
            leftPoints[i] = points[i] - 0.07f * cross(points[i + 1] - points[i], glm::vec3(0, 1, 0));
            rightPoints[i] = points[i] + 0.07f * cross(points[i + 1] - points[i], glm::vec3(0, 1, 0));

        }
        treePosExterior[28] = points[28] + 0.25f * cross(points[0] - points[28], glm::vec3(0, 1, 0));
        treePosInterior[28] = points[28] - 0.25f * cross(points[0] - points[28], glm::vec3(0, 1, 0));
        exteriorPoints[28] = points[28] + 0.15f * cross(points[0] - points[28], glm::vec3(0, 1, 0));
        interiorPoints[28] = points[28] - 0.15f * cross(points[0] - points[28], glm::vec3(0, 1, 0));
        leftPoints[28] = points[28] - 0.07f * cross(points[0] - points[28], glm::vec3(0, 1, 0));
        rightPoints[28] = points[28] + 0.07f * cross(points[0] - points[28], glm::vec3(0, 1, 0));

        angles[0] = findAngle(points[28], points[0], points[1]);
        for (int i = 1; i < 28; ++i) {
            angles[i] = findAngle(points[i - 1], points[i], points[i + 1]);
        }
        angles[28] = findAngle(points[27], points[28], points[0]);
        int clockWiseIndices[10] = { 3, 4, 7, 10, 14, 19, 20, 21, 22, 26 };
        for (int i = 0; i < 10; ++i) {
            angles[clockWiseIndices[i]] *= -1;
        }

        carInitPoz = points[0] + glm::vec3(0, carHeight, 0);

        enemiesDirection[0] = -1;
        enemiesPos[0] = 2;
        enemiesInitPoz[0] = leftPoints[2] + glm::vec3(0, carHeight, 0);
        enemiesTrack[0] = 2;
        enemiesOyAng[0] = 27.5f + 180 + angles[1];

        enemiesDirection[1] = 1;
        enemiesPos[1] = 5;
        enemiesInitPoz[1] = rightPoints[5] + glm::vec3(0, carHeight, 0);
        enemiesTrack[1] = 1;
        enemiesOyAng[1] = 27.5f + (angles[1] + angles[2] + angles[3] + angles[4] + angles[5]);

        enemiesDirection[2] = 1;
        enemiesPos[2] = 9;
        enemiesInitPoz[2] = points[9] + glm::vec3(0, carHeight, 0);
        enemiesTrack[2] = 0;
        enemiesOyAng[2] = 27.5f + (angles[1] + angles[2] + angles[3] + angles[4] + angles[5] + angles[6] + angles[7] + angles[8] + angles[9]);

        enemiesDirection[3] = -1;
        enemiesPos[3] = 15;
        enemiesInitPoz[3] = leftPoints[15] + glm::vec3(0, carHeight, 0);
        enemiesTrack[3] = 2;
        enemiesOyAng[3] = enemiesOyAng[2] + 180 + angles[10] + angles[11] + angles[12] + angles[13] + angles[14];

        enemiesDirection[4] = -1;
        enemiesPos[4] = 22;
        enemiesInitPoz[4] = leftPoints[22] + glm::vec3(0, carHeight, 0);
        enemiesTrack[4] = 2;
        enemiesOyAng[4] = enemiesOyAng[3] + angles[15] + angles[16] + angles[17] + angles[18] + angles[19] + angles[20] + angles[21];

        enemiesDirection[5] = 1;
        enemiesPos[5] = 26;
        enemiesInitPoz[5] = rightPoints[26] + glm::vec3(0, carHeight, 0);
        enemiesTrack[5] = 1;
        enemiesOyAng[5] = enemiesOyAng[4] - 180 + angles[22] + angles[23] + angles[24] + angles[25] + angles[26];

        enemiesDirection[6] = -1;
        enemiesPos[6] = 7;
        enemiesInitPoz[6] = leftPoints[7] + glm::vec3(0, carHeight, 0);
        enemiesTrack[6] = 2;
        enemiesOyAng[6] = enemiesOyAng[1] + 180 + angles[6];

        enemiesDirection[7] = 1;
        enemiesPos[7] = 17;
        enemiesInitPoz[7] = points[17] + glm::vec3(0, carHeight, 0);
        enemiesTrack[7] = 0;
        enemiesOyAng[7] = enemiesOyAng[3] - 180 + angles[15] + angles[16] + angles[17];;


        camera = new implemented::CameraTema();
        camera->Set(carInitPoz + glm::vec3(0, 0.27, -0.41), carInitPoz, glm::vec3(0, 1, 0));
        camera->RotateThirdPerson_OX(angOyCar / (180.0f / (float)M_PI));

        cameraMiniMap = new implemented::CameraTema();
        cameraMiniMap->Set(carInitPoz + glm::vec3(0, 1, 0.001), carInitPoz, glm::vec3(0, 1, 0));
        cameraMiniMap->RotateThirdPerson_OX(180 - angOyCar / (180.0f / (float)M_PI));

        Mesh* track = objectTema2::CreateTrack("track", points, 29, terrainComplexity, glm::vec3(0.2, 0.2, 0.2), fillTerrain);
        AddMeshToList(track);

        Mesh* trackOutline = objectTema2::TrackOutline("trackOutline", points, 29, glm::vec3(0.8, 0.8, 0.8));
        AddMeshToList(trackOutline);

        Mesh* startLine = objectTema2::StartLine("startLine", exteriorPoints[0], exteriorPoints[1], interiorPoints[1], interiorPoints[0], glm::vec3(0.6, 0.6, 0));
        AddMeshToList(startLine);

        Mesh* trunk;
        Mesh *leaves;
        for (int i = 0; i < 29; ++i) {
            char trunk1[20], trunk2[20], leaves1[20], leaves2[20];
            sprintf(trunk1, "trunk%d", 2 * i);
            sprintf(trunk2, "trunk%d", 2 * i + 1);
            sprintf(leaves1, "leaves%d", 2 * i);
            sprintf(leaves2, "leaves%d", 2 * i + 1);

            trunk = objectTema2::CreateTrunk(trunk1, treePosInterior[i], 0.15f, 0.05f, glm::vec3(0.3f, 0.1, 0));
            AddMeshToList(trunk);
            leaves = objectTema2::CreateLeaves(leaves1, treePosInterior[i], 0.15f, 0.05f, glm::vec3(0.2f, 0.41f, 0.1f));
            AddMeshToList(leaves);

            trunk = objectTema2::CreateTrunk(trunk2, treePosExterior[i], 0.15f, 0.05f, glm::vec3(0.3f, 0.1f, 0));
            AddMeshToList(trunk);
            leaves = objectTema2::CreateLeaves(leaves2, treePosExterior[i], 0.15f, 0.05f, glm::vec3(0.2f, 0.41f, 0.1f));
            AddMeshToList(leaves);
        }
    }

    {
        Mesh* car = objectTema2::CreateCar("car", carInitPoz, carLength, carWidth, carHeight, glm::vec3(0.8, 0, 0.1));
        AddMeshToList(car);
    }

    {
        Mesh* car = objectTema2::CreateCar(enemies[0], enemiesInitPoz[0], carLength, carWidth, carHeight, glm::vec3(0.2, 0.3, 0.6));
        AddMeshToList(car);  // blue
    }

    {
        Mesh* car = objectTema2::CreateCar(enemies[1], enemiesInitPoz[1], carLength, carWidth, carHeight, glm::vec3(0.1, 0.4, 0.1));
        AddMeshToList(car);  // green
    }

    {
        Mesh* car = objectTema2::CreateCar(enemies[2], enemiesInitPoz[2], carLength, carWidth, carHeight, glm::vec3(0.5, 0.2, 0.6));
        AddMeshToList(car);  // purple
    }

    {
        Mesh* car = objectTema2::CreateCar(enemies[3], enemiesInitPoz[3], carLength, carWidth, carHeight, glm::vec3(0.6, 0.6, 0.2));
        AddMeshToList(car);  // yellow
    }

    {
        Mesh* car = objectTema2::CreateCar(enemies[4], enemiesInitPoz[4], carLength, carWidth, carHeight, glm::vec3(0.03, 0.03, 0.03));
        AddMeshToList(car);  // black 
    }

    {
        Mesh* car = objectTema2::CreateCar(enemies[5], enemiesInitPoz[5], carLength, carWidth, carHeight, glm::vec3(0.6, 0.3, 0));
        AddMeshToList(car);  // brown
    }

    {
        Mesh* car = objectTema2::CreateCar(enemies[6], enemiesInitPoz[6], carLength, carWidth, carHeight, glm::vec3(0.9, 0.9, 0.9));
        AddMeshToList(car); // white
    }

    {
        Mesh* car = objectTema2::CreateCar(enemies[7], enemiesInitPoz[7], carLength, carWidth, carHeight, glm::vec3(0, 0.8, 0.8));
        AddMeshToList(car);  // cyan
    }

    {
        Mesh* grass = objectTema2::CreateGrass("grass", glm::vec3(-30, 0, -30), 60, 60, terrainComplexity,  glm::vec3(0.34, 0.69, 0.27), fillTerrain);
        AddMeshToList(grass);
    }

    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
    projectionMatrixMiniMap = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.0f, 300.0f);

    glm::ivec2 resolution = window->GetResolution();
    miniMap = ViewportArea(50, 50, (int)(resolution.x / 5.0f), (int)(resolution.y / 5.0f));

}

float Tema2::findAngle(glm::vec3 A, glm::vec3 B, glm::vec3 C) {
    float AB = sqrt((A.x - B.x) * (A.x - B.x) + (A.z - B.z) * (A.z - B.z));
    float AC = sqrt((A.x - C.x) * (A.x - C.x) + (A.z - C.z) * (A.z - C.z));
    float BC = sqrt((B.x - C.x) * (B.x - C.x) + (B.z - C.z) * (B.z - C.z));

    return 180.0f - (180.0f / (float)M_PI) * acos((AB * AB + BC * BC - AC * AC) / (2 * AB * BC));
}

bool Tema2::pointInTriangle(glm::vec2 P, glm::vec2 A, glm::vec2 B, glm::vec2 C) {
    glm::vec2 v0 = C - A;
    glm::vec2 v1 = B - A;
    glm::vec2 v2 = P - A;

    float dot00 = dot(v0, v0);
    float dot01 = dot(v0, v1);
    float dot02 = dot(v0, v2);
    float dot11 = dot(v1, v1);
    float dot12 = dot(v1, v2);

    float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    return (u >= 0) && (v >= 0) && (u + v < 1);
    
 }


bool Tema2::isInside(float tx, float tz) {
    glm::vec2 P = glm::vec2(tx + carInitPoz.x, tz + carInitPoz.z);
    for (int i = 0; i < 28; ++i) {
        glm::vec2 A = glm::vec2(interiorPoints[i].x, interiorPoints[i].z);
        glm::vec2 B = glm::vec2(interiorPoints[i + 1].x, interiorPoints[i + 1].z);
        glm::vec2 C = glm::vec2(exteriorPoints[i + 1].x, exteriorPoints[i + 1].z);
        glm::vec2 D = glm::vec2(exteriorPoints[i].x, exteriorPoints[i].z);
        if (pointInTriangle(P, A, B, C) || pointInTriangle(P, A, D, C)) {
            return true;
        }
    }
    glm::vec2 A = glm::vec2(interiorPoints[28].x, interiorPoints[28].z);
    glm::vec2 B = glm::vec2(interiorPoints[0].x, interiorPoints[0].z);
    glm::vec2 C = glm::vec2(exteriorPoints[0].x, exteriorPoints[0].z);
    glm::vec2 D = glm::vec2(exteriorPoints[28].x, exteriorPoints[28].z);
    if (pointInTriangle(P, A, B, C) || pointInTriangle(P, A, D, C)) {
        return true;
    }
    return false;
}

bool Tema2::hitsEnemy(float tx, float tz) {
    glm::vec2 P = glm::vec2(tx + carInitPoz.x, tz + carInitPoz.z);
    for (int i = 0; i < 8; ++i) {
        glm::vec2 M = glm::vec2(txEnemies[i] + enemiesInitPoz[i].x, tzEnemies[i] + enemiesInitPoz[i].z);
        if (distance(P, M) < carWidth * 2.5) {
            return true;

        }
    }
    return false;
}

void Tema2::moveEnemies(float deltaTimeSeconds, glm::mat4 projMatrix) {
     
    if (projMatrix != projectionMatrix) {
        for (int i = 0; i < 8; ++i) {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(txEnemies[i], 0, tzEnemies[i]));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(enemiesInitPoz[i].x, 0, enemiesInitPoz[i].z));
            modelMatrix = glm::rotate(modelMatrix, RADIANS(enemiesOyAng[i]), glm::vec3(0, 1, 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(miniMapScale * carsScaleFactor, miniMapScale * carsScaleFactor, miniMapScale * carsScaleFactor));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-enemiesInitPoz[i].x, 0, -enemiesInitPoz[i].z));
            RenderMesh(meshes[enemies[i]], shaders["VertexColor"], modelMatrix, projMatrix);
        }
        return;
    }
    for (int i = 0; i < 8; ++i) {
        int nextPos;
        float rotateAngle = 0;

        if (enemiesDirection[i] == 1) {
            if (enemiesPos[i] < 28) {
                nextPos = enemiesPos[i] + 1;
            }
            else {
                nextPos = 0;
            }
        }
        else {
            if (enemiesPos[i] > 0) {
                nextPos = enemiesPos[i] - 1;
            }
            else {
                nextPos = 28;
            }
        }
        glm::vec3 currentPos = glm::vec3(txEnemies[i] + enemiesInitPoz[i].x, 0, tzEnemies[i] + enemiesInitPoz[i].z);
        glm::vec3 pointToCompare;
        glm::vec3 startOfSegment;
        if (enemiesTrack[i] == 1) {
            pointToCompare = rightPoints[nextPos];
            startOfSegment = rightPoints[enemiesPos[i]];
        }
        else if (enemiesTrack[i] == 2) {
            pointToCompare = leftPoints[nextPos];
            startOfSegment = leftPoints[enemiesPos[i]];
        }
        else {
            pointToCompare = points[nextPos];
            startOfSegment = points[enemiesPos[i]];
        }
        if (abs(currentPos.x - pointToCompare.x) < 0.01 && abs(currentPos.z - pointToCompare.z) < 0.01) {
            rotateAngle = enemiesDirection[i] * angles[nextPos];
            enemiesPos[i] = nextPos;
            txEnemies[i] = pointToCompare.x - enemiesInitPoz[i].x;
            tzEnemies[i] = pointToCompare.z - enemiesInitPoz[i].z;
        }
        else {
            float deltaX = pointToCompare.x - startOfSegment.x;
            float deltaZ = pointToCompare.z - startOfSegment.z;
            glm::vec2 dir = glm::vec2(deltaX, deltaZ);
            dir = glm::normalize(dir);
            txEnemies[i] += dir.x * deltaTimeSeconds * enemySpeed;
            tzEnemies[i] += dir.y * deltaTimeSeconds * enemySpeed;
        }

        enemiesOyAng[i] += rotateAngle;
        enemiesOyAng[i] = enemiesOyAng[i] - (int)(enemiesOyAng[i] / 360) * 360;

        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(txEnemies[i], 0, tzEnemies[i]));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(enemiesInitPoz[i].x, 0, enemiesInitPoz[i].z));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(enemiesOyAng[i]), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-enemiesInitPoz[i].x, 0, -enemiesInitPoz[i].z));
        RenderMesh(meshes[enemies[i]], shaders["VertexColor"], modelMatrix, projMatrix);
    }
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

void Tema2::RenderScene(float deltaTimeSeconds, glm::mat4 projMatrix) {
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(txCar, 0, tzCar));
        modelMatrix = glm::translate(modelMatrix, carInitPoz);
        modelMatrix = glm::rotate(modelMatrix, RADIANS(angOyCar), glm::vec3(0, 1, 0));
        if (projectionMatrix != projMatrix) {
            modelMatrix = glm::scale(modelMatrix, glm::vec3(miniMapScale * carsScaleFactor, miniMapScale * carsScaleFactor, miniMapScale * carsScaleFactor));
        }
        modelMatrix = glm::translate(modelMatrix, -carInitPoz);
        RenderMesh(meshes["car"], shaders["VertexColor"], modelMatrix, projMatrix);
    }
    {
        moveEnemies(deltaTimeSeconds, projMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderMesh(meshes["grass"], shaders["VertexColor"], modelMatrix, projMatrix);
        RenderMesh(meshes["track"], shaders["VertexColor"], modelMatrix, projMatrix);
        RenderMesh(meshes["startLine"], shaders["VertexColor"], modelMatrix, projMatrix);
        //RenderMesh(meshes["trackOutline"], shaders["VertexColor"], modelMatrix, projMatrix);

        for (int i = 0; i < 29; ++i) {
            char trunk1[20], trunk2[20], leaves1[20], leaves2[20];
            sprintf(trunk1, "trunk%d", 2 * i);
            sprintf(trunk2, "trunk%d", 2 * i + 1);
            sprintf(leaves1, "leaves%d", 2 * i);
            sprintf(leaves2, "leaves%d", 2 * i + 1);
            RenderMesh(meshes[trunk1], shaders["VertexColor"], modelMatrix, projMatrix);
            RenderMesh(meshes[trunk2], shaders["VertexColor"], modelMatrix, projMatrix);
            RenderMesh(meshes[leaves1], shaders["VertexColor"], modelMatrix, projMatrix);
            RenderMesh(meshes[leaves2], shaders["VertexColor"], modelMatrix, projMatrix);
        }
    }
}

void Tema2::Update(float deltaTimeSeconds)
{   
    RenderScene(deltaTimeSeconds, projectionMatrix);

    glClear(GL_DEPTH_BUFFER_BIT);

    glViewport(miniMap.x, miniMap.y, miniMap.width, miniMap.height);
    RenderScene(deltaTimeSeconds, projectionMatrixMiniMap);
}


void Tema2::FrameEnd()
{
    //DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::mat4& projMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    if (projMatrix == projectionMatrix) {
        glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    }
    else {
        glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(cameraMiniMap->GetViewMatrix()));
    }
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods) {

    if (window->KeyHold(GLFW_KEY_Z) && miniMapScale < 3.1)
    {
        miniMapScale += 0.01f;
        orthoLeft = -16.0f * miniMapScale;
        orthoRight = -orthoLeft;
        orthoUp = 9.0f * miniMapScale;
        orthoDown = -orthoUp;
        projectionMatrixMiniMap = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.0f, 300.0f);
    }
    if (window->KeyHold(GLFW_KEY_X) && miniMapScale > 0.1)
    {
        miniMapScale -= 0.01f;
        orthoLeft = -16.0f * miniMapScale;
        orthoRight = -orthoLeft;
        orthoUp = 9.0f * miniMapScale;
        orthoDown = -orthoUp;
        projectionMatrixMiniMap = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.0f, 300.0f);
    }
    if (window->KeyHold(GLFW_KEY_C) && carsScaleFactor < 25) {
        carsScaleFactor += 0.1f;
    }
    if (window->KeyHold(GLFW_KEY_V) && carsScaleFactor > 2.5) {
        carsScaleFactor -= 0.1f;
    }

    float sensivity = 0.01f;
    float sensitivityKeyboard = 180.0f / (float)M_PI; // 1 radian 

    glm::vec3 posInit = camera->position;
    if (window->KeyHold(GLFW_KEY_S)) {
        if (!hitsEnemy(txCar, tzCar)) {
            if (!window->KeyHold(GLFW_KEY_W)) {
                // TODO(student): Translate the camera backward
                camera->MoveForward(-deltaTime * speed);
                glm::vec3 deltaPos = camera->position - posInit;
                txCar += deltaPos.x;
                tzCar += deltaPos.z;
                if (!isInside(txCar, tzCar)) {
                    txCar -= deltaPos.x;
                    tzCar -= deltaPos.z;
                    camera->MoveForward(deltaTime * speed);
                }
                else {
                    cameraMiniMap->Set(carInitPoz + glm::vec3(txCar, 1, 0.001 + tzCar), carInitPoz + glm::vec3(txCar, 0, tzCar), glm::vec3(0, 1, 0));
                    cameraMiniMap->RotateThirdPerson_OX(180 - 27.5f / (180 / (float)M_PI));
                }
                if (window->KeyHold(GLFW_KEY_A)) {
                    // TODO(student): Translate the camera to the left
                    camera->RotateThirdPerson_OX(-sensivity * turnSpeed);
                    angOyCar -= sensivity * turnSpeed * sensitivityKeyboard;
                    angOyCar = angOyCar - (int)(angOyCar / 360) * 360;

                }
                if (window->KeyHold(GLFW_KEY_D)) {
                    // TODO(student): Translate the camera to the right
                    camera->RotateThirdPerson_OX(sensivity * turnSpeed);
                    angOyCar += sensivity * turnSpeed * sensitivityKeyboard;
                    angOyCar = angOyCar - (int)(angOyCar / 360) * 360;
                }
            }
        }
    }
    else {
        if (!hitsEnemy(txCar, tzCar)) {
            if (window->KeyHold(GLFW_KEY_W)) {

                // TODO(student): Translate the camera forward
                camera->MoveForward(deltaTime * speed);
                glm::vec3 deltaPos = camera->position - posInit;
                txCar += deltaPos.x;
                tzCar += deltaPos.z;
                if (!isInside(txCar, tzCar)) {
                    txCar -= deltaPos.x;
                    tzCar -= deltaPos.z;
                    camera->MoveForward(-deltaTime * speed);
                }
                else {
                    cameraMiniMap->Set(carInitPoz + glm::vec3(txCar, 1, 0.001 + tzCar), carInitPoz + glm::vec3(txCar, 0, tzCar), glm::vec3(0, 1, 0));
                    cameraMiniMap->RotateThirdPerson_OX(180 - 27.5f / (180 / (float)M_PI));
                }
            }
            if (window->KeyHold(GLFW_KEY_A)) {
                // TODO(student): Translate the camera to the left
                camera->RotateThirdPerson_OX(sensivity * turnSpeed);
                angOyCar += sensivity * turnSpeed * sensitivityKeyboard;
                angOyCar = angOyCar - (int)(angOyCar / 360) * 360;
            }
            if (window->KeyHold(GLFW_KEY_D)) {
                // TODO(student): Translate the camera to the right
                camera->RotateThirdPerson_OX(-sensivity * turnSpeed);
                angOyCar -= sensivity * turnSpeed * sensitivityKeyboard;
                angOyCar = angOyCar - (int)(angOyCar / 360) * 360;
            }
        }
    }
}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
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
