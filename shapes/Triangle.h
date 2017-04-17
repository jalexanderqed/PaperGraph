//
// Created by john on 11/23/16.
//

#ifndef PAPERGRAPH_TRIANGLE_H
#define PAPERGRAPH_TRIANGLE_H


#include "Shape.h"

class Triangle : public Shape {
public:
    Triangle(){}
    Triangle(bool b);
    void Draw(ShaderProgram& p);
};


#endif //PAPERGRAPH_TRIANGLE_H
