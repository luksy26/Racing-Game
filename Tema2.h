#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/tema_camera.h"
#include "lab_m1/Tema2/objectTema2.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };
        Tema2();
        ~Tema2();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderScene(float deltaTimeSeconds, glm::mat4 projMatrix);
        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::mat4& projMatrix);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        bool isInside(float tx, float tz);
        bool pointInTriangle(glm::vec2 P, glm::vec2 A, glm::vec2 B, glm::vec2 C);
        float findAngle(glm::vec3 A, glm::vec3 B, glm::vec3 C);
        void moveEnemies(float deltaTimeSeconds, glm::mat4 projMatrix);
        bool hitsEnemy(float tx, float ty);

    protected:
        implemented::CameraTema* camera;
        implemented::CameraTema* cameraMiniMap;
        glm::mat4 projectionMatrix;
        glm::mat4 projectionMatrixMiniMap;

        // TODO(student): If you need any other class variables, define them here.

        float orthoLeft, orthoRight, orthoUp, orthoDown;
        float turnSpeed, speed, enemySpeed;
        float txCar, tzCar, angOyCar, txEnemies[10], tzEnemies[10];
        float carHeight, carLength, carWidth;
        int enemiesDirection[10];  // 0 for clockwise, 1 for anticlockwise
        int enemiesPos[10]; // index of point where the segment of track starts
        int enemiesTrack[10]; // 0 for center, 1 for right, 2 for left
        char enemies[10][20] = { "blueCar", "greenCar", "purpleCar", "yellowCar", "blackCar", "brownCar", "whiteCar", "cyanCar"};
        glm::vec3 exteriorPoints[30], interiorPoints[30];
        glm::vec3 points[30], leftPoints[30], rightPoints[30];
        float angles[30], enemiesOyAng[30];
        glm::vec3 carInitPoz, enemiesInitPoz[10];
        ViewportArea miniMap;
        float miniMapScale, carsScaleFactor, scaleOnScreen;
        bool fillTerrain;
        int terrainComplexity;
    };
}   // namespace m1
