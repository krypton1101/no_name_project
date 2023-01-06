#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"

GLfloat points[] = {
    0.0f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
};

GLfloat colors[] = {
    0.0f, 1.0f, 0.5f,
    0.0f, 0.5f, 0.5f,
    0.0f, 0.5f, 1.0f
};

int glWindowSizeX = 1280;
int glWindowSizeY = 920;

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    glWindowSizeX = width;
    glWindowSizeY = height;
    glViewport(0, 0, glWindowSizeX, glWindowSizeY); // update drawing space
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

int main(int argc, char** argv)
{
    GLFWwindow* pWindow;

    /* Initialize the library */
    if (!glfwInit())
    {
        std::cerr << "glfwInit failed!" << std::endl;
        return -1;
    }

    /* Setting OpenGL version to use */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    pWindow = glfwCreateWindow(glWindowSizeX, glWindowSizeY, "No Name Project", nullptr, nullptr);
    if (!pWindow)
    {
        glfwTerminate();
        std::cerr << "glfwCreateWindow failed!" << std::endl;
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    /* Set function that will be called on window size changing and on key events */
    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    /* GLAD initializing */
    if(!gladLoadGL())
    {
        std::cerr << "gladLoadGL failed!" << std::endl;
        return -1;
    }

    /* GL version print */
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(0, 1, 1, 1); // Color to clear window
    
    { // limit the scope of visibility
        ResourceManager resourceManager(argv[0]);
        auto pDefaultShaderProgram = resourceManager.loadShaders("DefaultShader",
            "resources/shaders/Vertex.txt", "resources/shaders/Fragment.txt");
        if(!pDefaultShaderProgram)
        {
            std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
            return -1;
        }

        GLuint points_vertexbufferobject = 0;
        glGenBuffers(1, &points_vertexbufferobject);
        glBindBuffer(GL_ARRAY_BUFFER, points_vertexbufferobject);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

        GLuint colors_vertexbufferobject = 0;
        glGenBuffers(1, &colors_vertexbufferobject);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vertexbufferobject);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint VertexArrayObject = 0;
        glGenVertexArrays(1, &VertexArrayObject);
        glBindVertexArray(VertexArrayObject);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vertexbufferobject);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vertexbufferobject);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(pWindow))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            pDefaultShaderProgram->use();
            glBindVertexArray(VertexArrayObject);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            /* Swap front and back buffers */
            glfwSwapBuffers(pWindow);

            /* Poll for and process events */
            glfwPollEvents();
        }
    } // limit the scope of visibility

    glfwTerminate();
    return 0;
}