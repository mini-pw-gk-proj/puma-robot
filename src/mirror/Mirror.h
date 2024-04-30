//
// Created by Bartek Jadczak on 28/04/2024.
//

#ifndef PUMAROBOT_MIRROR_H
#define PUMAROBOT_MIRROR_H

#include "../Shader.h"
#include "../mesh/Mesh.h"
#include "../mesh/PositionNormalVertex.h"
#include "../importer/Model.h"

class Mirror
{
    std::unique_ptr<Mesh<PositionNormalVertex>> meshFront;
    std::unique_ptr<Mesh<PositionNormalVertex>> meshBack;

    static Model generateMirrorPlaneFront();
    static Model generateMirrorPlaneBack();

public:

    Mirror();

    void render(Shader &shader);
    void renderBack(Shader &shader);
    void renderFront(Shader &shader);
};


#endif //PUMAROBOT_MIRROR_H
