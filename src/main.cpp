#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ShaderProgram.h>
#include <Box.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

int screenWidth, screenHeight;

ShaderProgram shader;
Box box;

glm::vec3 lightPos = glm::vec3(0, 0, -1);

void draw(){
    shader.setProj(glm::perspective(glm::radians(45.0f), ((float) screenWidth) / screenHeight, 0.05f, 500.0f));
    shader.setView(glm::lookAt(glm::vec3(3, 3, 7), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));

    float lightLoc = 3.5 + 2 * sin(0.33 * glfwGetTime());
    
    glm::mat4 model;

    model = glm::mat4();
    //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0, 0, 1));
    shader.setModel(model);
    box.Draw(shader);

    model = glm::mat4();
    model = glm::translate(model, -2 * lightPos);
    shader.setModel(model);
    box.Draw(shader);
}

void init(){
    shader = ShaderProgram("shaders/standard.vert", "shaders/standard.frag");
    shader.use();

    shader.setLight(0, LightType::LIGHT_DIRECTION, lightPos, glm::vec3(0.7f, 0.7f, 0.7f));

    box = Box(1, 1, 1);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void windowSizeCallback(GLFWwindow *window, int w, int h) {
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glViewport(0, 0, screenWidth, screenHeight);
    //drawState.setScreenDims(w, h);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(800, 800, "PaperGraph", nullptr, nullptr);
    if (window == nullptr) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cout << "Failed to initialize GLEW" << endl;
        return -1;
    }

    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    windowSizeCallback(window, screenWidth, screenHeight);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetWindowSizeCallback(window, windowSizeCallback);

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    glClearDepth(1);
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

    init();

    int lastSecond = 0;
    int frames = 0;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        draw();
        glfwSwapBuffers(window);

        int time = (int) glfwGetTime();
        if (time > lastSecond) {
            lastSecond = time;
            frames = 0;
        }
        frames++;
    }

    glfwTerminate();

    return 0;
}