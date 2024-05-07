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
#include "../mesh/PosNorTexVertex.h"
#include "../texture/Texture.h"

class Mirror
{
    std::unique_ptr<Mesh<PosNorTexVertex>> meshFront;
    std::unique_ptr<Mesh<PosNorTexVertex>> meshBack;
    std::unique_ptr<Mesh<PosNorTexVertex>> meshVolume;

    Texture texture{"../res/textures/dirt.png"};

    Material material{{0.25*113/256.f, 0.25*121/256.f, 0.5*166/256.f,1},0.2,0.5};
    Material transparentMaterial{{113/256.f, 121/256.f, 126/256.f, 0.6},0.2,0.5};

    static Model<PosNorTexVertex> generateMirrorPlane();
    static Model<PosNorTexVertex> generateMirrorPlaneFront();
    static Model<PosNorTexVertex> generateMirrorPlaneBack();

public:

    Mirror();

    void render(Shader &shader);
    void renderShadow(Shader &shader);
    void renderBack(Shader &shader);
    void renderFront(Shader &shader);

    static glm::mat4 getModel() ;
};


#endif //PUMAROBOT_MIRROR_H
