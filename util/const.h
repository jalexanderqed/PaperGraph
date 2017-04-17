//
// Created by john on 11/16/16.
//

#ifndef PAPERGRAPH_CONST_H
#define PAPERGRAPH_CONST_H

#define POINT_LIGHT_PREFIX "pointLight_"
#define DIRECTION_LIGHT_PREFIX "directionLight_"
#define MAX_NUM_LIGHTS 4

enum LightType{
    LIGHT_DISABLED = 0,
    LIGHT_POINT = 1,
    LIGHT_DIRECTION = 2,
};

enum UniformDataType{
    TYPE_DISABLED = 0,
    TYPE_INT,
    TYPE_UINT,
    TYPE_FLOAT,
    TYPE_VEC3,
    TYPE_MAT3,
    TYPE_MAT4,
    TYPE_TEXTURE,
};

#endif //PAPERGRAPH_CONST_H