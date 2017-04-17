//
// Created by john on 10/12/16.
//

#include <glm/ext.hpp>
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const GLchar *vertexPath, const GLchar *fragmentPath) {
    string vertexCode = myReadFile(vertexPath);
    string fragmentCode = myReadFile(fragmentPath);

    GLint success;
    GLchar infoLog[512];
    const char *cstr;

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    cstr = vertexCode.c_str();
    glShaderSource(vertexShader, 1, &cstr, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED file:"
             << vertexPath << "\n" << infoLog << endl;
        cout << vertexCode << endl;
        exit(-1);
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    cstr = fragmentCode.c_str();
    glShaderSource(fragmentShader, 1, &cstr, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED file:"
             << vertexPath << "\n" << infoLog << endl;
        cout << fragmentCode << endl;
        exit(-1);
    }

    this->ProgramId = glCreateProgram();
    glAttachShader(this->ProgramId, vertexShader);
    glAttachShader(this->ProgramId, fragmentShader);
    glLinkProgram(this->ProgramId);

    glGetProgramiv(this->ProgramId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->ProgramId, 512, NULL, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED index:" << infoLog << endl;
        exit(-1);
    }

    initStructs();
}

void ShaderProgram::use() {
    glUseProgram(this->ProgramId);
    writeEverything();
}

void ShaderProgram::setLight(int lightIndex, LightType type, glm::vec3 position, glm::vec3 color) {
    if (lightIndex > MAX_NUM_LIGHTS) {
        return;
    }

    lights[lightIndex].type.value.intVal = type;
    lights[lightIndex].color.value.vec3Val = color;
    lights[lightIndex].position.value.vec3Val = position;

    updateValue(lights[lightIndex].type);
    updateValue(lights[lightIndex].color);
    updateValue(lights[lightIndex].position);
}

void ShaderProgram::setModel(glm::mat4 mat) {
    modelMat.value.mat4Val = mat;
    updateModelMat();
}

void ShaderProgram::setView(glm::mat4 mat) {
    viewMat.value.mat4Val = mat;
    updateValue(viewMat);
}

void ShaderProgram::setProj(glm::mat4 mat) {
    projectionMat.value.mat4Val = mat;
    updateValue(projectionMat);
}

void ShaderProgram::setViewPos(glm::vec3 pos) {
    viewPos.value.vec3Val = pos;
    updateValue(viewPos);
}

void ShaderProgram::initStructs() {
    for (int i = 0; i < MAX_NUM_LIGHTS; i++) {
        UniformData type = {
                UniformDataType::TYPE_INT,
                "lights[" + to_string(i) + "].type",
                -1,
                intDef
        };
        UniformData color = {
                TYPE_VEC3,
                "lights[" + to_string(i) + "].color",
                -1,
                vec3Def
        };
        UniformData position = {
                TYPE_VEC3,
                "lights[" + to_string(i) + "].position",
                -1,
                vec3Def
        };
        setLocation(type);
        setLocation(color);
        setLocation(position);
        lights[i].type = type;
        lights[i].color = color;
        lights[i].position = position;
    }

    setLocation(modelMat);
    setLocation(viewMat);
    setLocation(projectionMat);
    setLocation(normalModelMat);
    setLocation(viewPos);

    writeEverything();
}

void ShaderProgram::setLocation(UniformData &uniform) {
    uniform.location = glGetUniformLocation(ProgramId, uniform.name.c_str());
}

void ShaderProgram::updateValue(const UniformData &uniform) {
    if(uniform.location == -1){
        return;
    }

    switch (uniform.type) {
        case UniformDataType::TYPE_DISABLED:
            break;
        case UniformDataType::TYPE_INT:
            glUniform1i(uniform.location, uniform.value.intVal);
            break;
        case UniformDataType::TYPE_UINT:
            glUniform1ui(uniform.location, uniform.value.intVal);
            break;
        case UniformDataType::TYPE_FLOAT:
            glUniform1f(uniform.location, uniform.value.intVal);
            break;
        case UniformDataType::TYPE_VEC3:
            glUniform3fv(uniform.location, 1, glm::value_ptr(uniform.value.vec3Val));
            break;
        case UniformDataType::TYPE_MAT3:
            glUniformMatrix3fv(uniform.location, 1, GL_FALSE, glm::value_ptr(uniform.value.mat4Val));
            break;
        case UniformDataType::TYPE_MAT4:
            glUniformMatrix4fv(uniform.location, 1, GL_FALSE, glm::value_ptr(uniform.value.mat4Val));
            break;
        case UniformDataType::TYPE_TEXTURE:
            break;
        default:
            cout << "Unrecognized uniform type: " << uniform.type << endl;
            exit(-1);
    }
}

void ShaderProgram::writeLights() {
    for (int i = 0; i < MAX_NUM_LIGHTS; i++) {
        updateValue(lights[i].type);
        updateValue(lights[i].color);
        updateValue(lights[i].position);
    }
}

void ShaderProgram::writeEverything(){
    writeLights();
    updateModelMat();
    updateValue(viewMat);
    updateValue(projectionMat);
    updateValue(viewPos);
}

void ShaderProgram::updateModelMat() {
    normalModelMat.value.mat4Val = glm::mat3(glm::transpose(glm::inverse(modelMat.value.mat4Val)));
    updateValue(modelMat);
    updateValue(normalModelMat);
}