/* First OpenGL
 *
 * This program creates a new window with the background in red color.
 * 
 * It is an adaptation for the code listed in:
 *
 * Gordon, V. S., & Clevenger, J.  (2019). Computer graphics programming in
 * Opengl with C++. Mercury Learning and Information. p.  10.
 *
 * (2021) Jaime Lopez <jailop AT protonmail DOT com>
 */

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

void init(GLFWwindow *win) {
    /* At this moment nothing is done here */
}

void display(GLFWwindow *win, double curr_time) {
    /* Setting color to clear the screen */
    glClearColor(1.0, 0.0, 0.0, 1.0);
    /* Clearing the screen */
    glClear(GL_COLOR_BUFFER_BIT);
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
    win = glfwCreateWindow(600, 600, "First OpenGL", NULL, NULL);
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
