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
    std::unique_ptr<Mesh<PositionNormalVertex>> meshFront;
    std::unique_ptr<Mesh<PositionNormalVertex>> meshBack;
    std::unique_ptr<Mesh<PositionNormalVertex>> meshVolume;

    Material material{{113/256.f, 121/256.f, 126/256.f,1},0.2,0.5};
    Material transparentMaterial{{113/256.f, 121/256.f, 126/256.f, 0.6},0.2,0.5};

    static Model generateMirrorPlane();
    static Model generateMirrorPlaneFront();
    static Model generateMirrorPlaneBack();

public:

    Mirror();

    void render(Shader &shader);
    void renderShadow(Shader &shader);
    void renderBack(Shader &shader);
    void renderFront(Shader &shader);

    static glm::mat4 getModel() ;
};


#endif //PUMAROBOT_MIRROR_H
