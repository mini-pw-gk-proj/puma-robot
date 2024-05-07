//
// Created by faliszewskii on 07.05.24.
//

#include "SparksEntity.h"

void SparksEntity::update(bool generate) {
    sparkGenerator.update(generate);
    std::vector<SparkVertex> vertices(sparkGenerator.sparks.size());
    std::transform(sparkGenerator.sparks.begin(), sparkGenerator.sparks.end(), vertices.begin(),
                   [&](const auto &spark) {
        return SparkVertex{spark.prevPos, spark.currPos, glm::normalize(spark.velocity), spark.ttl};
    });
    mesh.update(std::move(vertices));
}

void SparksEntity::render(Shader &shader) {
    shader.setUniform("maxTTL", SparkGenerator::MAX_TTL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    texture.bind(0);
    mesh.render();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
