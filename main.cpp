#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "shader.h"
#include <iostream>
#include <cmath>

const uint SCR_WIDTH = 960;
const uint SCR_HEIGHT = 720;

/*
void framebuffer_size_callback(GLFWwindow* window,int width, int height)
{
  glViewport(0,0,width, height);
}
*/
void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window,true);
  }
}

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OPENGL", NULL, NULL);

  if (window == NULL)
  {
    std::cout << "Failed to create window/n";
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD/n";
      return -1;
  }

Shader colorfulShader("vertexSH.vs" , "fragSH.fs");

float vertices[] = {
   0.50f, -0.50f, 0.0f, 1.0f, 0.0f, 0.0f,
  -0.50f, -0.50f, 0.0f, 0.0f, 1.0f, 0.0f,
   0.0f, 0.50f, 0.0f  , 0.0f, 0.0f, 1.0f,
};

uint VBO, VAO;

//The VAO is a container that stores the configuration of vertex attributes and their associated buffer objects (VBOs).
glGenVertexArrays(1, &VAO);
glBindVertexArray(VAO);
//glGenBuffers does not allocate memory or initialize the buffer; it just generates an ID.
//Generate the vertex buffer
glGenBuffers(1, &VBO);
//Bind the newly created buffer to the GL_ARRAY_BUFFER, the buffer type of a vertex buffer object
glBindBuffer(GL_ARRAY_BUFFER, VBO);

//copy the defined data into the bounded buffer
//first argument: type of buffer to copy data into. second:the size of the data to pass to buffer
//third: the data we want to send. fourth: how we want the graphics card to manage the given data
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//glVertexAttribPointer configures how vertex data is read from the buffer.
//0 = This attribute corresponds to layout(location = 0) in the vertex shader.
//3 = The attribute has 3 components (e.g., x, y, z for position).
//GL_FLOAT = Each component is a float.
//GL_FALSE = The data is not normalized.
//6 * = byte offset between consecutive vertices (each vertex is 24 bytes apart),
//3 * = The attribute starts after the first 3 floats (12 bytes) in each vertex.
//Position
glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

//Color
glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);

//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  while (!glfwWindowShouldClose(window))
  {
    //input
    processInput(window);

    //clear the screen
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //draw the triangle
    colorfulShader.use();
    //color changing
    double timeValue = glfwGetTime() * 2;
    float redValue = static_cast<float>(sin(timeValue) / 3.0);
    float greenValue = static_cast<float>(sin(timeValue + 2) / 3.0);
    float blueValue = static_cast<float>(sin(timeValue + 4) / 3.0);
    int vertexColorLocation = glGetUniformLocation(colorfulShader.ID, "uniColor");
    glUniform4f(vertexColorLocation, redValue / 3, greenValue / 3, blueValue / 3, 1.0f);

    //position changing
    double posTime = glfwGetTime();
    float xPos = sin(posTime);
    int vertexPosLocation = glGetUniformLocation(colorfulShader.ID, "uniPos");
    glUniform4f(vertexPosLocation, xPos / 2, 0.0f, 0.0f, 1.0);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
 }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glfwTerminate();
  return 0;
}
