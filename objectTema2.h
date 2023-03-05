#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace objectTema2
{
    Mesh* CreateGrass(const std::string& name, glm::vec3 leftBottomCorner, float length, float width, int complexity, glm::vec3 color, bool fill = false);
    Mesh* CreateTrunk(const std::string& name, glm::vec3 rootCenter, float height, float size, glm::vec3 color);
    Mesh* CreateLeaves(const std::string& name, glm::vec3 rootCenter, float height, float size, glm::vec3 color);
    Mesh* CreateTrack(const std::string& name, glm::vec3 *points, int nr, int complexity, glm::vec3 color, bool fill);
    Mesh* CreateCar(const std::string& name, glm::vec3 center, float length, float width, float height, glm::vec3 color);
    Mesh* TrackOutline(const std::string& name, glm::vec3* points, int nr, glm::vec3 color);
    Mesh* StartLine(const std::string& name, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, glm::vec3 color);
}