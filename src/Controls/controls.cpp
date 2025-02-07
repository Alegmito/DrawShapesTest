#include <GLFW/glfw3.h>
#include "controls.hpp"
#include <glm/gtc/matrix_transform.hpp>

void MVPMatrix::computeMatricesFromInputs(GLFWwindow* window)
{

  // glfwGetTime is called only once, the first time this function is called
  static double lastTime = glfwGetTime();

  // Compute time difference between current and last frame
  double currentTime = glfwGetTime();
  float deltaTime = float(currentTime - lastTime);

  // Get mouse position
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);

  // Reset mouse position for next frame
  glfwSetCursorPos(window, 800 / 2.f, 600 / 2.f);

  // Compute new orientation
  horizontalAngle += mouseSpeed * float(800 / 2.f - xpos);
  verticalAngle += (mouseSpeed * float(600 / 2.f - ypos));
  verticalAngle = abs(verticalAngle) >= glm::half_pi<double>() ? glm::sign(verticalAngle) * glm::half_pi<double>() : verticalAngle;

  // Direction : Spherical coordinates to Cartesian coordinates conversion
  glm::vec3 direction(
	cos(verticalAngle) * sin(horizontalAngle),
	sin(verticalAngle),
	cos(verticalAngle) * cos(horizontalAngle)
  );

  // Right vector
  glm::vec3 right = glm::vec3(
	sin(horizontalAngle - 3.14f / 2.0f),
	0,
	cos(horizontalAngle - 3.14f / 2.0f)
  );

  // Up vector
  glm::vec3 up = glm::cross(right, direction);

  // Move forward
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
	position += direction * deltaTime * speed;
  }
  // Move backward
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
	position -= direction * deltaTime * speed;
  }
  // Strafe right
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
	position += right * deltaTime * speed;
  }
  // Strafe left
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
	position -= right * deltaTime * speed;
  }

  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
	position += up * deltaTime * speed;
  }

  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
	position -= up * deltaTime * speed;
  }


  printf("up vector is : %f, %f, %f\n", up.x, up.y, up.z);

  float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

  // Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
  ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
  // Camera matrix
  ViewMatrix = glm::lookAt(
	position,           // Camera is here
	position + glm::normalize(direction), // and looks here : at the same position, plus "direction"
	up                  // Head is up (set to 0,-1,0 to look upside-down)
  );

  // For the next frame, the "last time" will be "now"
  lastTime = currentTime;
}
