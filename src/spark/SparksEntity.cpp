//
// Created by faliszewskii on 07.05.24.
//

#include "SparksEntity.h"

void SparksEntity::update() {
    sparkGenerator.update();
    std::vector<SparkVertex> vertices(sparkGenerator.sparks.size());
    std::transform(sparkGenerator.sparks.begin(), sparkGenerator.sparks.end(), vertices.begin(),
                   [&](const auto &spark) {
        return SparkVertex{spark.prevPos, spark.currPos, glm::normalize(spark.velocity)};
    });
    mesh.update(std::move(vertices));
}

void SparksEntity::render(Shader &shader) {
    // TODO: Draw billboards.
    mesh.render();
}
