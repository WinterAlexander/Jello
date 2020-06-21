//
// Created by Alexander Winter on 2020-06-20.
//

#ifndef JELLO_ELASTICMESH_H
#define JELLO_ELASTICMESH_H

#include <vertex/Vertex.h>
#include <vector>
#include <vertex/Particle.h>
#include "Mesh.h"

namespace jello {
    class ElasticMesh;
}

class jello::ElasticMesh : public jello::Mesh {
    std::vector<jello::Particle> particles;

public:
    int getVertexCount() const override;

    void getVertices(float* arr) const override;
};


#endif //JELLO_ELASTICMESH_H
