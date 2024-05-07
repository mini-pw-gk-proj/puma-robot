//
// Created by faliszewskii on 18.04.24.
//

#ifndef PUMAROBOT_ROBOT_H
#define PUMAROBOT_ROBOT_H


#include "../Shader.h"
#include "../mesh/Mesh.h"
#include "../mesh/PositionNormalVertex.h"
#include "../importer/Model.h"
#include "RobotKinematics.h"
#include "../material/Material.h"
#include "../mesh/PosNorTexVertex.h"

class Robot {
    std::unique_ptr<Mesh<PosNorTexVertex>> standMesh;
    std::vector<Mesh<PosNorTexVertex>> armMeshes;

    std::unique_ptr<Mesh<PosNorTexVertex>> standMeshVolume;
    std::vector<Mesh<PosNorTexVertex>> armMeshesVolume;

    Material material{{0.15,0.15,0.3,1},0.5,1};
public:
    bool onFire;
    RobotKinematics kinematics;

    Robot(Model<PosNorTexVertex>& standModel, std::vector<Model<PosNorTexVertex>>& armModels);

    void update(float timeS);
    void render(Shader &shader);

    void renderShadow(Shader &shader);
};


#endif //PUMAROBOT_ROBOT_H
