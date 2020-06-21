//
// Created by Alexander Winter on 2020-06-20.
//

#include "mesh/ElasticMesh.h"

int jello::ElasticMesh::getVertexCount() const
{
    return static_cast<int>(particles.size());
}

void jello::ElasticMesh::getVertices(float *arr) const
{
    for(const Particle& it : particles)
    {
        *arr++ = it.getPosition().x;
        *arr++ = it.getPosition().y;
        *arr++ = it.getPosition().z;
    }
}
