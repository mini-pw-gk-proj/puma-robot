//
// Created by Bartek Jadczak on 28/04/2024.
//

#ifndef PUMAROBOT_MIRROR_H
#define PUMAROBOT_MIRROR_H

#include "../Shader.h"
#include "../mesh/Mesh.h"
#include "../mesh/PositionNormalVertex.h"
#include "../importer/Model.h"
#include "../material/Material.h"

class Mirror
{
    std::unique_ptr<Mesh<PositionNormalVertex>> mesh;
    std::unique_ptr<Mesh<PositionNormalVertex>> meshVolume;

    Material material{{1,1,1,0.4},0.2,0.5};

    static Model generateMirrorPlane();

public:

    Mirror();

    void render(Shader &shader);
    void renderShadow(Shader &shader);

    static glm::mat4 getModel() ;
};


#endif //PUMAROBOT_MIRROR_H
