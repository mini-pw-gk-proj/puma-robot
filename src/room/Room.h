//
// Created by Bartek Jadczak on 27/04/2024.
//

#ifndef PUMAROBOT_ROOM_H
#define PUMAROBOT_ROOM_H

#include "../Shader.h"
#include "../mesh/Mesh.h"
#include "../mesh/PositionNormalVertex.h"
#include "../importer/Model.h"

class Room
{
    std::unique_ptr<Mesh<PositionNormalVertex>> standMesh;

    static Model generateRoom(float width, float height, float depth);

public:

    Room();

    void render(Shader &shader);

};


#endif //PUMAROBOT_ROOM_H
