//
// Created by john on 10/12/16.
//

#ifndef GLHW_01_SHADER_H
#define GLHW_01_SHADER_H

#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include <string>
#include <algorithm>
#include "util.h"
#include "const.h"
#include "glm/glm.hpp"

using namespace std;

class ShaderProgram {
public:
    GLuint ProgramId;

    ShaderProgram() {}

    ShaderProgram(const GLchar *vertexPath, const GLchar *fragmentPath);

    void use();

    void setLight(int lightIndex, LightType type, glm::vec3 position, glm::vec3 color);

    void setModel(glm::mat4 mat);

    void setView(glm::mat4 mat);

    void setProj(glm::mat4 mat);

protected:
    void initStructs();

    void setLocation(UniformData &uniform);

    void updateValue(const UniformData &uniform);

    void writeLights();

    void writeEverything();

    void updateModelMat();

    UniformData modelMat = {UniformDataType::TYPE_MAT4, "modelMat", 0, mat4Def};
    UniformData normalModelMat = {UniformDataType::TYPE_MAT3, "normalModelMat", 0, mat3Def};
    UniformData viewMat = {UniformDataType::TYPE_MAT4, "viewMat", 0, mat4Def};
    UniformData projectionMat = {UniformDataType::TYPE_MAT4, "projectionMat", 0, mat4Def};

    UniformData ambientStrength = {UniformDataType::TYPE_FLOAT, "ambientStrength", 0, UniformValue(0.2f)};
    UniformData ambientColor = {UniformDataType::TYPE_VEC3, "ambientColor", 0, glm::vec3(1, 1, 1)};
    LightData lights[MAX_NUM_LIGHTS];
};

#endif //GLHW_01_SHADER_H
