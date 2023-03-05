#include "objectTema2.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* objectTema2::CreateGrass(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float width,
    int complexity,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    glm::vec3 corners[4];
    corners[0] = corner + glm::vec3(0, 0, 0);
    corners[1] = corner + glm::vec3(length, 0, 0);
    corners[2] = corner + glm::vec3(length, 0, width);
    corners[3] = corner + glm::vec3(0, 0, width);

    std::vector<VertexFormat> vertices;

    float deltaX_exterior = corners[1].x - corners[0].x;
    float deltaZ_exterior = corners[1].z - corners[0].z;
    float deltaX_interior = corners[2].x - corners[3].x;
    float deltaZ_interior = corners[3].z - corners[3].z;
    for (float k = 0; k <= 1; k += 1.0f / complexity) {
        vertices.push_back(VertexFormat(corners[0] + glm::vec3(k * deltaX_interior, -0.001, k * deltaZ_interior), color));
        vertices.push_back(VertexFormat(corners[3] + glm::vec3(k * deltaX_exterior, -0.001, k * deltaZ_exterior), color));
    }
    vertices.push_back(VertexFormat(corner + glm::vec3(length / 2, 0, width / 2), color));

    Mesh* grass = new Mesh(name);
    std::vector<unsigned int> indices;


    for (int i = 0; i < 2 * complexity; i += 2) {
        indices.push_back(i);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
        indices.push_back(i);
        indices.push_back(i + 3);
        indices.push_back(i + 1);
        indices.push_back(i);
        indices.push_back(i + 2);
        indices.push_back(i + 3);
    }
    indices.push_back(2 * complexity);
    indices.push_back(0);


    if (!fill) {
        grass->SetDrawMode(GL_LINE_LOOP);
    }

    grass->InitFromData(vertices, indices);
    return grass;
}

Mesh* objectTema2::CreateTrunk(
    const std::string& name,
    glm::vec3 rootCenter,
    float height,
    float size,
    glm::vec3 color)
{
    glm::vec3 center = rootCenter;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(-size * 0.75, 0, -size * 0.75), color),
        VertexFormat(center + glm::vec3(size * 0.75, 0, -size * 0.75), color),
        VertexFormat(center + glm::vec3(size * 0.75, 0, size * 0.75), color),
        VertexFormat(center + glm::vec3(-size * 0.75, 0, size * 0.75), color),
        VertexFormat(center + glm::vec3(-size * 0.75, height, -size * 0.75), color),
        VertexFormat(center + glm::vec3(size * 0.75, height, -size * 0.75), color),
        VertexFormat(center + glm::vec3(size * 0.75, height, size * 0.75), color),
        VertexFormat(center + glm::vec3(-size * 0.75, height, size * 0.75), color),
    };

    Mesh* tree = new Mesh(name);
    std::vector<unsigned int> indices = {0, 1, 2, 0, 3, 2, 0, 1, 5, 0, 4, 5, 0, 3, 7, 0, 4, 7, 0, 2, 6, 5, 4, 6, 7, 4, 6, 2, 3, 6, 7, 3, 6, 2, 1, 6, 5, 1, 6};

    tree->InitFromData(vertices, indices);
    return tree;
}

Mesh* objectTema2::CreateLeaves(
    const std::string& name,
    glm::vec3 rootCenter,
    float height,
    float size,
    glm::vec3 color)
{
    glm::vec3 center = rootCenter;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(0, 0.01, 0) + glm::vec3(-2.5 * size, height, -2.5 * size), color),
        VertexFormat(center + glm::vec3(0, 0.01, 0) + glm::vec3(2.5 * size, height, -2.5 * size), color),
        VertexFormat(center + glm::vec3(0, 0.01, 0) + glm::vec3(2.5 * size, height, 2.5 * size), color),
        VertexFormat(center + glm::vec3(0, 0.01, 0) + glm::vec3(-2.5 * size, height, 2.5 * size), color),
        VertexFormat(center + glm::vec3(0, 0.01, 0) + glm::vec3(-2.5 * size, 2.75 * height, -2.5 * size), color),
        VertexFormat(center + glm::vec3(0, 0.01, 0) + glm::vec3(2.5 * size, 2.75 * height, -2.5 * size), color),
        VertexFormat(center + glm::vec3(0, 0.01, 0) + glm::vec3(2.5 * size, 2.75 * height, 2.5 * size), color),
        VertexFormat(center + glm::vec3(0, 0.01, 0) + glm::vec3(-2.5 * size, 2.75 * height, 2.5 * size), color),
    };

    Mesh* leaves = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 0, 3, 2, 0, 1, 5, 0, 4, 5, 0, 3, 7, 0, 4, 7, 0, 2, 6, 5, 4, 6, 7, 4, 6, 2, 3, 6, 7, 3, 6, 2, 1, 6, 5, 1, 6 };

    leaves->InitFromData(vertices, indices);
    return leaves;
}

Mesh* objectTema2::CreateCar(
    const std::string& name,
    glm::vec3 center,
    float length,
    float width,
    float height,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(-width , -height, -length), color),
        VertexFormat(center + glm::vec3(width, -height, -length), color),
        VertexFormat(center + glm::vec3(width, -height, length), color),
        VertexFormat(center + glm::vec3(-width, -height, length), color),
        VertexFormat(center + glm::vec3(-width , height, -length), color),
        VertexFormat(center + glm::vec3(width, height, -length), color),
        VertexFormat(center + glm::vec3(width, height, length), color),
        VertexFormat(center + glm::vec3(-width, height, length), color),
    };
    Mesh* car = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 0, 3, 2, 0, 1, 5, 0, 4, 5, 0, 3, 7, 0, 4, 7, 0, 2, 6, 5, 4, 6, 7, 4, 6, 2, 3, 6, 7, 3, 6, 2, 1, 6, 5, 1, 6 };

    car->InitFromData(vertices, indices);
    return car;
}

