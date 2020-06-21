//
// Created by Alexander Winter on 2020-06-20.
//

#ifndef JELLO_RENDERABLE_H
#define JELLO_RENDERABLE_H

namespace jello {
    class Renderable;
}

class jello::Renderable {
public:
    virtual ~Renderable() = default;
    virtual void render() = 0;
};


#endif //JELLO_RENDERABLE_H
