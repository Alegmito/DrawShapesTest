#include "Shapes.hpp"
#include <glm/gtc/constants.hpp>

void genBuffer(GLuint* bufferIndex, const void* buffer_data, GLsizeiptr bufferSize)
{
  glGenBuffers(1, bufferIndex);
  glBindBuffer(GL_ARRAY_BUFFER, *bufferIndex);
  glBufferData(GL_ARRAY_BUFFER, bufferSize, buffer_data, GL_STATIC_DRAW);
}

void bindBuffer(unsigned int vertex_attribute_index, GLuint& buffer_index)
{
  glEnableVertexAttribArray(vertex_attribute_index);
  glBindBuffer(GL_ARRAY_BUFFER, buffer_index);
  glVertexAttribPointer(
	vertex_attribute_index,                  // attribute. No particular reason for 0, but must match the layout in the shader.
	3,                  // size
	GL_FLOAT,           // type
	GL_FALSE,           // normalized?
	0,                  // stride
	(void*)0            // array buffer offset
  );
}

void Triangle::genBuffers()
{
  genBuffer(&vertexBuffer, g_vertex_buffer_data, sizeof(g_vertex_buffer_data));
  genBuffer(&colorBuffer, g_color_buffer_data, sizeof(g_color_buffer_data));
}

void Triangle::deleteBuffers()
{
  glDeleteBuffers(1, &vertexBuffer);
  glDeleteBuffers(1, &colorBuffer);
}

void Triangle::draw()
{
  bindBuffer(0, vertexBuffer);
  bindBuffer(1, colorBuffer);

  // Draw the triangle !
  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

void Box::genBuffers()
{
  genBuffer(&vertexBuffer, g_vertex_buffer_data, sizeof(g_vertex_buffer_data));

  genBuffer(&colorBuffer, g_color_buffer_data, sizeof(g_color_buffer_data));
}

void Box::deleteBuffers()
{
  glDeleteBuffers(1, &vertexBuffer);
  glDeleteBuffers(1, &colorBuffer);
}

void Box::draw()
{
  bindBuffer(0, vertexBuffer);
  bindBuffer(1, colorBuffer);

  glDrawArrays(GL_TRIANGLES, 0, 3*12);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

void RectangleSH::genBuffers()
{
  genBuffer(&vertexBuffer, g_vertex_buffer_data, sizeof(g_vertex_buffer_data));

  genBuffer(&colorBuffer, g_color_buffer_data, sizeof(g_color_buffer_data));
}

void RectangleSH::deleteBuffers()
{
  glDeleteBuffers(1, &vertexBuffer);
  glDeleteBuffers(1, &colorBuffer);
}

void RectangleSH::draw()
{
  bindBuffer(0, vertexBuffer);
  bindBuffer(1, colorBuffer);

  glDrawArrays(GL_TRIANGLES, 0, 3 * 12);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

Circle::Circle(size_t inSides)
  : sides(inSides >= 3 ? inSides : 3)
{
  float fraction = 2 * glm::pi<double>() / sides;

  for (int i = 0; i < sides; i++) {
	vertices.push_back(glm::vec3(
	  cos(i * fraction),
	  sin(i * fraction),
	  sin(i * fraction)));
	vertices.push_back(glm::vec3(0));
	vertices.push_back(glm::vec3(
	  cos((i + 1) * fraction),
	  sin((i + 1) * fraction),
	  sin((i + 1) * fraction)));
  };
}

void Circle::genBuffers()
{
  genBuffer(&vertexBuffer, vertices.data(), vertices.size() * sizeof(glm::vec3));
}

void Circle::deleteBuffers()
{
  glDeleteBuffers(1, &vertexBuffer);
}

void Circle::draw()
{
  bindBuffer(0, vertexBuffer);

  glDrawArrays(GL_TRIANGLES, 0, 3 * sides);

  glDisableVertexAttribArray(0);
}


