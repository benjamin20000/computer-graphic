#include <GL/glut.h>
#include <cmath>
#include <algorithm>
#include<iostream>
#include"settings.h"
#include"button.h"
#include"world.h"
#include"control.h"

// Function to initialize OpenGL settings
void init() {
    glEnable(GL_DEPTH_TEST);            // Enable depth testing
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
}

// Function to render the scene
void display() {
    // Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set the camera view
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Define the camera view using gluLookAt
    gluLookAt(cameraX, cameraY, cameraZ, 
              cameraX + sin(cameraAngleX), cameraY - 0.2f, cameraZ - cos(cameraAngleX), 
              0.0f, 1.0f, 0.0f);

    // Initialize lighting and render the 3D objects
    initLighting();
    drawFloor();                                 // Draw the floor
    drawCube(cubeX, cubeY, cubeZ, cubeSize);     // Draw a cube
    drawMetallicSphere(-15.0f, 2.0f, 20.0f, 5.0f); // Draw a sphere
    drawRobot(robotX, 0.0f, robotZ, robotAngle); // Draw a robot

    // Switch to 2D mode for drawing buttons
    switchTo2D();

    // Disable certain states for 2D rendering
    glDisable(GL_LIGHTING);  // Disable lighting in 2D mode
    glDisable(GL_DEPTH_TEST); // Disable depth testing in 2D mode
    glDisable(GL_BLEND);      // Disable blending

    // Draw 2D buttons
    drawButton(0, 110, 50, 50,"On");
    drawButton(0, 55, 50, 50,"Off");
    drawButton(0, 0, 50, 50,"Quit");

    // Restore 3D projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    // Swap buffers to display the scene
    glutSwapBuffers();
}

// Main function
int main(int argc, char** argv) {
    // Initialize GLUT and set up the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Robot World");

    init();  // Initialize OpenGL settings

    // Register callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);      // Handles window resizing
    glutSpecialFunc(keyboard);     // Handles special keys (arrow keys)
    glutMouseFunc(mouseCallback);  // Handles mouse input

    // Enter the main loop
    glutMainLoop();
    return 0;
}
