//
// Created by faliszewskii on 07.05.24.
//

#include "SparksEntity.h"

void SparksEntity::update() {
    sparkGenerator.update();
    // TODO: Convert sparks to a TVertex type and update mesh.
    // A novel one. PosTanVertex maybe as we need position and the velocity vectors.
}

void SparksEntity::render() {
    // TODO: Draw billboards.
}
