//
//  main.cpp
//  triangle
//
//  Created by Nazirul Hasan on 26/8/23.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float rotateAngle = 0.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 transform;\n"
"void main()\n"
"{\n"
"   gl_Position = transform * vec4(aPos, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 colorInfo;\n"
"void main()\n"
"{\n"
"   FragColor =  colorInfo;\n"
"}\n\0";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _APPLE_
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    
    float vertices[] = {
//middle
      0.459,0.975,0,
0.497,1,0,
0.536,0.974,0,

0.357,0.864,0,
0.46,0.976,0,
0.535,0.976,0,
0.638,0.864,0,

0.291,0.293,0,
0.358,0.864,0,
0.637,0.864,0,
0.7,0.292,0,

0.008,0.131,0,
0.052,0.186,0,
0.294,0.293,0,

0.69,0.301,0,
0.943,0.184,0,
0.988,0.129,0,

0.006,0.128,0,
0.16,0.127,0,

0.158,0.127,0,
0.178,0.142,0,

0.176,0.142,0,
0.357,0.142,0,
 
0.355,0.142,0,
0.387,0.171,0,

0.384,0.171,0,
0.618,0.17,0,

0.616,0.17,0,
0.641,0.142,0,

0.638,0.142,0,
0.82,0.141,0,

0.817,0.141,0,
0.829,0.127,0,

0.827,0.127,0,
0.988,0.131,0,

0.344,0.068,0,
0.374,0.17,0,
0.492,0.17,0,
0.498,0.07,0,

0.495,0.07,0,
0.501,0.17,0,
0.624,0.168,0,
0.654,0.068,0,

0.495,0.011,0,
0.515,0.068,0,
0.635,0.068,0,
0.654,0.015,0,

0.344,0.014,0,
0.356,0.068,0,
0.478,0.068,0,
0.498,0.011,0,

0.268,0.272,0,
0.281,0.28,0,
0.402,0.594,0,
0.427,0.608,0,
0.445,0.616,0,
0.459,0.618,0,
0.479,0.621,0,
0.507,0.621,0,
0.53,0.621,0,
0.55,0.616,0,
0.566,0.611,0,
0.582,0.602,0,
0.598,0.594,0,
0.712,0.28,0,
0.723,0.272,0,

0.401,0.594,0,
0.473,0.679,0,
0.525,0.679,0,
0.597,0.592,0,

0.118,0.126,0,
0.126,0.06,0,
0.297,0.062,0,
0.305,0.124,0,

0.156,0.125,0,
0.176,0.14,0,
0.299,0.137,0,
0.305,0.123,0,

0.134, 0.222,0,
0.142, 0.594,0,
0.276, 0.597,0,
0.284, 0.299,0,

0.143, 0.593,0,
0.146, 0.683,0,
0.279, 0.683,0,
0.282, 0.595,0,

0.145, 0.683,0,
0.189, 0.776,0,
0.233, 0.776,0,
0.28, 0.683,0,

0.188, 0.776,0,
0.21, 0.803,0,
0.234, 0.776,0,

//right
0.765, 0.776,0,
0.789, 0.8,0,
0.812, 0.776,0,

0.719, 0.682,0,
0.766, 0.776,0,
0.811, 0.776,0,
0.858, 0.682,0,

0.719, 0.681,0,
0.723, 0.595,0,
0.855, 0.595,0,
0.858, 0.681,0,

0.716, 0.283,0,
0.722, 0.597,0,
0.856, 0.595,0,
0.862, 0.222,0,

0.696, 0.139,0,
0.82, 0.138,0,
0.831, 0.126,0,
0.88, 0.123,0,

0.685, 0.076,0,
0.697, 0.139,0,
0.879, 0.123,0,
0.892, 0.076,0,

    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // create transformations
        /*glm::mat4 trans = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        trans = glm::translate(trans, glm::vec3( -0.6, -0.4, 0.0f));
        trans = glm::rotate(trans, glm:: radians(rotateAngle), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::scale(trans,glm::vec3(scale_X, scale_Y, 1.0));*/
        glm::mat4 translationMatrix;
        glm::mat4 rotationMatrix;
        glm::mat4 scaleMatrix;
        glm::mat4 modelMatrix;
        glm::mat4 identityMatrix = glm::mat4(1.0f);
        translationMatrix = glm::translate(identityMatrix, glm::vec3(-0.6f, -0.4f, 0.0f));
        rotationMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.3f, 1.0f));
        modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
        //modelMatrix = rotationMatrix * scaleMatrix;

        // get matrix's uniform location and set matrix
        glUseProgram(shaderProgram);
        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));


        int colorLocation = glGetUniformLocation(shaderProgram, "colorInfo");
        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));


        // draw our first triangle
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        // glDrawArrays(GL_LINE, 0,58 );

        //middle
        glDrawArrays(GL_LINE_STRIP, 0, 3);
        glDrawArrays(GL_LINE_STRIP, 3, 4);
        glDrawArrays(GL_LINE_STRIP, 7, 4);
        glDrawArrays(GL_LINE_STRIP, 11, 3);
        glDrawArrays(GL_LINE_STRIP, 14, 3);
        glDrawArrays(GL_LINE_STRIP, 17, 2);
        glDrawArrays(GL_LINE_STRIP, 19, 2);
        glDrawArrays(GL_LINE_STRIP, 21, 2);
        glDrawArrays(GL_LINE_STRIP, 23, 2);
        glDrawArrays(GL_LINE_STRIP, 25, 2);
        glDrawArrays(GL_LINE_STRIP, 27, 2);
        glDrawArrays(GL_LINE_STRIP, 29, 2);
        glDrawArrays(GL_LINE_STRIP, 31, 2);
        glDrawArrays(GL_LINE_STRIP, 33, 2);
        glDrawArrays(GL_LINE_STRIP, 35, 4);
        glDrawArrays(GL_LINE_STRIP, 39, 4);
        glDrawArrays(GL_LINE_STRIP, 43, 4);
        glDrawArrays(GL_LINE_STRIP, 47, 4);
        glDrawArrays(GL_LINE_STRIP, 51, 15);
        glDrawArrays(GL_LINE_STRIP, 66, 4);
        glDrawArrays(GL_LINE_STRIP, 70, 4);
        glDrawArrays(GL_LINE_STRIP, 74, 4);
        glDrawArrays(GL_LINE_STRIP, 78, 4);
        glDrawArrays(GL_LINE_STRIP, 82, 4);
        glDrawArrays(GL_LINE_STRIP, 86, 4);
        glDrawArrays(GL_LINE_STRIP, 90, 3);
        glDrawArrays(GL_LINE_STRIP, 93, 3);
        glDrawArrays(GL_LINE_STRIP, 96, 4);
        glDrawArrays(GL_LINE_STRIP, 100, 4);
        glDrawArrays(GL_LINE_STRIP, 104, 4);
        //
        glDrawArrays(GL_LINE_STRIP, 108, 4);
        glDrawArrays(GL_LINE_STRIP, 112, 4);
        




        




       
        



        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(0.1f, 0.1f, 0.0f, 0.1f)));
        glDrawArrays(GL_TRIANGLE_FAN, 0, 3); 
        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(0.6f, 0.2f, 0.2f, 0.36f)));
        glDrawArrays(GL_TRIANGLE_FAN, 3,4 );
        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(.8f, .9f, .98f, 0.1f)));
        glDrawArrays(GL_TRIANGLE_FAN, 7, 4); 
        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(.8f, .8f, .7f, .25f)));
        glDrawArrays(GL_TRIANGLE_FAN, 11, 3);
        glDrawArrays(GL_TRIANGLE_FAN, 14, 3);
        glDrawArrays(GL_TRIANGLE_FAN, 17, 2);
        glDrawArrays(GL_TRIANGLE_FAN, 19, 2);
        glDrawArrays(GL_TRIANGLE_FAN, 21, 2);

        glDrawArrays(GL_TRIANGLE_FAN, 23, 2);
        glDrawArrays(GL_TRIANGLE_FAN, 25, 2);
        glDrawArrays(GL_TRIANGLE_FAN, 27, 2);
        glDrawArrays(GL_TRIANGLE_FAN, 29, 2);
        glDrawArrays(GL_TRIANGLE_FAN, 31, 2);
        glDrawArrays(GL_TRIANGLE_FAN, 33, 2);
        glDrawArrays(GL_TRIANGLE_FAN, 35, 4);
        glDrawArrays(GL_TRIANGLE_FAN, 39, 4);
        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(.8f, .9f, .98f, 0.1f)));
        glDrawArrays(GL_TRIANGLE_FAN, 43, 4);
        glDrawArrays(GL_TRIANGLE_FAN, 47, 4);
        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(.8f, .8f, .7f, .25f)));
        glDrawArrays(GL_TRIANGLE_FAN, 51, 15);
        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(.1f, .1f, .0f, 0.1f)));
        glDrawArrays(GL_TRIANGLE_FAN, 66, 4);
        glDrawArrays(GL_TRIANGLE_FAN, 70, 4);
        glDrawArrays(GL_TRIANGLE_FAN, 74, 4);
       glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(.8f, .9f, .98f, 0.1f)));
        glDrawArrays(GL_TRIANGLE_FAN, 78, 4);
        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(0.6f, 0.2f, 0.2f, 0.36f)));
        glDrawArrays(GL_TRIANGLE_FAN, 82, 4);
        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(.8f, .9f, .98f, 0.1f)));
        glDrawArrays(GL_TRIANGLE_FAN, 86, 4);
        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(.1f, .1f, .0f, 0.1f)));
        glDrawArrays(GL_TRIANGLE_FAN, 90, 3);
        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(0.1f, 0.1f, 0.0f, 0.1f)));
        glDrawArrays(GL_TRIANGLE_FAN, 93, 3);
        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(.8f, .9f, .98f, 0.1f)));
        glDrawArrays(GL_TRIANGLE_FAN, 96, 4);
        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(0.6f, 0.2f, 0.2f, 0.36f)));
        glDrawArrays(GL_TRIANGLE_FAN, 100, 4);
        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(.8f, .9f, .98f, 0.1f)));
        glDrawArrays(GL_TRIANGLE_FAN, 104, 4);
        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(0.1f, 0.1f, 0.0f, 0.1f)));
        glDrawArrays(GL_TRIANGLE_FAN, 108, 4);
        glDrawArrays(GL_TRIANGLE_FAN, 112, 4);
        


       
        

        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        rotateAngle += 1;
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        rotateAngle -= 1;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        translate_Y += 0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        translate_Y -= 0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        translate_X += 0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        translate_X -= 0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        scale_X += 0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        scale_X -= 0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        scale_Y += 0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
    {
        scale_Y -= 0.01;
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}