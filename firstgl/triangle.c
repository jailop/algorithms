/* Drawing a traingle in OpenGL
 *
 * It is an adaptation for the code listed in:
 *
 * Gordon, V. S., & Clevenger, J.  (2019). Computer graphics programming in
 * Opengl with C++. Mercury Learning and Information. p. 28.
 *
 * (2021) Jaime Lopez <jailop AT protonmail DOT com>
 */

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#define numVAOs 1

GLuint renderingProgram;
/* Vertex Array Objects */
GLuint vao[numVAOs];

GLuint createShaderProgram() {
    GLuint vshader, fshader;
    GLuint vfprogram;
    const char *vshaderSource =
        "#version 430 \n"
        "void main(void) \n"
        "{ \n"
        "if (gl_VertexID == 0) \n"
        "    gl_Position = vec4(0.25, -0.25, 0.0, 1.0); \n"
        "else if (gl_VertexID == 1) \n"
        "    gl_Position = vec4(-0.25, -0.25, 0.0, 1.0); \n"
        "else \n"
        "    gl_Position = vec4(0.25, 0.25, 0.0, 1.0); \n"
        "}";
    const char *fshaderSource =
        "#version 430 \n"
        "out vec4 color; \n"
        "void main(void) \n"
        "{ color = vec4(0.0, 0.0, 1.0, 1.0); }";
    vshader = glCreateShader(GL_VERTEX_SHADER);
    fshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vshader, 1, &vshaderSource, NULL);
    glShaderSource(fshader, 1, &fshaderSource, NULL);
    glCompileShader(vshader);
    glCompileShader(fshader);
    vfprogram = glCreateProgram();
    glAttachShader(vfprogram, vshader);
    glAttachShader(vfprogram, fshader);
    glLinkProgram(vfprogram);
    return vfprogram;
}

void init(GLFWwindow *win) {
    renderingProgram = createShaderProgram();
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void display(GLFWwindow *win, double curr_time) {
    glUseProgram(renderingProgram);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main() {
    int ret;
    GLFWwindow *win;

    /* GLFW library initialization
     * GLFW: OpenGL framework */
    ret = glfwInit();
    if (!ret) {
        fprintf(stderr, "GLFW could not be initilizated\n");
        exit(EXIT_FAILURE);
    }

    /* Options for windows
     * OpenGL must be compatible with version 4.3 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    /* Window and context creation */
    win = glfwCreateWindow(600, 600, "Triangle OpenGL", NULL, NULL);
    glfwMakeContextCurrent(win);
    
    /* GLEW library initialization
     * GLEW: OpenGL Extension Wrangler */
    ret = glewInit();
    if (ret != GLEW_OK) {
        fprintf(stderr, "GLEW could not be initilizated\n");
        exit(EXIT_FAILURE);
    }

    /* Vertical syncronization */
    glfwSwapInterval(1);
    
    init(win);
    while (!glfwWindowShouldClose(win)) {
        display(win, glfwGetTime());
        /* Paiting the screen */
        glfwSwapBuffers(win);
        /* Handling other windows related events */
        glfwPollEvents();
    }
    
    /* Cleaning environment */
    glfwDestroyWindow(win);
    glfwTerminate();
    return 0;
}
