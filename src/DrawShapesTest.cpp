// DrawShapesTest.cpp : Defines the entry point for the application.
//
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <Shapes.hpp>
#include <LoadShaders.hpp>
#include <controls.hpp>
#include <memory>

// Window dimensions
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

int main() {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }
  // Configure GLFW
  glfwWindowHint(GLFW_SAMPLES, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a windowed mode window and its OpenGL context
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "DrawShapes", NULL, NULL);
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
  // Enable depth test
  glEnable(GL_DEPTH_TEST);
  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);

  // Set viewport
  glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


  GLuint programID = LoadShaders("Shaders/SimpleVertex.vert", "Shaders/SimpleFragment.frag");

  
  // Get a handle for our "MVP" uniform
  GLuint MatrixID = glGetUniformLocation(programID, "MVP");


  auto mvpMatrix = std::shared_ptr<MVPMatrix>(new MVPMatrix());

  std::vector<Shape*> shapes = { new Triangle(), new Box(), new RectangleSH(), new Circle(6), new Circle(10)};
  for (auto& shape : shapes)
    shape->genBuffers();

  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  glfwSetCursorPos(window, 800 / 2.f, 600 / 2.f);

  // Render loop
  while (!glfwWindowShouldClose(window)) {
    // Per-frame time logic
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Rendering commands here
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(programID);
    // 1st attribute buffer : vertices

    mvpMatrix->computeMatricesFromInputs(window);
    auto model = glm::mat4(1.f);
    auto MVP = mvpMatrix->getProjectionMatrix() * mvpMatrix->getViewMatrix() * model;
    auto ViewProjMatrix = mvpMatrix->getProjectionMatrix() * mvpMatrix->getViewMatrix();

    float drawStartPos = -6.f;
    for (IDrawable* drawable : shapes)
    {
      model = glm::translate(glm::mat4(1.f), glm::vec3(drawStartPos, 0.f, 0.f));
      MVP = ViewProjMatrix * model;
      glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
      drawable->draw();
      drawStartPos += 3.f;
    }

    // Swap buffers and poll IO events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  for (auto shapeIt = shapes.begin(); shapeIt != shapes.end(); shapeIt++)
    (*shapeIt)->deleteBuffers();
  glDeleteVertexArrays(1, &VertexArrayID);
  glDeleteProgram(programID);

  glfwTerminate();
  return 0;
}