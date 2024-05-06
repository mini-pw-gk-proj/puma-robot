//
// Created by Bartek Jadczak on 27/04/2024.
//

#ifndef PUMAROBOT_ROOM_H
#define PUMAROBOT_ROOM_H

#include "../Shader.h"
#include "../mesh/Mesh.h"
#include "../mesh/PositionNormalVertex.h"
#include "../importer/Model.h"
#include "../material/Material.h"
#include "../mesh/PosNorTexVertex.h"
#include "../texture/Texture.h"

class Room
{
    std::unique_ptr<Mesh<PosNorTexVertex>> wallsMesh;
    Texture transparentWallTexture{"../res/textures/wall.png"};
    Texture wallTexture{"../res/textures/wall2.png"};
    std::unique_ptr<Mesh<PosNorTexVertex>> floorMesh;
    Texture floorTexture{"../res/textures/floor.png"};
    std::unique_ptr<Mesh<PosNorTexVertex>> ceilingMesh;
    Texture ceilingTexture{"../res/textures/concrete.jpg"};

    Material material{{1,1,1,1},0.0,0};

    void generateRoom(float width, float height, float depth);

public:
    bool isTransparent = false;

    Room();

    void render(Shader &shader);

};


#endif //PUMAROBOT_ROOM_H
