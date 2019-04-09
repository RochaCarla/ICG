#include <iostream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>



using namespace std;
unsigned int compile_shader(string filename, bool is_fragment);

unsigned int compile_shader(string filename, bool is_fragment)
{
    ifstream file(filename);
    string src = "";
    
    if(file.is_open())
    {
        string line;
        while(getline(file, line)) src += line + "\n";
        file.close();
    }
    else
    {
        cout << "Could not load file [" << filename << "]" << endl;
        return 0;
    }
    
    unsigned int shader;
    if (is_fragment) shader = glCreateShader(GL_FRAGMENT_SHADER);
    else shader = glCreateShader(GL_VERTEX_SHADER);
    
    const char * src_str = src.c_str();
    glShaderSource(shader, 1, &src_str, NULL);
    glCompileShader(shader);
    
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char log[512];
        glGetShaderInfoLog(shader, 512, NULL, log);
        cout << "Shader [" << filename << "] compilation failed: " << log << endl;
        return 0;
    }
    
    return shader;
}
float  vertices[] = {
    0.0f, 0.5f,
    0.5f, -0.5f,
    -0.5f, 0.5f
};
unsigned int indices[] = {
0, 1, 2
};
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    cout << "Game On" << endl;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Mac OS only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Playground", NULL, NULL);
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

    int screenWidth = 800;
    int screenHeight = 600;
    glViewport(0, 0, screenWidth, screenHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    unsigned int v_shader = compile_shader("vertex.glsl", false);
    unsigned int f_shader = compile_shader("fragment.glsl", false);
    
    unsigned int  shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,v_shader);
    glAttachShader(shaderProgram,f_shader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);


    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    unsigned int VAO;
    unsigned int  vbo, EBO;
    glGenBuffers(1,&vbo);
    glGenBuffers(1,&EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

  
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices , vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glUseProgram(shaderProgram);
    

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
       
        glBindVertexArray(VAO);
       // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
