#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    glClearColor(
      230.0f / 256.0f,
      162.0f / 256.0f,
      110.0f / 256.0f,
      1.0f);

  if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    glClearColor(
      126.0f / 256.0f,
      237.0f / 256.0f,
      148.0f / 256.0f,
      1.0f);

  if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    glClearColor(
      26.0f / 256.0f,
      44.0f / 256.0f,
      121.0f / 256.0f,
      1.0f);
  
  if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    glClearColor(
      100.0f / 256.0f,
      166.0f / 256.0f,
      234.0f / 256.0f,
      1.0f);

  if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    glClearColor(
      161.0f / 256.0f,
      99.0f / 256.0f,
      162.0f / 256.0f,
      1.0f);
}


int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow* window = glfwCreateWindow(800, 800, "Geneva Engine", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // default clear color
  glClearColor(
    230.0f / 256.0f,
    162.0f / 256.0f,
    110.0f / 256.0f,
    1.0f);

// render loop
  while (!glfwWindowShouldClose(window))
  {
    // input
    processInput(window);

    // rendering commands here
    glClear(GL_COLOR_BUFFER_BIT);

    // check and call events and swap the buffers
    glfwPollEvents();
    glfwSwapBuffers(window);
  }


  glfwTerminate();
  return 0;

}
