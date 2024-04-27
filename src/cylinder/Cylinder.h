//
// Created by Bartek Jadczak on 27/04/2024.
//

#ifndef PUMAROBOT_CYLINDER_H
#define PUMAROBOT_CYLINDER_H

#include "../Shader.h"
#include "../mesh/Mesh.h"
#include "../mesh/PositionNormalVertex.h"
#include "../importer/Model.h"

class Cylinder
{
    std::unique_ptr<Mesh<PositionNormalVertex>> mesh;

    static Model generateCylinder(float radius, float height, int slices);

    float x, y, z;

public:

    Cylinder();

    void render(Shader &shader);
};


#endif //PUMAROBOT_CYLINDER_H