Mesh* objectTema2::CreateTrack(
    const std::string& name,
    glm::vec3 *points,
    int nr,
    int complexity,
    glm::vec3 color,
    bool fill)
{

    glm::vec3 exteriors[30], interiors[30];

    for (int i = 0; i < nr - 1; ++i) {
        exteriors[i] = points[i] + 0.15f * cross(points[i + 1] - points[i], glm::vec3(0, 1, 0));
        interiors[i] = points[i] - 0.15f * cross(points[i + 1] - points[i], glm::vec3(0, 1, 0));
    }
    exteriors[nr - 1] = points[nr - 1] + 0.15f * cross(points[0] - points[nr - 1], glm::vec3(0, 1, 0));
    interiors[nr - 1] = points[nr - 1] - 0.15f * cross(points[0] - points[nr - 1], glm::vec3(0, 1, 0));
    exteriors[nr] = exteriors[0];
    interiors[nr] = interiors[0];

    std::vector<VertexFormat> vertices;
    
    for (int i = 0; i < nr; ++i) {
        float deltaX_exterior = exteriors[i + 1].x - exteriors[i].x;
        float deltaZ_exterior = exteriors[i + 1].z - exteriors[i].z;
        float deltaX_interior = interiors[i + 1].x - interiors[i].x;
        float deltaZ_interior = interiors[i + 1].z - interiors[i].z;
        vertices.push_back(VertexFormat(interiors[i], color));
        vertices.push_back(VertexFormat(exteriors[i], color));
        for (float k = 0; k < 1; k += 1.0f / complexity) {
            vertices.push_back(VertexFormat(interiors[i] + glm::vec3(k * deltaX_interior, 0, k * deltaZ_interior), color));
            vertices.push_back(VertexFormat(exteriors[i] + glm::vec3(k * deltaX_exterior, 0, k * deltaZ_exterior), color));
        }
    }
    nr *= complexity + 1;
    Mesh* track = new Mesh(name);
    if (!fill) {
        track->SetDrawMode(GL_LINE_LOOP);
    }
    std::vector<unsigned int> indices;
    for (int i = 0; i < 2 * (nr - 1); i += 2) {
        indices.push_back(i);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
        indices.push_back(i);
        indices.push_back(i + 3);
        indices.push_back(i + 1);
        indices.push_back(i);
        indices.push_back(i + 2);
        indices.push_back(i + 3);
    }
    indices.push_back(2 * (nr - 1));
    indices.push_back(2 * (nr - 1) + 1);
    indices.push_back(0);
    indices.push_back(2 * (nr - 1));
    indices.push_back(1);
    indices.push_back(2 * (nr - 1) + 1);
    indices.push_back(2 * (nr - 1));
    indices.push_back(0);
    indices.push_back(1);

    track->InitFromData(vertices, indices);
    return track;
}

Mesh* objectTema2::TrackOutline(
    const std::string& name,
    glm::vec3* points,
    int nr,
    glm::vec3 color)
{

    std::vector<VertexFormat> vertices;

    for (int i = 0; i < nr; ++i) {
        vertices.push_back(VertexFormat(points[i] + glm::vec3(0, 0.001, 0), color));
    }
    Mesh* track = new Mesh(name);
    track->SetDrawMode(GL_LINE_LOOP);

    std::vector<unsigned int> indices;
    for (int i = 0; i < nr; ++i) {
        indices.push_back(i);
    }
    indices.push_back(0);

    track->InitFromData(vertices, indices);
    return track;
}

Mesh* objectTema2::StartLine(
    const std::string& name,
    glm::vec3 p1,
    glm::vec3 p2,
    glm::vec3 p3,
    glm::vec3 p4,
    glm::vec3 color
)
{
    std::vector<VertexFormat> vertices;

    glm::vec3 p5 = glm::vec3(0, 0.0011, 0) + glm::vec3((p2.x - p1.x) / 10 + p1.x, 0, (p2.z - p1.z) / 10 + p1.z);
    glm::vec3 p6 = glm::vec3(0, 0.0011, 0) + glm::vec3((p2.x - p1.x) / 7 + p1.x, 0, (p2.z - p1.z) / 7 + p1.z);
    glm::vec3 p7 = glm::vec3(0, 0.0011, 0) + glm::vec3((p3.x - p4.x) / 10 + p4.x, 0, (p3.z - p4.z) / 10 + p4.z);
    glm::vec3 p8 = glm::vec3(0, 0.0011, 0) + glm::vec3((p3.x - p4.x) / 7 + p4.x, 0, (p3.z - p4.z) / 7 + p4.z);

    vertices.push_back(VertexFormat(p5, color));
    vertices.push_back(VertexFormat(p6, color));
    vertices.push_back(VertexFormat(p7, color));
    vertices.push_back(VertexFormat(p8, color));

    Mesh* startLine = new Mesh(name);
    std::vector<unsigned int> indices = {0, 1, 2, 2, 1, 3};

    startLine->InitFromData(vertices, indices);
    return startLine;
}