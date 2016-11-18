#ifndef GLHW_01_UTIL_H
#define GLHW_01_UTIL_H

#include <fstream>
#include <string>
#include <GL/glew.h>
#include <opencv2/opencv.hpp>
#include "glm/glm.hpp"
#include "const.h"

using namespace std;

struct Vertex {
    // Position
    glm::vec3 Position;
    // Normal
    glm::vec3 Normal;
    // TexCoords
    glm::vec2 TexCoords;
};

union UniformValue {
    UniformValue() {
        intVal = 0;
    }

    UniformValue(int i) {
        intVal = i;
    }

    UniformValue(GLuint i) {
        uintVal = i;
    }

    UniformValue(GLfloat i) {
        floatVal = i;
    }

    UniformValue(glm::vec3 i) {
        vec3Val = i;
    }

    UniformValue(glm::mat3 i) {
        mat3Val = i;
    }

    UniformValue(glm::mat4 i) {
        mat4Val = i;
    }

    GLint intVal;
    GLuint uintVal;
    GLfloat floatVal;
    glm::vec3 vec3Val;
    glm::mat3 mat3Val;
    glm::mat4 mat4Val;
};

const UniformValue intDef = {.intVal = 0};
const UniformValue uintDef = {.uintVal = 0};
const UniformValue floatDef = {.floatVal = 0};
const UniformValue vec3Def = {.vec3Val = glm::vec3()};
const UniformValue mat3Def = {.mat3Val = glm::mat3()};
const UniformValue mat4Def = {.mat4Val = glm::mat4()};

struct UniformData {
    UniformData() {
        type = UniformDataType::TYPE_DISABLED;
        name = "";
        location = 0;
        value = UniformValue();
    }

    UniformData(UniformDataType t, string n, GLuint l, UniformValue v) {
        type = t;
        name = n;
        location = l;
        value = v;
    }

    UniformDataType type;
    string name;
    GLuint location;
    UniformValue value;
};

struct LightData {
    LightData() {
        type = UniformData();
        color = UniformData();
        position = UniformData();
    }

    LightData(UniformData t, UniformData c, UniformData p) {
        type = t;
        color = c;
        position = p;
    }

    UniformData type;
    UniformData color;
    UniformData position;
};

string myReadFile(string name);

#endif