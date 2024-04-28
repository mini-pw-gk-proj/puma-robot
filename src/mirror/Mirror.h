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
    std::unique_ptr<Mesh<PositionNormalVertex>> mesh;
    std::unique_ptr<Mesh<PositionNormalVertex>> meshVolume;

    static Model generateMirrorPlane();

public:

    Mirror();

    void render(Shader &shader);
    void renderShadow(Shader &shader);

    static glm::mat4 getModel() ;
};


#endif //PUMAROBOT_MIRROR_H
