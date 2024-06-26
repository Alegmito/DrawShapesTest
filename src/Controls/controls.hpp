#pragma once
#include <glm/glm.hpp>

class GLFWwindow;

class MVPMatrix {
  glm::mat4 ViewMatrix = glm::mat4(0);
  glm::mat4 ProjectionMatrix;


  // Initial position : on +Z
  glm::vec3 position = glm::vec3(0, 0, 5);
  // Initial horizontal angle : toward -Z
  float horizontalAngle = 3.14f;
  // Initial vertical angle : none
  float verticalAngle = 0.0f;
  // Initial Field of View
  float initialFoV = 45.0f;

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