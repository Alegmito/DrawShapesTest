#pragma once
#include <glm/gtc/constants.hpp>
#include <glm/glm.hpp>

class GLFWwindow;

class MVPMatrix {
  glm::mat4 ViewMatrix;
  glm::mat4 ProjectionMatrix;


  // Initial position : on +Z
  glm::vec3 position = glm::vec3(0, 0, 5);
  // Initial horizontal angle : toward -Z
  float horizontalAngle = 3.14f;
  // Initial vertical angle : none
  float verticalAngle = 0;
  // Initial Field of View
  float initialFoV = 90.0f;

  float speed = 3.0f; // 3 units / second
  float mouseSpeed = 0.005f;

public:
  void computeMatricesFromInputs(GLFWwindow* window);

  glm::mat4 getViewMatrix() const {
	return ViewMatrix;
  }
  glm::mat4 getProjectionMatrix() const {
	return ProjectionMatrix;
  }
};