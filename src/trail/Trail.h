//
// Created by faliszewskii on 28.04.24.
//

#ifndef PUMAROBOT_TRAIL_H
#define PUMAROBOT_TRAIL_H


#include "../robot/Robot.h"
#include "../mesh/EmptyVertex.h"

class Trail {
    std::unique_ptr<Mesh<EmptyVertex>> mesh;

    Robot &robot;

    static constexpr int TRAIL_POINTS = 256;
    static constexpr int SKIP = 2;
    std::array<glm::vec3, TRAIL_POINTS> trailPoints{};
    int pointCount{};
    int caret{};
    int skip{};

public:
    explicit Trail(Robot &robot);

    void update(bool shouldReset);
    void render(Shader &shader);

    void reset();
};


#endif //PUMAROBOT_TRAIL_H
