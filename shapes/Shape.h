//
// Created by john on 11/23/16.
//

#ifndef PAPERGRAPH_SHAPE_H
#define PAPERGRAPH_SHAPE_H


#include <ShaderProgram.h>

class Shape {
public:
    virtual void Draw(ShaderProgram& p) = 0;
};


#endif //PAPERGRAPH_SHAPE_H
