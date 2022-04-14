#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int WIDTH = 720;
int HEIGHT = 720;

const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
    "}\n\0";

int main()
{
    // initialize glfw and tell it what version of openGL we're using
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Puzzle-Game", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Couldn't create window.\n";
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    // load glad
    gladLoadGL();

    // define viewport
    glViewport(0, 0, WIDTH, HEIGHT);

    // initialize shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // initialize shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // delete shaders as they are already part of the shader program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // vertices
    GLfloat vertices[] =
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower left
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower right
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // upper
        -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // inner left
        0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // inner right
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // inner down
    };

    GLuint indices[] =
    {
        0, 3, 5, // lower left triangle
        3, 2, 4, // upper triangle
        5, 4, 1 // lower right triangle
    };

    // make object
    // always make VAO before VBO
    GLuint VAO, VBO, EBO; // normally an array - we only have 1 object

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); // 1 = 1 object
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // STREAM/STATIC/DYNAMIC, DRAW/READ/COPY
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 0 = index
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
    // change color
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    // main loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        // process events
        glfwPollEvents();
    }

    // delete objects
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // terminate window
    glfwDestroyWindow(window);
    glfwTerminate();
}