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

class Robot {
    std::unique_ptr<Mesh<PositionNormalVertex>> standMesh;
    std::vector<Mesh<PositionNormalVertex>> armMeshes;

    std::unique_ptr<Mesh<PositionNormalVertex>> standMeshVolume;
    std::vector<Mesh<PositionNormalVertex>> armMeshesVolume;

    Material material{{0.9,0.85,1,1},0.7,0.9};
public:
    bool onFire;
    RobotKinematics kinematics;

    Robot(Model& standModel, std::vector<Model>& armModels);

    void update(float timeS);
    void render(Shader &shader);

    void renderShadow(Shader &shader);
};


#endif //PUMAROBOT_ROBOT_H
